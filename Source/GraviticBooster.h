#pragma once

#include "PotentialHeatmap.h"
#include "Building.h"
#include "Unit.h"
#include <unordered_map>

class GraviticBooster {
private:
  static std::unordered_map<int, Entity*> _entities;
  static double _maxDistance;
  static unsigned int _clock;
  static Map * _map;
  static PotentialHeatmap * _phm;
  static Camera * _camera;

public:
  static int getClock() { return GraviticBooster::_clock; }
  static Map * getMap() { return GraviticBooster::_map; }
  static void setMap(Map * map) { GraviticBooster::_map = map; }
  static PotentialHeatmap * getHeatmap() { return GraviticBooster::_phm; }
  static void setHeatmap(PotentialHeatmap * phm) { GraviticBooster::_phm = phm; }
  static Camera * getCamera() { return GraviticBooster::_camera; }
  static void setCamera(Camera * camera) { GraviticBooster::_camera = camera; }
  static double getMaxDistance() { return GraviticBooster::_maxDistance; }
  static void setMaxDistance(double maxDistance) { GraviticBooster::_maxDistance = maxDistance; }
  static void addEntity(int id, Entity *entity) { GraviticBooster::_entities[id] = entity; }
  static std::unordered_map<int, Entity*> getEntities() { return GraviticBooster::_entities; }
  static void update();
  static Building* closestUnseenBuilding(Position pos, int owner);
};
