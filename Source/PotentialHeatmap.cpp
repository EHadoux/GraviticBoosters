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
  std::cout << "Renderer created" << std::endl;
}

PotentialHeatmap::~PotentialHeatmap() {
  SDL_DestroyWindow(_window);
  SDL_Quit();
}


void PotentialHeatmap::update(Map * map, Camera * camera) {

  _tileW = _width / map->getNumOfTilesH();
  _tileH = _height / map->getNumOfTilesV();

  SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
  SDL_RenderClear(_renderer);

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
  for(unsigned int i = 0; i < map->getWidth(); i++)
    SDL_RenderDrawLine(_renderer, i*_tileW, 0, i*_tileW, _height);
  for(unsigned int j = 0; j < map->getHeight(); j++)
    SDL_RenderDrawLine(_renderer, 0, j*_tileH, _width, j*_tileH);

  // TODO display camera

  SDL_RenderPresent(_renderer);

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
