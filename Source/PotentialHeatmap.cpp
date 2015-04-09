#include "PotentialHeatmap.h"

PotentialHeatmap::PotentialHeatmap(unsigned int width, unsigned int height) {

  std::cout << "Starting SDL..." << std::endl;;
  if(SDL_Init(SDL_INIT_VIDEO) == -1)
    exit(EXIT_FAILURE);

  _width = width;
  _height = height;

  std::cout << "Create window..." << std::endl;;
  _window = SDL_CreateWindow("GraviticBoosters (heatmap)",
                             SDL_WINDOWPOS_UNDEFINED,
                             SDL_WINDOWPOS_UNDEFINED,
                             width, height,
                             SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

  std::cout << "Create renderer..." << std::endl;;
  _renderer = SDL_CreateRenderer(_window, 0, SDL_RENDERER_ACCELERATED);

}

PotentialHeatmap::~PotentialHeatmap() {
  SDL_Quit();
}


void PotentialHeatmap::update(Map * map, Camera * camera) {

  _tileW = _width / map->getWidth();
  _tileH = _height / map->getHeight();

  SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);

  SDL_Color color;
  SDL_Rect r;
  Tile * tile;
  r.w = _tileW;
  r.h = _tileH;

  for(unsigned int w = 0; w < map->getNumOfTilesH(); w++) {
    for(unsigned int h = 0; h < map->getNumOfTilesV(); h++) {
      tile = map->getTileAt(w, h);
      color = potentialToColor(tile->getPotential());
      r.x = _tileW * w;
      r.y = _tileH * h;
      SDL_SetRenderDrawColor(_renderer, color.r, color.g, color.b, 255);
      SDL_RenderFillRect(_renderer, &r);
    }
  }

  SDL_SetRenderDrawColor(_renderer, 60, 60, 60, 255);

  r.w = _width;
  r.h = 1;
  r.y = 0;
  for(unsigned int i = 0; i < map->getWidth(); i++) {
    r.x = i*_tileW;
    SDL_RenderFillRect(_renderer, &r);
  }

  r.w = 1;
  r.h = _height;
  r.x = 0;
  for(unsigned int j = 0; j < map->getHeight(); j++) {
    r.y = j*_tileH;
    SDL_RenderFillRect(_renderer, &r);
  }

  // TODO display camera

}

SDL_Color PotentialHeatmap::potentialToColor(double potential) {
  SDL_Color color;
  if(potential < .5) {
    color.r = 0;
    color.g = 0;
    color.b = (int)(potential * 510);
  } else {
    color.r = (int)(potential * 510 - 255);
    color.g = (int)(potential * 510 - 255);
    color.b = 255;
  }
  return color;
}
