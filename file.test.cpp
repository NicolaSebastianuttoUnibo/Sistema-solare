#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN



#include "doctest.h"
#include "universe.hpp"
#include "Graphic.hpp"
TEST_CASE("Testing the class handling a floating point data sample") {

SUBCASE("Fileuniverse") {
   U::Newton n{};
   U::FileUniverse u(n, "test",true);
   gr::TM tm("Texture", &u);


 CHECK(u.state()[0].m == doctest::Approx(500));
 CHECK(u.state()[1].m == doctest::Approx(20));
 CHECK(u.state()[2].m == doctest::Approx(5));
 CHECK(u.state()[3].m == doctest::Approx(87));

  CHECK(u.state()[0].x == doctest::Approx(100));
 CHECK(u.state()[1].x == doctest::Approx(-300));
 CHECK(u.state()[2].x == doctest::Approx(500));
 CHECK(u.state()[3].x == doctest::Approx(700));

   CHECK(u.state()[0].y == doctest::Approx(200));
 CHECK(u.state()[1].y == doctest::Approx(0));
 CHECK(u.state()[2].y == doctest::Approx(-200));
 CHECK(u.state()[3].y == doctest::Approx(80));

    CHECK(u.state()[0].v_x == doctest::Approx(0.01));
 CHECK(u.state()[1].v_x == doctest::Approx(0.01));
 CHECK(u.state()[2].v_x == doctest::Approx(0.01));
 CHECK(u.state()[3].v_x == doctest::Approx(0.01));

     CHECK(u.state()[0].v_y == doctest::Approx(0.02));
 CHECK(u.state()[1].v_y == doctest::Approx(0.02));
 CHECK(u.state()[2].v_y == doctest::Approx(0.02));
 CHECK(u.state()[3].v_y == doctest::Approx(0.02));

      CHECK(u.state()[0].r == doctest::Approx(10));
 CHECK(u.state()[1].r == doctest::Approx(2));
 CHECK(u.state()[2].r == doctest::Approx(8));
 CHECK(u.state()[3].r == doctest::Approx(20));



 }


}