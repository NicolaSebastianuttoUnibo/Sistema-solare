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

    G::PlanetState p1{1e10, 0, 0, 0, 0};
    G::PlanetState p2{1e12, 200, 100, 0, 0};
    newton(p1, p2);

    CHECK(newton.f_x == doctest::Approx(11939350));
    CHECK(newton.f_y == doctest::Approx(5969677));

        G::PlanetState p3{1e10, 0, 0, 0, 0};
    G::PlanetState p4{1e12, 100, 200, 0, 0};
    newton(p3, p4);

    CHECK(newton.f_y == doctest::Approx(11939350));
    CHECK(newton.f_x == doctest::Approx(5969677));

//////////////////

        G::PlanetState p5{1e10, 0, 0, 0, 0};
    G::PlanetState p6{1e12, -200, 100, 0, 0};
    newton(p5, p6);

    CHECK(newton.f_x == doctest::Approx(-11939350));
    CHECK(newton.f_y == doctest::Approx(5969677));

        G::PlanetState p7{1e10, 0, 0, 0, 0};
    G::PlanetState p8{1e12, -100, 200, 0, 0};
    newton(p7, p8);

    CHECK(newton.f_y == doctest::Approx(11939350));
    CHECK(newton.f_x == doctest::Approx(-5969677));
//////
    G::PlanetState p9{1e10, 0, 0, 0, 0};
    G::PlanetState p10{1e12, 200, -100, 0, 0};
    newton(p9, p10);

    CHECK(newton.f_x == doctest::Approx(11939350));
    CHECK(newton.f_y == doctest::Approx(-5969677));

        G::PlanetState p11{1e10, 0, 0, 0, 0};
    G::PlanetState p12{1e12, 100, -200, 0, 0};
    newton(p11, p12);

    CHECK(newton.f_y == doctest::Approx(-11939350));
    CHECK(newton.f_x == doctest::Approx(5969677));
///////
    G::PlanetState p13{1e10, 0, 0, 0, 0};
    G::PlanetState p14{1e12, -200, -100, 0, 0};
    newton(p13, p14);

    CHECK(newton.f_x == doctest::Approx(-11939350));
    CHECK(newton.f_y == doctest::Approx(-5969677));

        G::PlanetState p15{1e10, 0, 0, 0, 0};
    G::PlanetState p16{1e12, -100, -200, 0, 0};
    newton(p15, p16);

    CHECK(newton.f_y == doctest::Approx(-11939350));
    CHECK(newton.f_x == doctest::Approx(-5969677));
    

  }

  SUBCASE("First Universe")
  {
    G::Newton n{};
    U::Universe u(n);
    G::PlanetState p1{35, 100, 100, 0, 0};
    G::PlanetState p2{674938, 30100, 30100, 0, 0};
    u.push_back(p1); u.push_back(p2);



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

  SUBCASE("Second Universe")
  {
    G::Newton n{};
    U::Universe u(n);
    G::PlanetState p1{6e25,100,100,0,-100};
    G::PlanetState p2{6e26,50,50,0,0};
    u.push_back(p1); u.push_back(p2);

n(p1,p2);
//std::vector<G::PlanetState> uu=u.state;
    CHECK(n.f_x == doctest::Approx(-3.398e38));
    CHECK(n.f_y == doctest::Approx(-3.398e38)); 
    u.evolve(1);



    CHECK(u.state()[0].v_x == doctest::Approx(-5663331347608));
    CHECK(u.state()[0].v_y == doctest::Approx(-5663331348608));
    CHECK(u.state()[1].v_x == doctest::Approx(566333134761));
    CHECK(u.state()[1].v_y == doctest::Approx(566333134761));


    CHECK(u.state()[0].x == doctest::Approx(-2831665673704));
    CHECK(u.state()[0].y == doctest::Approx(-2831665673804));
 CHECK(u.state()[1].x == doctest::Approx(283166567430));
    CHECK(u.state()[1].y == doctest::Approx(283166567430));

   
    
    }

}