#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <string>
#include "doctest.h"
#include "universe.hpp"
TEST_CASE("COLLISIONS") {


SUBCASE("Test in static collisions") {




 U::Newton n{};
 U::Universe u(n);
 G::PlanetState p1{1e10, 0, 0, 0, 0, 0};
 G::PlanetState p2{1e10, 0, 0, 0, 0, 0};
 u.push_back(p1);
 u.push_back(p2);

  CHECK(u.size() == doctest::Approx(2));
u.evolve(0);
CHECK(u.size() == doctest::Approx(1));

 U::Universe universe(n);
 
 G::PlanetState p3{1e10, 1000, 0, 0, 0,50};
 G::PlanetState p4{1e10, 0, 0, 0, 0,50};
 G::PlanetState p5{1e34, 100, 0, 0, 0, 60};
 u.push_back(p3);
 u.push_back(p4);
 u.push_back(p5);



  CHECK(universe.size() == doctest::Approx(2));
  u.evolve(0);
 CHECK(universe.size() == doctest::Approx(1));
 
}

SUBCASE("Testing collision in dinamic collision") {
   
   U::Newton newton;
    U::Universe universe(newton);

    G::PlanetState planet1{10,0,0,1,0,10};
    G::PlanetState planet2{100,200,0,0,0,50};


    universe.galaxy_.push_back(planet1);
    universe.galaxy_.push_back(planet2);

for(int i=0;i<1e5;i++){
    universe.evolve(0.1);
}


    CHECK(1 == doctest::Approx(universe.size()));
    CHECK(110 == doctest::Approx(universe[0].m));
    CHECK(100.49875 == doctest::Approx(universe[0].r));



 

}



}