#ifndef FORZA_G_HPP
#define FORZA_G_HPP
#include <string>
namespace G {

struct PlanetState {
  double m{};    // mass
  double x{};    // pos_x 1x=1000km (espresssa in megametri 10^6 m)
  double y{};    // pos_y
  double v_x{};  // vel x
  double v_y{};  // vel y
  double r{};
  std::string texture{};
};

struct Newton {
  // la forza è espressa in megaNewton (10^6)N
  double f_x{};  // force x
  double f_y{};  // force y
  void operator()(PlanetState const& a, PlanetState const& b);

 private:
  double G_{6.67430e-29};  /// costante G (MN*Mm^2/kg^2) our G = usual G*10^-18
};

}  // namespace G

#endif