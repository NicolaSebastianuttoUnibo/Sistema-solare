

#include "../universe.hpp"
#include "doctest.h"

TEST_CASE("Testing distance calculation") {
  G::PlanetState planet1;
  G::PlanetState planet2;

  U::Newton newton;

  SUBCASE("Check distance calculation") {
    planet1.x = 0;
    planet1.y = 0;

    planet2.x = 3;
    planet2.y = 4;

    CHECK((25) == doctest::Approx(newton.d_2(planet1, planet2)));
    planet1.x = 36;
    planet1.y = -12;

    planet2.x = -22;
    planet2.y = 38;

    CHECK((5864) == doctest::Approx(newton.d_2(planet1, planet2)));

    planet1.x = -4;
    planet1.y = -84;

    planet2.x = -6;
    planet2.y = -2;

    CHECK((6728) == doctest::Approx(newton.d_2(planet1, planet2)));

    planet1.x = 37;
    planet1.y = 0;

    planet2.x = 0;
    planet2.y = 0;

    CHECK((1369) == doctest::Approx(newton.d_2(planet1, planet2)));
  }

  SUBCASE("Check minumm distance planet calculation") {
    planet1.r = 10;
    planet2.r = 0;
    CHECK((100) == doctest::Approx(newton.r_2(planet1, planet2)));

    planet1.r = 27;
    planet2.r = 8;
    CHECK((1225) == doctest::Approx(newton.r_2(planet1, planet2)));

    planet1.r = 36;
    planet2.r = 100;
    CHECK((18496) == doctest::Approx(newton.r_2(planet1, planet2)));

    planet1.r = 17;
    planet2.r = 41;
    CHECK((3364) == doctest::Approx(newton.r_2(planet1, planet2)));
  }
}
