#include "PotentialHeatmap.h"
#include "GraviticBooster.h"

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

  SDL_Color color;
  SDL_Rect r;
  Tile * tile;
  r.w = _tileW;
  r.h = _tileH;

  for(unsigned int w = 0; w < map->getNumOfTilesH(); w++) {
    for(unsigned int h = 0; h < map->getNumOfTilesV(); h++) {
      tile = map->getTileAt(w, h);
      color = potentialToColor(tile, map->getMaxTile());
      r.x = _tileW * w;
      r.y = _tileH * h;
      SDL_SetRenderDrawColor(_renderer, color.r, color.g, color.b, 255);
      SDL_RenderFillRect(_renderer, &r);
    }
  }

  SDL_SetRenderDrawColor(_renderer, 40, 40, 40, 255);
  for(unsigned int i = 0; i < map->getWidth(); i++)
    SDL_RenderDrawLine(_renderer, i*_tileW, 0, i*_tileW, _height);
  for(unsigned int j = 0; j < map->getHeight(); j++)
    SDL_RenderDrawLine(_renderer, 0, j*_tileH, _width, j*_tileH);

  SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
  int camX = (GraviticBooster::getCamera()->getPosition().getX()*_width) / map->getWidth();
  int camY = (GraviticBooster::getCamera()->getPosition().getY()*_height) / map->getHeight();
  r.x = camX - 15; r.y = camY - 15;
  SDL_RenderDrawLine(_renderer, camX - 15, camY, camX + 14, camY);
  SDL_RenderDrawLine(_renderer, camX, camY - 15, camX, camY + 14);
  r.w = 30; r.h = 30;
  SDL_RenderDrawRect(_renderer, &r);

  SDL_RenderPresent(_renderer);
}

SDL_Color PotentialHeatmap::potentialToColor(Tile * tile, Tile * maxTile) {
  SDL_Color color;
  color.r = (int)((tile->getAggressionPotential() * 255) / maxTile->getAggressionPotential());
  color.g = (int)((tile->getEconomicPotential() * 255) / maxTile->getEconomicPotential());
  color.b = (int)((tile->getStrategicPotential() * 255) / maxTile->getStrategicPotential());
  return color;
}
