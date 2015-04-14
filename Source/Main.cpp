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
#include <windows.h>

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

void theadGB(std::unordered_map<int, BWAPI::Player> enemies) {
  Position * initPosCam = new Position(BWAPI::Broodwar->mapWidth() / 2, BWAPI::Broodwar->mapHeight() / 2);
  Map * map = new Map(BWAPI::Broodwar->mapWidth()*TILE_SIZE, BWAPI::Broodwar->mapHeight()*TILE_SIZE, 40, 40);
  PotentialHeatmap * phm = new PotentialHeatmap(800, 600);
  Camera * camera = new Camera(*initPosCam);
  BWAPI::Position pos;
  BWAPI::Unit u, enemy = NULL;
  while(true) {
    for(auto entity : GraviticBooster::getEntities()) {
      u = BWAPI::Broodwar->getUnit(entity.second->getId());
      pos = u->getPosition();
      entity.second->setPosition(Position(pos.x, pos.y));
      //enemy = u->getClosestUnit(BWAPI::Filter::IsEnemy);
      //std::cout << enemy << std::endl;
      double dist = 9999999999;
      double curDist;
      for(auto e : enemies[u->getPlayer()->getID()]->getUnits()) {
        curDist = u->getDistance(e);
        if(curDist < dist) {
          dist = curDist;
          enemy = e;
        }
      }
      if(enemy) {
        pos = enemy->getPosition();
        entity.second->setClosestEnemyPosition(Position(pos.x, pos.y)); // FIXME ca plante
      }
    }
    map->update();
    phm->update(map, camera);
    Sleep(500);
  }
}

void changeCameraPosition(const Camera &camera) {
  auto pos = camera.getPosition();
  BWAPI::Broodwar->setScreenPosition(pos.getX(), pos.getY());
}

int main(int argc, char *argv[]) {
  BWAPI::Unitset units;
  std::vector<BWAPI::Unit> bases;
  std::vector<BWAPI::Player> players;
  std::unordered_map<int, BWAPI::Player> enemies;
  std::cout << "Connecting..." << std::endl;;
  reconnect();
  while(true) {
    waitForAMatch();
    BWAPI::Broodwar->enableFlag(BWAPI::Flag::CompleteMapInformation);
    BWAPI::Broodwar->enableFlag(BWAPI::Flag::UserInput);
    std::cout << "Starting main loop" << std::endl;    
    for(auto p : BWAPI::Broodwar->getPlayers()) {
      units = p->getUnits();
      if(!p->getUnits().empty() && !p->isNeutral())
        for(auto u : units)
          if(u->getType().isResourceDepot()) {
            players.push_back(p);
            bases.push_back(u);
          }
    }
    enemies[players[0]->getID()] = players[1];
    enemies[players[1]->getID()] = players[0];
    //std::cout << bases[0]->getDistance(bases[1]) << std::endl;
    GraviticBooster::setMaxDistance(bases[0]->getDistance(bases[1]));
    std::thread runGB(theadGB, enemies);
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
          if(ut.isBuilding())
            GraviticBooster::addEntity(u->getID(), new Building(u->getID(), Position(p.x, p.y), ut.mineralPrice(), ut.gasPrice(),
            w.damageAmount() / (double)w.damageCooldown(), u->getPlayer()->getID()));
          else
            GraviticBooster::addEntity(u->getID(), new Unit(u->getID(), Position(p.x, p.y), ut.mineralPrice(), ut.gasPrice(),
            w.damageAmount() / (double)w.damageCooldown(), ut.topSpeed(), u->getPlayer()->getID()));
          break;
        case BWAPI::EventType::UnitDestroy:
          u = e.getUnit();
          delete  GraviticBooster::getEntities()[u->getID()];
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
    for(auto p : GraviticBooster::getEntities())
      delete p.second;
  }
  std::cout << "Press ENTER to continue..." << std::endl;
  std::cin.ignore();
  return 0;
}
