#include <BWAPI.h>
#include <BWAPI/Client.h>
#include "Unit.h"

#include <iostream>
#include <thread>
#include <chrono>
#include <string>

void reconnect() {
  while(!BWAPI::BWAPIClient.connect()) {
    std::this_thread::sleep_for(std::chrono::milliseconds{1000});
  }
}

void reconnecting() {
  BWAPI::BWAPIClient.update();
  if(!BWAPI::BWAPIClient.isConnected()) {
    std::cout << "Reconnecting..." << std::endl;;
    reconnect();
  }
}

void waitForAMatch() {
  std::cout << "waiting to enter match" << std::endl;
  while(!BWAPI::Broodwar->isInGame())
    reconnecting();
  std::cout << "starting match!" << std::endl;
}

int main(int argc, const char* argv[]) {
  std::cout << "Connecting..." << std::endl;;
  reconnect();
  while(true) {
    waitForAMatch();
    BWAPI::Broodwar->enableFlag(BWAPI::Flag::CompleteMapInformation);

    if(BWAPI::Broodwar->isReplay()) {
      BWAPI::Broodwar << "The following players are in this replay:" << std::endl;
      BWAPI::Playerset players = BWAPI::Broodwar->getPlayers();
      for(auto p : players) {
        if(!p->getUnits().empty() && !p->isNeutral())
          BWAPI::Broodwar << p->getName() << ", playing as " << p->getRace() << std::endl;
      }
    } else {
      if(BWAPI::Broodwar->enemy())
        BWAPI::Broodwar << "The match up is " << BWAPI::Broodwar->self()->getRace() << " vs "
        << BWAPI::Broodwar->enemy()->getRace() << std::endl;

      //send each worker to the mineral field that is closest to it
      BWAPI::Unitset units = BWAPI::Broodwar->self()->getUnits();
      BWAPI::Unitset minerals = BWAPI::Broodwar->getMinerals();
      for(auto &u : units) {
        if(u->getType().isWorker()) {
          BWAPI::Unit closestMineral = nullptr;

          for(auto &m : minerals) {
            if(!closestMineral || u->getDistance(m) < u->getDistance(closestMineral))
              closestMineral = m;
          }
          if(closestMineral)
            u->rightClick(closestMineral);
        } else if(u->getType().isResourceDepot()) {
          //if this is a center, tell it to build the appropiate type of worker
          u->train(BWAPI::Broodwar->self()->getRace().getWorker());
        }
      }
    }
    while(BWAPI::Broodwar->isInGame()) {
      for(auto &e : BWAPI::Broodwar->getEvents()) {
        switch(e.getType()) {
        case BWAPI::EventType::MatchEnd:
          break;
        case BWAPI::EventType::ReceiveText:
          break;
        case BWAPI::EventType::PlayerLeft:
          break;
        case BWAPI::EventType::NukeDetect:
          break;
        case BWAPI::EventType::UnitCreate:
          break;
        case BWAPI::EventType::UnitDestroy:
          break;
        case BWAPI::EventType::UnitMorph:
          break;
        case BWAPI::EventType::UnitShow:
          break;
        case BWAPI::EventType::UnitHide:
          break;
        case BWAPI::EventType::UnitRenegade:
          break;
        }
      }

      reconnecting();
    }
    std::cout << "Game ended" << std::endl;
  }
  std::cout << "Press ENTER to continue..." << std::endl;
  std::cin.ignore();
  return 0;
}
