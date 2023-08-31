#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <string>

#include "doctest.h"
#include "universe.hpp"

TEST_CASE("Testing distance calculation") {
    G::PlanetState planet1;
    planet1.x = 0;
    planet1.y = 0;

    G::PlanetState planet2;
    planet2.x = 3;
    planet2.y = 4;

    U::Newton newton;
    
    SUBCASE("Check distance calculation") {
        double calculated_distance_squared = newton.d_2(planet1, planet2); // Calcoliamo il quadrato della distanza
        double expected_distance_squared = 25.0; // (3^2 + 4^2) = 25.0
        
        CHECK(calculated_distance_squared == doctest::Approx(expected_distance_squared));
    }
}
