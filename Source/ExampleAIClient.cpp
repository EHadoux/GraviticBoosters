#include <BWAPI.h>
#include <BWAPI/Client.h>
#include "Unit.h"

#include <iostream>
#include <thread>
#include <chrono>
#include <string>

void drawStats();
void drawBullets();
void drawVisibilityData();
void showPlayers();
void showForces();
bool show_bullets;
bool show_visibility_data;

void reconnect()
{
  while(!BWAPI::BWAPIClient.connect())
  {
    std::this_thread::sleep_for(std::chrono::milliseconds{ 1000 });
  }
}

int main(int argc, const char* argv[])
{
  std::cout << "Connecting..." << std::endl;;
  reconnect();
  while(true)
  {
    std::cout << "waiting to enter match" << std::endl;
	while (!BWAPI::Broodwar->isInGame())
    {
      BWAPI::BWAPIClient.update();
      if (!BWAPI::BWAPIClient.isConnected())
      {
        std::cout << "Reconnecting..." << std::endl;;
        reconnect();
      }
    }
    std::cout << "starting match!" << std::endl;
	BWAPI::Broodwar->sendText("Hello world!");
	BWAPI::Broodwar << "The map is " << BWAPI::Broodwar->mapName() << ", a " 
		<< BWAPI::Broodwar->getStartLocations().size() << " player map" << std::endl;
    // Enable some cheat flags
	BWAPI::Broodwar->enableFlag(BWAPI::Flag::UserInput);
    // Uncomment to enable complete map information
    //Broodwar->enableFlag(Flag::CompleteMapInformation);

    show_bullets=false;
    show_visibility_data=false;

	if (BWAPI::Broodwar->isReplay())
    {
		BWAPI::Broodwar << "The following players are in this replay:" << std::endl;;
		BWAPI::Playerset players = BWAPI::Broodwar->getPlayers();
      for(auto p : players)
      {
        if ( !p->getUnits().empty() && !p->isNeutral() )
			BWAPI::Broodwar << p->getName() << ", playing as " << p->getRace() << std::endl;
      }
    }
    else
    {
		if (BWAPI::Broodwar->enemy())
			BWAPI::Broodwar << "The match up is " << BWAPI::Broodwar->self()->getRace() << " vs " 
			<< BWAPI::Broodwar->enemy()->getRace() << std::endl;

      //send each worker to the mineral field that is closest to it
		BWAPI::Unitset units = BWAPI::Broodwar->self()->getUnits();
		BWAPI::Unitset minerals = BWAPI::Broodwar->getMinerals();
      for ( auto &u : units )
      {		  
        if ( u->getType().isWorker() )
        {
			BWAPI::Unit closestMineral = nullptr;

          for (auto &m : minerals)
          {
            if ( !closestMineral || u->getDistance(m) < u->getDistance(closestMineral))
              closestMineral = m;
          }
          if ( closestMineral )
            u->rightClick(closestMineral);
        }
        else if ( u->getType().isResourceDepot() )
        {
          //if this is a center, tell it to build the appropiate type of worker
			u->train(BWAPI::Broodwar->self()->getRace().getWorker());
        }
      }
    }
	while (BWAPI::Broodwar->isInGame())
    {
		for (auto &e : BWAPI::Broodwar->getEvents())
      {
        switch(e.getType())
        {
		case BWAPI::EventType::MatchEnd:
            if (e.isWinner())
				BWAPI::Broodwar << "I won the game" << std::endl;
            else
				BWAPI::Broodwar << "I lost the game" << std::endl;
            break;
		case BWAPI::EventType::SendText:
            if (e.getText()=="/show bullets")
            {
              show_bullets=!show_bullets;
            } else if (e.getText()=="/show players")
            {
              showPlayers();
            } else if (e.getText()=="/show forces")
            {
              showForces();
            } else if (e.getText()=="/show visibility")
            {
              show_visibility_data=!show_visibility_data;
            }
            else
            {
				BWAPI::Broodwar << "You typed \"" << e.getText() << "\"!" << std::endl;
            }
            break;
		case BWAPI::EventType::ReceiveText:
			BWAPI::Broodwar << e.getPlayer()->getName() << " said \"" << e.getText() << "\"" << std::endl;
            break;
		case BWAPI::EventType::PlayerLeft:
			BWAPI::Broodwar << e.getPlayer()->getName() << " left the game." << std::endl;
            break;
		case BWAPI::EventType::NukeDetect:
			if (e.getPosition() != BWAPI::Positions::Unknown)
            {
				BWAPI::Broodwar->drawCircleMap(e.getPosition(), 40, BWAPI::Colors::Red, true);
				BWAPI::Broodwar << "Nuclear Launch Detected at " << e.getPosition() << std::endl;
            }
            else
				BWAPI::Broodwar << "Nuclear Launch Detected" << std::endl;
            break;
		case BWAPI::EventType::UnitCreate:
			if (!BWAPI::Broodwar->isReplay())
				BWAPI::Broodwar << "A " << e.getUnit()->getType() << " [" << 
				e.getUnit() << "] has been created at " << e.getUnit()->getPosition() << std::endl;
            else
            {
              // if we are in a replay, then we will print out the build order
              // (just of the buildings, not the units).
              if (e.getUnit()->getType().isBuilding() && e.getUnit()->getPlayer()->isNeutral()==false)
              {
				  int seconds = BWAPI::Broodwar->getFrameCount() / 24;
                int minutes=seconds/60;
                seconds%=60;
				BWAPI::Broodwar->sendText("%.2d:%.2d: %s creates a %s", minutes, seconds, e.getUnit()->getPlayer()->getName().c_str(), e.getUnit()->getType().c_str());
              }
            }
            break;
		case BWAPI::EventType::UnitDestroy:
			if (!BWAPI::Broodwar->isReplay())
				BWAPI::Broodwar->sendText("A %s [%p] has been destroyed at (%d,%d)", e.getUnit()->getType().c_str(), e.getUnit(), e.getUnit()->getPosition().x, e.getUnit()->getPosition().y);
            break;
		case BWAPI::EventType::UnitMorph:
			if (!BWAPI::Broodwar->isReplay())
				BWAPI::Broodwar->sendText("A %s [%p] has been morphed at (%d,%d)", e.getUnit()->getType().c_str(), e.getUnit(), e.getUnit()->getPosition().x, e.getUnit()->getPosition().y);
            else
            {
              // if we are in a replay, then we will print out the build order
              // (just of the buildings, not the units).
              if (e.getUnit()->getType().isBuilding() && e.getUnit()->getPlayer()->isNeutral()==false)
              {
				  int seconds = BWAPI::Broodwar->getFrameCount() / 24;
                int minutes=seconds/60;
                seconds%=60;
				BWAPI::Broodwar->sendText("%.2d:%.2d: %s morphs a %s", minutes, seconds, e.getUnit()->getPlayer()->getName().c_str(), e.getUnit()->getType().c_str());
              }
            }
            break;
		case BWAPI::EventType::UnitShow:
			if (!BWAPI::Broodwar->isReplay())
				BWAPI::Broodwar->sendText("A %s [%p] has been spotted at (%d,%d)", e.getUnit()->getType().c_str(), e.getUnit(), e.getUnit()->getPosition().x, e.getUnit()->getPosition().y);
            break;
		case BWAPI::EventType::UnitHide:
			if (!BWAPI::Broodwar->isReplay())
				BWAPI::Broodwar->sendText("A %s [%p] was last seen at (%d,%d)", e.getUnit()->getType().c_str(), e.getUnit(), e.getUnit()->getPosition().x, e.getUnit()->getPosition().y);
            break;
		case BWAPI::EventType::UnitRenegade:
			if (!BWAPI::Broodwar->isReplay())
				BWAPI::Broodwar->sendText("A %s [%p] is now owned by %s", e.getUnit()->getType().c_str(), e.getUnit(), e.getUnit()->getPlayer()->getName().c_str());
            break;
		case BWAPI::EventType::SaveGame:
			BWAPI::Broodwar->sendText("The game was saved to \"%s\".", e.getText().c_str());
            break;
        }
      }

      if (show_bullets)
        drawBullets();

      if (show_visibility_data)
        drawVisibilityData();

      drawStats();
	  BWAPI::Broodwar->drawTextScreen(300, 0, "FPS: %f", BWAPI::Broodwar->getAverageFPS());

      BWAPI::BWAPIClient.update();
      if (!BWAPI::BWAPIClient.isConnected())
      {
        std::cout << "Reconnecting..." << std::endl;
        reconnect();
      }
    }
    std::cout << "Game ended" << std::endl;
  }
  std::cout << "Press ENTER to continue..." << std::endl;
  std::cin.ignore();
  return 0;
}

