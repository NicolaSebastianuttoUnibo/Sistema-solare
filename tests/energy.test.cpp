#include "doctest.h"
#include "../universe.hpp"

TEST_CASE("Testing conservation of energy") {
    SUBCASE("First test"){

    U::Newton newton;
    U::Universe universe(newton);

    
G::PlanetState p1{100,0,3,12,12,32};
universe.push_back(p1);



G::PlanetState p2{12,12,5,1212,213,6e4};
universe.push_back(p2);
   
    universe.calculateenergy();
    double initial_energy = universe.total_energy_;

   for(int i=0;i<1e5;i++){
    universe.evolve(0.01);
   }
 universe.calculateenergy();

    double final_energy = universe.total_energy_;
    CHECK(initial_energy == doctest::Approx(final_energy));}


    SUBCASE("Second test"){

    U::Newton newton;
    U::Universe universe(newton);

    
G::PlanetState p1{36,367,278,37,1,0};
universe.push_back(p1);


G::PlanetState p2{10,29,28,-12,-21,12};
universe.push_back(p2);
   
    universe.calculateenergy();
    double initial_energy = universe.total_energy_;

   for(int i=0;i<1e5;i++){
    universe.evolve(0.01);
   }
 universe.calculateenergy();

    double final_energy = universe.total_energy_;
    CHECK(initial_energy == doctest::Approx(final_energy));}


}
