#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <string>
#include "doctest.h"
#include "universe.hpp"

TEST_CASE("Testing planet collision in Universe") {
   
   U::Newton newton;
    U::Universe universe(newton);

    G::PlanetState planet1;
    planet1.x = 0.0;
    planet1.y = 0.0;
    planet1.r = 2.0;

    G::PlanetState planet2;
    planet2.x = 6.0;
    planet2.y = 0.0;
    planet2.r = 3.0;

    universe.galaxy_.push_back(planet1);
    universe.galaxy_.push_back(planet2);

    double distance_squared = newton.d_2(planet1, planet2);
    double sum_of_radii_squared = newton.r_2(planet1, planet2);

    if (distance_squared <= sum_of_radii_squared) {
        // The planets collide
        CHECK(true);
    } else {
        // The planets do not collide
        CHECK(false);
    }
}



/*SUBCASE ("Secondcase"){
   U::Newton newton;
    U::Universe universe(newton);

    G::PlanetState planet1;
    planet1.x = 1.0;
    planet1.y = 2.0;
    planet1.r = 3.0;

    G::PlanetState planet2;
    planet2.x = 4.0;
    planet2.y = 5.0;
    planet2.r = 6.0;

    universe.galaxy_.push_back(planet1);
    universe.galaxy_.push_back(planet2);

    double distance_squared = newton.d_2(planet1, planet2);
    double sum_of_radii_squared = newton.r_2(planet1, planet2);

    if (distance_squared <= sum_of_radii_squared) {
        // The planets collide
        CHECK(true);
    } else {
        // The planets do not collide
        CHECK(false);
    }
}*/



/*#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "universe.hpp"

TEST_CASE("Testing planet collision verification in Universe") {
    U::Newton newton;
    U::Universe universe(newton);

    // Inserisci i dati dei pianeti
    G::PlanetState planet1;
    planet1.x = 0.0;
    planet1.y = 0.0;
    planet1.r = 2.0;
    universe.galaxy_.push_back(planet1);

    G::PlanetState planet2;
    planet2.x = 6.0;
    planet2.y = 0.0;
    planet2.r = 3.0;
    universe.galaxy_.push_back(planet2);

    // Verifica manuale del risultato
    double distance_squared = newton.d_2(planet1, planet2);
    double sum_of_radii_squared = newton.r_2(planet1, planet2);
    bool expected_collision = (distance_squared <= sum_of_radii_squared);

    // Esegui il calcolo nel programma e confronta con il risultato atteso
    bool actual_collision = (distance_squared <= sum_of_radii_squared);

    CHECK(actual_collision == expected_collision);
}*/

