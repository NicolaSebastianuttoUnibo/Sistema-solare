#ifndef FORZA_G_HPP
#define FORZA_G_HPP
#include <string>
#include <SFML/Graphics.hpp>


namespace G {


struct PlanetState {
 double m{};    // mass
 long double x{};    // pos_x 1x=1000km (espresssa in megametri 10^6 m)
 long double y{};    // pos_y
 long double v_x{};  // vel x
 long double v_y{};  // vel y
 double r{};
 std::string stringtexture{};
 sf::Texture *texture{};


void setPlanetTexture( std::string texturePath, sf::Texture* pointer);


bool operator==(const PlanetState& a)const{
  return m==a.m&&x==a.x&&y==a.y&&v_x==a.v_x&&v_y==a.v_y&&r==a.r;
}
};


 private:
  double G_{6.67430e-29};  /// costante G (MN*Mm^2/kg^2) our G = usual G*10^-18
};  // namespace G

#endif