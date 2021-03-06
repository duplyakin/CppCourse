#include <algorithm>
#include <vector>
#include <cstdlib>
#include "logger.h"

class Unit {
protected:
  Unit(int health, int armor, int damage, int speed);

public:
  ~Unit() {}

  void attack() const;

private:
  int m_health;
  int m_armor;
  int m_damage;
  int m_speed;
};

Unit::Unit(int health, int armor, int damage, int speed)
  : m_health(health), m_armor(armor), m_damage(damage), m_speed(speed) {
  DBG("Unit ctor(%i, %i, %i, %i)", m_health, m_armor, m_damage, m_speed);
}

void Unit::attack() const {
  DBG("Unit attacks");
}

// ----------------------------------------------
class Footman : public Unit {
public:
  Footman();

  void attack() const;  // hiding
};

Footman::Footman() : Unit(420, 7, 21, 270) {}

void Footman::attack() const {
  INF("Footman attacks");
}

// ----------------------------------------------
class Archer : public Unit {
public:
  Archer();

  void attack() const;  // hiding
};

Archer::Archer() : Unit(235, 4, 17, 280) {}

void Archer::attack() const {
  INF("Archer attacks");
}

// ----------------------------------------------
class Knight : public Unit {
public:
  Knight();

  void attack() const;  // hiding
};

Knight::Knight() : Unit(875, 11, 36, 340) {}

void Knight::attack() const {
  INF("Knight attacks");
}

/* Create army */
// ----------------------------------------------------------------------------
enum UnitType {
  FOOTMAN = 0, ARCHER = 1, KNIGHT = 2
};

void create(std::vector<Unit*>* units) {
  size_t size = rand() % 10 + 3;
  for (size_t i = 0; i < size; ++i) {
    int value = rand() % 3;
    switch (value) {
      case FOOTMAN:
        units->push_back(new Footman());
        break;
      case ARCHER:
        units->push_back(new Archer());
        break;
      case KNIGHT:
        units->push_back(new Knight());
        break;
     }
  }
}

void clear(std::vector<Unit*>* units) {
  for (auto it = units->begin(); it != units->end(); ++it) {
    delete *it;
  }
  units->clear();
}

/* Main */
// ----------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 5]: Polymorphism 0");

  std::vector<Unit*> units;
  create(&units);

  for (auto ptr : units) {
    ptr->attack();
  }

  clear(&units);

  DBG("[Lesson 5]: Polymorphism 0 [END]");
  return 0;
}