void drawStats()
{
  int line = 0;
  BWAPI::Broodwar->drawTextScreen(5, 0, "I have %d units:", BWAPI::Broodwar->self()->allUnitCount());
  for (auto& unitType : BWAPI::UnitTypes::allUnitTypes())
  {
	  int count = BWAPI::Broodwar->self()->allUnitCount(unitType);
    if ( count )
    {
		BWAPI::Broodwar->drawTextScreen(5, 16 * line, "- %d %s%c", count, unitType.c_str(), count == 1 ? ' ' : 's');
      ++line;
    }
  }
}

void drawBullets()
{
	for (auto &b : BWAPI::Broodwar->getBullets())
  {
	BWAPI::Position p = b->getPosition();
    double velocityX = b->getVelocityX();
    double velocityY = b->getVelocityY();
	BWAPI::Broodwar->drawLineMap(p, p + BWAPI::Position((int)velocityX, (int)velocityY), b->getPlayer() == BWAPI::Broodwar->self() ? BWAPI::Colors::Green : BWAPI::Colors::Red);
	BWAPI::Broodwar->drawTextMap(p, "%c%s", b->getPlayer() == BWAPI::Broodwar->self() ? BWAPI::Text::Green : BWAPI::Text::Red, b->getType().c_str());
  }
}

void drawVisibilityData()
{
	int wid = BWAPI::Broodwar->mapHeight(), hgt = BWAPI::Broodwar->mapWidth();
  for ( int x = 0; x < wid; ++x )
    for ( int y = 0; y < hgt; ++y )
    {
		if (BWAPI::Broodwar->isExplored(x, y))
			BWAPI::Broodwar->drawDotMap(x * 32 + 16, y * 32 + 16, BWAPI::Broodwar->isVisible(x, y) ? BWAPI::Colors::Green : BWAPI::Colors::Blue);
      else
		  BWAPI::Broodwar->drawDotMap(x * 32 + 16, y * 32 + 16, BWAPI::Colors::Red);
    }
}

void showPlayers()
{
	BWAPI::Playerset players = BWAPI::Broodwar->getPlayers();
  for(auto p : players)
	  BWAPI::Broodwar << "Player [" << p->getID() << "]: " << p->getName() << " is in force: " << p->getForce()->getName() << std::endl;
}

void showForces()
{
	BWAPI::Forceset forces = BWAPI::Broodwar->getForces();
  for(auto f : forces)
  {
	  BWAPI::Playerset players = f->getPlayers();
	  BWAPI::Broodwar << "Force " << f->getName() << " has the following players:" << std::endl;
    for(auto p : players)
		BWAPI::Broodwar << "  - Player [" << p->getID() << "]: " << p->getName() << std::endl;
  }
}
