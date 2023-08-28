#include "universe.hpp"

#include <cmath>
#include <cassert>



void U::Newton::operator()(const G::PlanetState& a, const G::PlanetState& b) {
double distance{d_2(a,b)};
double f = G_ * a.m * b.m / (distance);


if (distance == 0) {
  f_x = 0;
  f_y = 0;
  return;
}
f_x = f * (b.x - a.x) / std::sqrt(distance);
f_y = f * (b.y - a.y) / std::sqrt(distance);
}

double U::Newton::d_2(G::PlanetState const& a, G::PlanetState const& b){
  double  r = (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
  assert (r>=0);
  return r;
  
}

double U::Newton::r_2(G::PlanetState const& a, G::PlanetState const& b){
  double r = (a.r + b.r) * (a.r + b.r);
  assert (r>=0);
  return r;
}


void G::PlanetState::setPlanetTexture( std::string texturePath, sf::Texture* pointer) {
         stringtexture = texturePath;
         texture = pointer;
       if(pointer==nullptr){
   throw std::runtime_error("nullpointer");}


     
  }












