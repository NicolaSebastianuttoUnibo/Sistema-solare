#include <string>

#include "../universe.hpp"
#include "doctest.h"
TEST_CASE("COLLISIONS") {
  SUBCASE("Test in static collisions") {
    U::Newton n{};
    U::Universe u(n);
    G::PlanetState p1{1e2, 0, 0, 0, 0, 0};
    G::PlanetState p2{110, 0, 0, 0, 0, 0};
    u.push_back(p1);
    u.push_back(p2);

    CHECK(u.size() == doctest::Approx(2));
    u.evolve(0);
    CHECK(u.size() == doctest::Approx(1));

    U::Universe universe(n);

    G::PlanetState p3{2, 1000, 0, 0, 0, 50};
    G::PlanetState p4{1e1, 0, 0, 0, 0, 50};
    G::PlanetState p5{1e2, 100, 0, 0, 0, 60};
    universe.push_back(p3);
    universe.push_back(p4);
    universe.push_back(p5);

    CHECK(universe.size() == doctest::Approx(3));
    universe.evolve(1);
    CHECK(universe.size() == doctest::Approx(2));
  }

  SUBCASE("Testing collision in dinamic collision") {
    U::Newton newton;
    U::Universe universe(newton);

    G::PlanetState planet1{10, 0, 0, 1, 0, 10};
    G::PlanetState planet2{100, 200, 0, 0, 0, 50};

    universe.push_back(planet1);
    universe.push_back(planet2);

    for (int i = 0; i < 1e5; i++) {
      universe.evolve(0.1);
    }

    CHECK(1 == doctest::Approx(universe.size()));
    CHECK(110 == doctest::Approx(universe[0].m));
    CHECK(50.99 == doctest::Approx(universe[0].r));
  }
}