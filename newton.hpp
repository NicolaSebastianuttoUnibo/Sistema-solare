#ifndef FORZA_G_HPP
#define FORZA_G_HPP
#include <SFML/Graphics.hpp>
#include <string>

namespace G {

struct PlanetState {
  double m{};    // mass 1u=10^27kg
  double x{};    // pos_x 1 pixel=1 million of chilometer
  double y{};    // pos_y
  double v_x{};  // vel x
  double v_y{};  // vel y
  double r{};
  std::string stringtexture{};
  sf::Texture* texture{};

  bool operator==(const PlanetState& a) const;
};

};  // namespace G

#endif