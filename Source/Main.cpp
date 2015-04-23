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
#include <mutex>

std::mutex mutex;

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

void initGraviticBooster() {
  Position * initPosCam = new Position(BWAPI::Broodwar->mapWidth()*TILE_SIZE / 2, BWAPI::Broodwar->mapHeight()*TILE_SIZE / 2);
  GraviticBooster::setMap(new Map(BWAPI::Broodwar->mapWidth()*TILE_SIZE, BWAPI::Broodwar->mapHeight()*TILE_SIZE, 40, 40));
  GraviticBooster::setHeatmap(new PotentialHeatmap(800, 600));
  GraviticBooster::setCamera(new Camera(*initPosCam));
}

void changeCameraPosition() {
  auto pos = GraviticBooster::getCamera()->getPosition();
  BWAPI::Broodwar->setScreenPosition(BWAPI::Position(pos.getX(), pos.getY()) - BWAPI::Position(320, 240));
}

void theadGB(std::unordered_map<int, BWAPI::Player> enemies) {
  initGraviticBooster();
  BWAPI::Position pos;
  BWAPI::Unit u, enemy = NULL, building = NULL;
  while(BWAPI::Broodwar->isInGame()) {
    mutex.lock();
    for(auto entity : GraviticBooster::getEntities()) {
      u = BWAPI::Broodwar->getUnit(entity.second->getId());
      pos = u->getPosition();
      entity.second->setPosition(Position(pos.x, pos.y));
      double ennemyDist = 9999999999, buildingDist = 999999999999;
      double curDist;
      if(u->getPlayer()->getName() == "Neutral")
        continue;
      for(auto e : enemies[u->getPlayer()->getID()]->getUnits()) {
        curDist = u->getDistance(e);
        if(curDist < ennemyDist) {
          ennemyDist = curDist;
          enemy = e;
        }
        if(e->getType().isBuilding()) {
          Building *b = dynamic_cast<Building*>(GraviticBooster::getEntities()[e->getID()]);
          if(curDist < buildingDist && !b->seen() && (entity.second->getOwner() != b->getOwner())) {
            buildingDist = curDist;
            building = e;
          }
          if(e->isVisible(u->getPlayer()))
            b->setVisibility(true);
        }
      }
      pos = enemy->getPosition();
      entity.second->setClosestEnemyPosition(Position(pos.x, pos.y));
      if(building != NULL) {
        pos = building->getPosition();
        entity.second->setClosestUnseenBuildingPosition(Position(pos.x, pos.y));
      } else {
        entity.second->setClosestUnseenBuildingPosition(Position(-1, -1));
      }
      entity.second->isAttacking(u->isAttacking());
    }
    GraviticBooster::update();
    changeCameraPosition();
    mutex.unlock();
    Sleep(500);
  }
}

void createUnit(const BWAPI::Unit &u) {
  BWAPI::UnitType ut = u->getType();
  BWAPI::WeaponType w = ut.groundWeapon();
  BWAPI::Position p = u->getPosition();
  if(ut.isBuilding())
    GraviticBooster::addEntity(u->getID(), new Building(u->getID(), Position(p.x, p.y), ut.mineralPrice(), ut.gasPrice(),
    w.damageAmount() / (double)w.damageCooldown(), u->getPlayer()->getID(), ut.isResourceDepot()));
  else
    GraviticBooster::addEntity(u->getID(), new Unit(u->getID(), Position(p.x, p.y), ut.mineralPrice(), ut.gasPrice(),
    w.damageAmount() / (double)w.damageCooldown(), ut.topSpeed(), u->getPlayer()->getID(), ut.isWorker()));
}

std::thread waitAndInitAMatch() {
  BWAPI::Unitset units;
  std::vector<BWAPI::Unit> bases;
  std::vector<BWAPI::Player> players;
  std::unordered_map<int, BWAPI::Player> enemies;

  std::cout << "waiting to enter match" << std::endl;
  while(!BWAPI::Broodwar->isInGame())
    reconnecting();
  std::cout << "starting match!" << std::endl;

  BWAPI::Broodwar->enableFlag(BWAPI::Flag::CompleteMapInformation);
  BWAPI::Broodwar->enableFlag(BWAPI::Flag::UserInput);

  for(auto p : BWAPI::Broodwar->getPlayers()) {
    units = p->getUnits();
    if(!p->getUnits().empty() && !p->isNeutral())
      for(auto u : units) {
        createUnit(u);
        if(u->getType().isResourceDepot()) {
          players.push_back(p);
          bases.push_back(u);
        }
      }
  }
  enemies[players[0]->getID()] = players[1];
  enemies[players[1]->getID()] = players[0];
  //std::cout << bases[0]->getDistance(bases[1]) << std::endl;
  GraviticBooster::setMaxDistance(bases[0]->getDistance(bases[1]) + 400);
  std::thread runGB(theadGB, enemies);
  return runGB;
}

void treatEvent(const BWAPI::Event &e) {
  BWAPI::Unit u = e.getUnit();
  if(u != NULL && u->getPlayer()->isNeutral())
    return;
  switch(e.getType()) {
  case BWAPI::EventType::UnitCreate:
    createUnit(u);
    break;
  case BWAPI::EventType::UnitDestroy:
    delete GraviticBooster::getEntities()[u->getID()];
    break;
    /*case BWAPI::EventType::UnitMorph:
    u = e.getUnit();
    ut = u->getType();
    if(ut == BWAPI::UnitTypes::Zerg_Egg)
    break;
    std::cout << ut << std::endl;
    p = u->getPosition();
    w = ut.groundWeapon();
    if(ut.isBuilding())
    GraviticBooster::addEntity(u->getID(), new Building(u->getID(), Position(p.x, p.y), ut.mineralPrice(), ut.gasPrice(),
    w.damageAmount() / (double)w.damageCooldown(), u->getPlayer()->getID()));
    else
    GraviticBooster::addEntity(u->getID(), new Unit(u->getID(), Position(p.x, p.y), ut.mineralPrice(), ut.gasPrice(),
    w.damageAmount() / (double)w.damageCooldown(), ut.topSpeed(), u->getPlayer()->getID()));
    break;*/
  case BWAPI::EventType::UnitShow:
    /*if(u->getType().isBuilding())
    dynamic_cast<Building*>(GraviticBooster::getEntities()[u->getID()])->setVisibility(true);*/
    break;
    /*case BWAPI::EventType::UnitHide:
    break;
    case BWAPI::EventType::UnitRenegade:
    break;*/
    /*case BWAPI::EventType::MatchEnd:
      break;
      case BWAPI::EventType::ReceiveText:
      break;
      case BWAPI::EventType::PlayerLeft:
      break;
      case BWAPI::EventType::NukeDetect:
      break;*/
  }
}

int main(int argc, char *argv[]) {
  std::cout << "Connecting..." << std::endl;
  reconnect();
  std::thread s = waitAndInitAMatch();
  std::cout << "Starting main loop" << std::endl;
  while(BWAPI::Broodwar->isInGame()) {
    mutex.lock();
    for(auto e : BWAPI::Broodwar->getEvents())
      treatEvent(e);
    mutex.unlock();
    reconnecting();
  }
  std::cout << "Game ended" << std::endl;
  for(auto p : GraviticBooster::getEntities())
    delete p.second;
  s.join();
  std::cout << "Press ENTER to continue..." << std::endl;
  std::cin.ignore();
  return 0;
}
