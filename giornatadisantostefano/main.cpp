#include <array>
#include "Particle.hpp"

int main(){
    const char* name1="A";
    const char* name2="B";
    ParticleType* particleArray[2];
    ParticleType part(name1,2.,3);
    ResonanceType reso(name2,4.,5,6.);
    

    particleArray[0] = &part;
    particleArray[1] = &reso;

    for (int i{0}; i < 2; ++i){
       ( *particleArray[i]).Print();
    } 
}












































