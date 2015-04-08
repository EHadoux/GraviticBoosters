#include <BWAPI.h>
#include <BWAPI/Client.h>
#include "Unit.h"
#include "Building.h"
#include "Position.h"
#include "GraviticBooster.h"

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
  BWAPI::Unitset units;
  std::cout << "Connecting..." << std::endl;;
  reconnect();
  while(true) {
    waitForAMatch();
    BWAPI::Broodwar->enableFlag(BWAPI::Flag::CompleteMapInformation);
    BWAPI::Broodwar->enableFlag(BWAPI::Flag::UserInput);

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
      units = BWAPI::Broodwar->self()->getUnits();
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
    std::map<int, Entity*> entities;
    while(BWAPI::Broodwar->isInGame()) {
      for(auto &e : BWAPI::Broodwar->getEvents()) {
        BWAPI::Unit u;
        BWAPI::Position p;
        BWAPI::UnitType ut;
        BWAPI::WeaponType w;
        //Unit *unit;
        //Building *building;
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
          u = e.getUnit();
          ut = u->getType();
          if(ut.isNeutral() || ut == BWAPI::UnitTypes::Zerg_Larva)
            break;
          p = u->getPosition();
          w = ut.groundWeapon();
          if(ut.isBuilding()) {
            entities[u->getReplayID()] = new Building(u->getReplayID(), Position(p.x, p.y), ut.mineralPrice(), ut.gasPrice());
            //delete building;
          } else {
            entities[u->getReplayID()] = new Unit(u->getReplayID(), Position(p.x, p.y), ut.mineralPrice(), ut.gasPrice(), w.damageAmount() / (double)w.damageCooldown(),
                                                  ut.topSpeed());
            //GraviticBooster::addUnit(unit);
            //delete unit;
          }
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
        BWAPI::Position pos;
        Entity* e;
        for(auto &u : units) {
          pos = u->getPosition();
          e = entities[u->getReplayID()];
          if(e == NULL)
            break;
          e->getPosition().update(pos.x, pos.y);
          std::cout << *entities[u->getReplayID()] << std::endl;
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
