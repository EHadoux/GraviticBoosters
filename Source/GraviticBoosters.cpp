#include "GraviticBooster.h"

void GraviticBooster::update() {
  _clock++;
  GraviticBooster::_map->update();
  GraviticBooster::_phm->update(GraviticBooster::_map, GraviticBooster::_camera);
  GraviticBooster::_camera->update(GraviticBooster::_map);
}

Building* GraviticBooster::closestUnseenBuilding(Position pos, int owner) {
  double distance = 999999999999;
  Building *e = NULL, *ret = NULL;
  for(auto p : GraviticBooster::_entities) {
    e = dynamic_cast<Building*>(p.second);
    if(e == NULL) continue;
    double curDist = pos.euclidian(p.second->getPosition());
    if(owner != e->getOwner() && curDist < distance && !e->seen()) {
      distance = curDist;
      ret = e;
    }
  }
  return ret;
}

std::unordered_map<int, Entity*> GraviticBooster::_entities;
double GraviticBooster::_maxDistance;
unsigned int GraviticBooster::_clock;
Map * GraviticBooster::_map;
PotentialHeatmap * GraviticBooster::_phm;
Camera * GraviticBooster::_camera;