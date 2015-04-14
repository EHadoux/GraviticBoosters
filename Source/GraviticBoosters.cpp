#include "GraviticBooster.h"

std::unordered_map<int, Entity*> GraviticBooster::_entities;
double GraviticBooster::_maxDistance;
Map * GraviticBooster::_map;
PotentialHeatmap * GraviticBooster::_phm;
Camera * GraviticBooster::_camera;