#ifndef FORZA_G_HPP
#define FORZA_G_HPP
#include <string>
#include <SFML/Graphics.hpp>

#include <mpfr.h>
namespace G {


struct PlanetState {
  double m{};    // mass
  double x{};    // pos_x 1x=1000km (espresssa in megametri 10^6 m)
  double y{};    // pos_y
  double v_x{};  // vel x
  double v_y{};  // vel y
 double r{};
 std::string stringtexture{};
 sf::Texture *texture{};


void setPlanetTexture( std::string texturePath, sf::Texture* pointer);


bool operator==(const PlanetState& a)const{
  return m==a.m&&x==a.x&&y==a.y&&v_x==a.v_x&&v_y==a.v_y&&r==a.r;
}



 

};

};  // namespace G

#endif