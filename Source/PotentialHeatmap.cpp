#include "PotentialHeatmap.h"

PotentialHeatmap::PotentialHeatmap(unsigned int width, unsigned int height) {

  std::cout << "Starting SDL..." << std::endl;;
  if(SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  _width = width;
  _height = height;
  _mode = MIXED;

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
  SDL_PollEvent(&_event);
  switch(_event.type) {
  case SDL_QUIT:
    SDL_DestroyWindow(_window);
    SDL_Quit();
    break;
    // TODO 
  }

  _tileW = _width / map->getNumOfTilesH();
  _tileH = _height / map->getNumOfTilesV();

  SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
  SDL_RenderClear(_renderer);

  double potential;
  SDL_Color color;
  SDL_Rect r;
  Tile * tile;
  r.w = _tileW;
  r.h = _tileH;

  for(unsigned int w = 0; w < map->getNumOfTilesH(); w++) {
    for(unsigned int h = 0; h < map->getNumOfTilesV(); h++) {
      tile = map->getTileAt(w, h);
      // TODO
      //switch(_mode) {
      //case AGGRESSION: potential = tile->getAggressionPotential(); break; 
      //case ECONOMIC: potential = tile->getEconomicPotential(); break;
      //case STRATEGIC: potential = tile->getStartegicPotential(); break;
      //default: potential = tile->getPotential();
      //}
      potential = tile->getPotential();
      //std::cout << potential << std::endl;
      color = potentialToColor(potential,map->getMaxTile());
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

SDL_Color PotentialHeatmap::potentialToColor(double potential, Tile * maxTile) {
  SDL_Color color;
  color.r = 0;
  color.g = 0;
  color.b = (int)((potential * 255)/maxTile->getPotential());
  return color;
}
