#pragma once

#include "SDL.h"
#include "Map.h"
#include "Camera.h"

class PotentialHeatmap {

public:
  PotentialHeatmap(unsigned int width, unsigned int height);
  virtual ~PotentialHeatmap();
  void update(Map * map, Camera * camera);

private:
  SDL_Color potentialToColor(double potential);

  SDL_Window * _window;
  SDL_Renderer * _renderer;
  SDL_Event _event;

  int _width, _height, _tileW, _tileH;
};