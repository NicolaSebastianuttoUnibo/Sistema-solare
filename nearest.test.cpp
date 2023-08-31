#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <string>

#include "doctest.h"
#include "universe.hpp"

TEST_CASE("Testing nearest planet calculation") {
  SUBCASE("First"){
  
  U::Newton newton;
  U::Universe universe(newton);

  G::PlanetState planet1;
  planet1.x = 0;
  planet1.y = 0;

  G::PlanetState planet2;
  planet2.x = 3;
  planet2.y = 4;

  universe.push_back(planet1);
  universe.push_back(planet2);

  SUBCASE("Check nearest planet calculation") {
    sf::Vector2i targetPosition(2, 2);  // Generiche coordinate target
    int nearestPlanetIndex = universe.findNearestPlanet(targetPosition);

    CHECK(nearestPlanetIndex ==
          1);  // L'indice del pianeta più vicino deve essere 0
  }
}

SUBCASE("Second"){
  
  U::Newton newton;
  U::Universe universe(newton);

  G::PlanetState planet1;
  planet1.x = 3;
  planet1.y = 3;

  G::PlanetState planet2;
  planet2.x = 48000;
  planet2.y = 4600;

  universe.push_back(planet1);
  universe.push_back(planet2);

  SUBCASE("Check nearest planet calculation") {
    sf::Vector2i targetPosition(1500, 1700);  // Generiche coordinate target
    int nearestPlanetIndex = universe.findNearestPlanet(targetPosition);

    CHECK(nearestPlanetIndex ==
          0);  // L'indice del pianeta più vicino deve essere 0
  }
}

SUBCASE("Third"){
  
  U::Newton newton;
  U::Universe universe(newton);

  G::PlanetState planet1;
  planet1.x = -12;
  planet1.y = -12;

  G::PlanetState planet2;
  planet2.x = 12;
  planet2.y = 12;

  universe.push_back(planet1);
  universe.push_back(planet2);

  SUBCASE("Check nearest planet calculation") {
    sf::Vector2i targetPosition(0, 0);  // Generiche coordinate target
    int nearestPlanetIndex = universe.findNearestPlanet(targetPosition);

    CHECK(nearestPlanetIndex ==
          1);  // L'indice del pianeta più vicino deve essere 0
  }
}


}



