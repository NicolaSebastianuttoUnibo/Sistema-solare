#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "forzaG.hpp"


#include "doctest.h"
#include <string>
#include <string>
TEST_CASE("Testing the class handling a floating point data sample") {

    


  SUBCASE("First Newton") {

G::Newton newton{};

G::PlanetState p1{10,0,0,0,0};
G::PlanetState p2{1e6,100,0,0,0};


 newton(p1,p2);
    CHECK(newton.f_x==doctest::Approx(6.67430e-7));

newton(p2,p1);
    CHECK(newton.f_x==doctest::Approx(-6.67430e-7));
    
  }
SUBCASE("Second Newton") {
    G::Newton newton{};

  G::PlanetState p1{35,100,100,0,0};
G::PlanetState p2{674938,30100,30100,0,0};
newton(p1,p2);
   CHECK(newton.f_x==doctest::Approx(1.75184283e-12));
   CHECK(newton.f_y==doctest::Approx(1.75184283e-12));
   newton(p2,p1);
   CHECK(newton.f_x==doctest::Approx(-1.75184283e-12));
   CHECK(newton.f_y==doctest::Approx(-1.75184283e-12));
}
   


}