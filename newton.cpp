#include <cassert>
#include <cmath>

#include "universe.hpp"

void U::Newton::operator()(const G::PlanetState& a, const G::PlanetState& b) {
  double distance{d_2(a, b)};
  double f = G_ * a.m * b.m / (distance);

  if (distance == 0) {
    f_x = 0;
    f_y = 0;
    return;
  }
  f_x = f * (b.x - a.x) / std::sqrt(distance);
  f_y = f * (b.y - a.y) / std::sqrt(distance);
}

/// DISTANCE SQUARED
double U::Newton::d_2(G::PlanetState const& a, G::PlanetState const& b) {
  double r = (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
  assert(r >= 0);
  return r;
}
/// MINIMUM DISTANCE SQUARED
double U::Newton::r_2(G::PlanetState const& a, G::PlanetState const& b) {
  double r = (a.r + b.r) * (a.r + b.r);
  assert(r >= 0);
  return r;
}

bool G::PlanetState::operator==(const PlanetState& a) const {
  return m == a.m && x == a.x && y == a.y && v_x == a.v_x && v_y == a.v_y &&
         r == a.r;
}
