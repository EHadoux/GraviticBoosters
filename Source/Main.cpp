#include <BWAPI.h>
#include <BWAPI/Client.h>
#include "Unit.h"
#include "Building.h"
#include "Position.h"
#include "Map.h"
#include "PotentialHeatmap.h"
#include "GraviticBooster.h"

#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <unordered_map>

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

int main(int argc, char *argv[]) {
  BWAPI::Unitset units;
  std::vector<BWAPI::Unit> bases;
  Map * map;
  PotentialHeatmap * phm;
  Camera * camera;
  Position * initPosCam;
  std::cout << "Connecting..." << std::endl;;
  reconnect();
  while(true) {
    waitForAMatch();
    BWAPI::Broodwar->enableFlag(BWAPI::Flag::CompleteMapInformation);
    BWAPI::Broodwar->enableFlag(BWAPI::Flag::UserInput);
    initPosCam = new Position(BWAPI::Broodwar->mapWidth() / 2, BWAPI::Broodwar->mapHeight() / 2);
    map = new Map(BWAPI::Broodwar->mapWidth(), BWAPI::Broodwar->mapHeight(), 10, 10);
    phm = new PotentialHeatmap(800, 600);
    camera = new Camera(*initPosCam);
    if(BWAPI::Broodwar->isReplay()) {
      BWAPI::Broodwar << "The following players are in this replay:" << std::endl;
      BWAPI::Playerset players = BWAPI::Broodwar->getPlayers();
      for(auto p : players) {
        if(!p->getUnits().empty() && !p->isNeutral()) {
          BWAPI::Broodwar << p->getName() << ", playing as " << p->getRace() << std::endl;
          for(auto u : p->getUnits())
            if(u->getType().isResourceDepot())
              bases.push_back(u);
        }
      }
      GraviticBooster::setMaxDistance(bases[0]->getDistance(bases[1]));
    } /*else {
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
      }*/
    std::unordered_map<int, Entity*> entities;
    while(BWAPI::Broodwar->isInGame()) {
      for(auto e : BWAPI::Broodwar->getEvents()) {
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
            entities[u->getID()] = new Building(u->getID(), Position(p.x, p.y), ut.mineralPrice(), ut.gasPrice(),
                                                w.damageAmount() / (double)w.damageCooldown(), u->getPlayer()->getID());
            std::cout << *dynamic_cast<Building*>(entities[u->getID()]) << std::endl;
          } else {
            entities[u->getID()] = new Unit(u->getID(), Position(p.x, p.y), ut.mineralPrice(), ut.gasPrice(),
                                            w.damageAmount() / (double)w.damageCooldown(), ut.topSpeed(), u->getPlayer()->getID());
            std::cout << *dynamic_cast<Unit*>(entities[u->getID()]) << std::endl;
            //GraviticBooster::addUnit(unit);
          }
          break;
        case BWAPI::EventType::UnitDestroy:
          u = e.getUnit();
          delete entities[u->getID()];
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
      BWAPI::Position pos;
      BWAPI::Unit u, enemy;
      for(auto entity : entities) {
        u = BWAPI::Broodwar->getUnit(entity.second->getId());
        pos = u->getPosition();
        entity.second->setPosition(Position(pos.x, pos.y));
        enemy = u->getClosestUnit(BWAPI::Filter::IsEnemy);
        if(enemy) {
          pos = enemy->getPosition();
          entity.second->setClosestEnemyPosition(Position(pos.x, pos.y)); // FIXME ca plante
        }
      }
      std::cout << "Updating map" << std::endl;
      map->update();
      std::cout << "Refreshing the heatmap..." << std::endl;
      phm->update(map, camera);
      reconnecting();
    }
    std::cout << "Game ended" << std::endl;
    for(auto p : entities)
      delete p.second;
  }
  std::cout << "Press ENTER to continue..." << std::endl;
  std::cin.ignore();
  return 0;
}
