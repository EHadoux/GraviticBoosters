#include "GraviticBooster.h"

void GraviticBooster::update() {
  _clock++;
  GraviticBooster::_map->update();
  GraviticBooster::_phm->update(GraviticBooster::_map, GraviticBooster::_camera);
  GraviticBooster::_camera->update(GraviticBooster::_map);
}

void GraviticBooster::deleteAll() {
  for(auto e : _entities)
    delete e.second;
  delete _map;
  delete _phm;
  delete _camera;
}

std::unordered_map<int, Entity*> GraviticBooster::_entities;
double GraviticBooster::_maxDistance;
unsigned int GraviticBooster::_clock;
Map * GraviticBooster::_map;
PotentialHeatmap * GraviticBooster::_phm;
Camera * GraviticBooster::_camera;