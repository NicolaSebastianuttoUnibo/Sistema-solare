#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "universe.hpp"

#include "doctest.h"
#include <string>
#include <string>
TEST_CASE("Testing the class handling a floating point data sample")
{

  SUBCASE("First Newton")
  {

    G::Newton newton{};

    G::PlanetState p1{10, 0, 0, 0, 0};
    G::PlanetState p2{1e6, 100, 0, 0, 0};

    newton(p1, p2);
    CHECK(newton.f_x == doctest::Approx(6.67430e-7));

    newton(p2, p1);
    CHECK(newton.f_x == doctest::Approx(-6.67430e-7));
  }
  SUBCASE("Second Newton")
  {
    G::Newton newton{};

    G::PlanetState p1{35, 100, 100, 0, 0};
    G::PlanetState p2{674938, 30100, 30100, 0, 0};
    newton(p1, p2);
    CHECK(newton.f_x == doctest::Approx(1.75184283e-12));
    CHECK(newton.f_y == doctest::Approx(1.75184283e-12));
    newton(p2, p1);
    CHECK(newton.f_x == doctest::Approx(-1.75184283e-12));
    CHECK(newton.f_y == doctest::Approx(-1.75184283e-12));
  }

  SUBCASE("First Universe")
  {
    G::Newton n{};
    U::Universe u(n);
    G::PlanetState p1{35, 100, 100, 0, 0};
    G::PlanetState p2{674938, 30100, 30100, 0, 0};
    u.push_back(p1); u.push_back(p2);


//std::vector<G::PlanetState> uu=u.state;
  

    CHECK(u.state()[0].m == doctest::Approx(35));
    CHECK(u.state()[1].m == doctest::Approx(674938));
    CHECK(u.state()[0].x == doctest::Approx(100));
    CHECK(u.state()[1].x == doctest::Approx(30100));
    CHECK(u.state()[0].y == doctest::Approx(100));
    CHECK(u.state()[1].y == doctest::Approx(30100));
    CHECK(u.state()[0].v_x== doctest::Approx(0));
    CHECK(u.state()[1].v_x == doctest::Approx(0));
    CHECK(u.state()[0].v_y== doctest::Approx(0));
    CHECK(u.state()[1].v_y == doctest::Approx(0));
    
    u.evolve(1);
    }

  SUBCASE("First Universe")
  {
    G::Newton n{};
    U::Universe u(n);
    G::PlanetState p1{5e24,5,10,20,20};
    G::PlanetState p2{7e27,30,50,5,15};
    u.push_back(p1); u.push_back(p2);


//std::vector<G::PlanetState> uu=u.state;
  
    u.evolve(1);

    CHECK(u.state()[0].v_x == doctest::Approx(35));
   
    
    }

}