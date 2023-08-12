#ifndef UNIVERSE_HPP
#define UNIVERSE_HPP
#include <vector>

#include "newton.hpp"
namespace U {
class Universe {
  G::Newton newton_;
  std::vector<G::PlanetState> galaxy_;
  std::vector<G::PlanetState> copy_;
  G::PlanetState solve(G::PlanetState const &ps, double fx, double fy,
                       double delta_t) const;

 public:
  Universe(G::Newton const &newton);
  void push_back(G::PlanetState const &ps);
  int size() const;
  void evolve(double delta_t);
  std::vector<G::PlanetState> const &state() const;
};
}  // namespace U
#endif
