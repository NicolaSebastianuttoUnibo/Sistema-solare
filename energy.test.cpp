#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "universe.hpp"

TEST_CASE("Testing conservation of energy") {
    SUBCASE("First test"){
    U::Newton newton;
    U::Universe universe(newton);

    // Aggiungi i pianeti all'universo
    // ...
G::PlanetState p1;
p1.x=0;
p1.y=0;
p1.r=3;
p1.v_x = 12;
p1.v_y = 12;
p1.m = 32;
universe.push_back(p1);



G::PlanetState p2;
p2.x=12;
p2.y=12;
p2.r=5;
p2.v_x = 155555;
p2.v_y = 1222;
p2.m = 3200000000;
universe.push_back(p2);
    // Calcola l'energia iniziale
    double initial_energy = universe.calculateenergy();

    // Evolvi l'universo
    universe.evolve(1.0); // Supponiamo un passo di tempo di 1.0

    // Calcola l'energia finale
    double final_energy = universe.calculateenergy();

    // Verifica la conservazione dell'energia
    CHECK(initial_energy == doctest::Approx(final_energy));}
}
/*#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "universe.hpp"

TEST_CASE("Testing conservation of energy") {
    SUBCASE("First test") {
        U::Newton newton;
        U::Universe universe(newton);

        G::PlanetState p1;
        p1.v_x = 12;
        p1.v_y = 12;
        p1.m = 32;
        universe.push_back(p1);

        G::PlanetState p2;
        p2.v_x = 12;
        p2.v_y = 12;
        p2.m = 32;
        universe.push_back(p2);

        // Calcola l'energia iniziale
        double initial_energy = universe.calculateenergy();

        // Evolvi l'universo
        universe.evolve(1.0); // Supponiamo un passo di tempo di 1.0

        // Calcola l'energia finale
        double final_energy = universe.calculateenergy();

        // Verifica la conservazione dell'energia
        CHECK(initial_energy == doctest::Approx(final_energy));

        // Verifica che i pianeti non collidano e che le condizioni post-collisione siano rispettate
        for (auto it = universe.galaxy_.begin(); it != universe.galaxy_.end(); ++it) {
            for (auto jt = it + 1; jt != universe.galaxy_.end(); ++jt) {
                if (newton.d_2(*it, *jt) <= newton.r_2(*it, *jt)) {
                    // Condizioni post-collisione
                    double M = it->m + jt->m;
                    double X = (it->m * it->x + jt->m * jt->x) / M;
                    double Y = (it->m * it->y + jt->m * jt->y) / M;
                    double VX = (it->m * it->v_x + jt->m * jt->v_x) / M;
                    double VY = (it->m * it->v_y + jt->m * jt->v_y) / M;
                    double R = std::sqrt(it->r * it->r + jt->r * jt->r);

                    CHECK(X == doctest::Approx((*it).x).epsilon(1e-6));
                    CHECK(Y == doctest::Approx((*it).y).epsilon(1e-6));
                    CHECK(VX == doctest::Approx((*it).v_x).epsilon(1e-6));
                    CHECK(VY == doctest::Approx((*it).v_y).epsilon(1e-6));
                    CHECK(R == doctest::Approx(it->r).epsilon(1e-6));
                }
            }
        }
    }
}*/






/*#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "universe.hpp"

TEST_CASE("Testing conservation of energy") {
    SUBCASE("First test") {
        U::Newton newton;
        U::Universe universe(newton);

        G::PlanetState p1;
        p1.v_x = 12;
        p1.v_y = 12;
        p1.m = 32;
        universe.push_back(p1);

        G::PlanetState p2;
        p2.v_x = 12;
        p2.v_y = 12;
        p2.m = 32;
        universe.push_back(p2);

        // Calcola l'energia iniziale
        double initial_energy = universe.calculateenergy();

        // Evolvi l'universo
        universe.evolve(1.0); // Supponiamo un passo di tempo di 1.0

        // Calcola l'energia finale
        double final_energy = universe.calculateenergy();

        // Verifica la conservazione dell'energia
        CHECK(initial_energy == doctest::Approx(final_energy));
        
        // Verifica che i pianeti non collidano
        for (const auto& planet : universe.galaxy_) {
            CHECK(planet.m >= 0);
        }
    }
}
*/
