

/// check raggio e distanza al quadrato della struct Newton
/// check forza gravitazionale tra due pianeti
/// check evolve
/// check nearestPlanet
/// check file
/// check rimozione pianeta
////check energia che rimane costante

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <string>

#include "doctest.h"
#include "universe.hpp"
TEST_CASE("Testing the class handling a floating point data sample") {
  SUBCASE("First Newton") {
    U::Newton newton{};

    G::PlanetState p1{1e+10, 0, 0, 0, 0};
    G::PlanetState p2{1e+12, 200, 100, 0};
    newton(p1, p2);

    CHECK(newton.f_x == doctest::Approx(2.16e+14));
    CHECK(newton.f_y == doctest::Approx(8.65e+14));

    G::PlanetState p3{1e10, 0, 0, 0, 0};
    G::PlanetState p4{1e12, 100, 200, 0, 0};
    newton(p4, p3);

    CHECK(newton.f_x == doctest::Approx(-7.69e-5));
    CHECK(newton.f_y == doctest::Approx(-1.54e-4));

    //////////////////

    G::PlanetState p5{1e10, 0, 0, 0, 0};
    G::PlanetState p6{1e12, -200, 100, 0, 0};
    newton(p5, p6);

    CHECK(newton.f_x == doctest::Approx(-1.54e-4));
    CHECK(newton.f_y == doctest::Approx(7.69e-5));

    G::PlanetState p7{1e10, 0, 0, 0, 0};
    G::PlanetState p8{1e12, -100, 200, 0, 0};
    newton(p7, p8);

    CHECK(newton.f_x == doctest::Approx(-7.69e-5));
    CHECK(newton.f_y == doctest::Approx(1.54e-4));
    //////
    G::PlanetState p9{1e10, 0, 0, 0, 0};
    G::PlanetState p10{1e12, 200, -100, 0, 0};
    newton(p9, p10);

    CHECK(newton.f_x == doctest::Approx(1.54e-4));
    CHECK(newton.f_y == doctest::Approx(-7.69e-5));

    G::PlanetState p11{1e10, 0, 0, 0, 0};
    G::PlanetState p12{1e12, 100, -200, 0, 0};
    newton(p11, p12);

    CHECK(newton.f_x == doctest::Approx(7.69e-5));
    CHECK(newton.f_y == doctest::Approx(-1.54e-4));
    ///////
    G::PlanetState p13{1e10, 0, 0, 0, 0};
    G::PlanetState p14{1e12, -200, -100, 0, 0};
    newton(p13, p14);

    CHECK(newton.f_x == doctest::Approx(-1.54e-4));
    CHECK(newton.f_y == doctest::Approx(-7.69e-5));

    G::PlanetState p15{1e10, 0, 0, 0, 0};
    G::PlanetState p16{1e12, -100, -200, 0, 0};
    newton(p15, p16);

    CHECK(newton.f_x == doctest::Approx(-7.69e-5));
    CHECK(newton.f_y == doctest::Approx(-1.54e-4));
  }

  SUBCASE("First Universe") {
    U::Newton n{};
    U::Universe u(n);
    G::PlanetState p1{35, 100, 100, 0, 0};
    G::PlanetState p2{674938, 30100, 30100, 0, 0};
    u.push_back(p1);
    u.push_back(p2);

    CHECK(u.state()[0].m == doctest::Approx(35));
    CHECK(u.state()[1].m == doctest::Approx(674938));
    CHECK(u.state()[0].x == doctest::Approx(100));
    CHECK(u.state()[1].x == doctest::Approx(30100));
    CHECK(u.state()[0].y == doctest::Approx(100));
    CHECK(u.state()[1].y == doctest::Approx(30100));
    CHECK(u.state()[0].v_x == doctest::Approx(0));
    CHECK(u.state()[1].v_x == doctest::Approx(0));
    CHECK(u.state()[0].v_y == doctest::Approx(0));
    CHECK(u.state()[1].v_y == doctest::Approx(0));

    u.findimportantplanet();

    u.evolve(1);
  }

  SUBCASE("Second Universe") {
    U::Newton n{};
    U::Universe u(n);
    G::PlanetState p1{6e25, 100, 100, 0, -100};
    G::PlanetState p2{6e26, 50, 50, 0, 0};
    u.push_back(p1);
    u.push_back(p2);

    n(p1, p2);
    // std::vector<G::PlanetState> uu=u.state;
    CHECK(n.f_x == doctest::Approx(-4.40381e27));
    CHECK(n.f_y == doctest::Approx(-4.40381e27));
    u.findimportantplanet();
    u.evolve(1);

    CHECK(u.state()[0].v_x == doctest::Approx(-73.3968));
    CHECK(u.state()[0].v_y == doctest::Approx(-173.3968));
    CHECK(u.state()[1].v_x == doctest::Approx(7.33968));
    CHECK(u.state()[1].v_y == doctest::Approx(7.33968));

    CHECK(u.state()[0].x == doctest::Approx(63.3016));

    CHECK(u.state()[0].y == doctest::Approx(63.3016 - 100));

    CHECK(u.state()[1].x == doctest::Approx(53.6698));
    CHECK(u.state()[1].y == doctest::Approx(53.6698));
  }

  SUBCASE("Third Universe") {
    U::Newton n{};
    U::Universe u(n);
    G::PlanetState p1{1e10, 0, 0, 0, 0, 50};
    G::PlanetState p2{1, 100, 0, 0, 0, 1};
    u.push_back(p1);
    u.push_back(p2);
    n(p1, p2);
    CHECK(n.f_x == doctest::Approx(-8.64e-16));
    CHECK(n.f_y == doctest::Approx(0));
    u.findimportantplanet();
    u.evolve(0.1);
    CHECK(u.state()[0].v_x == doctest::Approx(0));
    CHECK(u.state()[0].v_y == doctest::Approx(0));
    CHECK(u.state()[1].v_x == doctest::Approx(0));
    CHECK(u.state()[1].v_y == doctest::Approx(0));

    CHECK(u[0].x == doctest::Approx(3.33e-35));
    CHECK(u.state()[0].y == doctest::Approx(0));
    CHECK(u.state()[1].x == doctest::Approx(100 - 3.33e-25));
    CHECK(u.state()[1].y == doctest::Approx(0));
  }
  SUBCASE("Fourth Universe") {
    U::Newton n{};
    U::FileUniverse u(n, "esempio", false);
    G::PlanetState p1{1e10, 0, 0, 0, 0};
    G::PlanetState p2{1, 100, 0, 0, 0};
  }
}
/*TEST_CASE("Testing distance calculation") {
    G::PlanetState planet1;
    planet1.x = 0;
    planet1.y = 0;

    G::PlanetState planet2;
    planet2.x = 3;
    planet2.y = 4;

    U::Newton newton;
    
    SUBCASE("Check distance calculation") {
        double calculated_distance = newton.d_2(planet1, planet2);
        double expected_distance = 5.0; // sqrt(3^2 + 4^2) = 5.0
        
        CHECK(calculated_distance == doctest::Approx(expected_distance));
    }
}*/
