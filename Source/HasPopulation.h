#pragma once

class HasPopulation {
public:
  HasPopulation(unsigned int population) { _population = population; }
  unsigned int getPopulation() const { return _population; }
  virtual void setPopulation(unsigned int population) = 0;

protected:
  unsigned int _population;
};