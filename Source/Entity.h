#pragma once

#include "Position.h"
#include "math.h"
#include <vector>
#include <iostream>
#include <string>

class Entity {
public:
  Entity(unsigned int id, Position position, unsigned int minerals, unsigned int gas, double dpf, unsigned int owner);
  virtual ~Entity();

  Position getPosition() const { return _position; }
  void setPosition(const Position &position) { _position = position; }
  Position getClosestEnemyPosition() const { return _closestEnemyPosition; }
  void setClosestEnemyPosition(const Position &position) { _closestEnemyPosition = position; }
  Position getClosestUnseenBuildingPosition() const { return _closestUnseenBuildingPosition; }
  void setClosestUnseenBuildingPosition(const Position &position) { _closestUnseenBuildingPosition = position; }
  int getId() const { return _id; }
  int getOwner() const { return _owner; }
  int getCreationTime() const { return _creationTime; }
  bool isAttacking() const { return _isAttacking; }
  void isAttacking(bool attacking) { _isAttacking = attacking; }

  virtual double aggressionPotential() const;
  virtual double economicPotential() const;
  virtual double strategicPotential() const;
  virtual double getPotential() const;
  bool isEnnemy(const Entity &other) const;
  std::vector<Entity*> neighborhood() const;

  std::string toString() const;

  friend std::ostream& operator<< (std::ostream &stream, const Entity& unit);

protected:
  Position _position, _closestEnemyPosition, _closestUnseenBuildingPosition;
  unsigned int _id, _minerals, _gas, _owner, _creationTime;
  double _dpf;
  bool _isAttacking;
};
