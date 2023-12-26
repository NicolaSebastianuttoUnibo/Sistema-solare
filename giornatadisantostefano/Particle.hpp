#ifndef PARTICLE_HPP
#define PARTICLE_HPP


#include "ResonanceType.hpp"
#include <array>
#include <vector>
#include <iostream>
#include <cmath>
#include <cstdlib>




class Particle{
static const int fMaxNumParticleType{10};
 static int findParticle(ParticleType* rt);





static std::vector<ParticleType*>* lochifo;



static int fNParticleType;
 
double fPx;
double fPy;
double fPz;

void Boost(double bx, double by, double bz);

public:
int fIndex=0; 
 static std::vector<ParticleType*> fParticleType;
std::vector<ParticleType*>   pfs(){ 
   
    return *lochifo;
}

Particle(const char* name, double px=0, double py=0, double pz=0);
Particle() = default;

 void Setter(const int index);
void Setter(const char* name);

 static void PrintAll();
 static int o() { return fParticleType.size();}
void PrintParticle();

int GetfIndex();
 static void AddParticleType (const char* name, const double mass, const int charge, const double width );
void SetfIndex(int);

double GetPx();
double GetPy();
double GetPz();
double GetMassParticle() const;
double GetImpulse();
double GetEnergy() const;
double InvMass(Particle &p);
void SetP(double,double,double);

int Decay2body(Particle &dau1,Particle &dau2) const;
};

#endif
