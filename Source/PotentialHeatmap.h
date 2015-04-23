#pragma once

#include "SDL.h"
#include "Map.h"
#include "Camera.h"

class PotentialHeatmap {

public:
  PotentialHeatmap(unsigned int width, unsigned int height);
  virtual ~PotentialHeatmap();
  void update(Map * map, Camera * camera);
  enum mode { MIXED, AGGRESSION, ECONOMIC, STRATEGIC };

private:
  SDL_Color potentialToColor(Tile * tile);

  SDL_Window * _window;
  SDL_Renderer * _renderer;
  SDL_Event _event;

  int _width, _height, _tileW, _tileH;
  mode _mode;
};