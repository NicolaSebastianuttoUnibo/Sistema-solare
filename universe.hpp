#ifndef UNIVERSE_HPP
#define UNIVERSE_HPP
#include <string>
#include <vector>

#include "newton.hpp"
namespace U {
class Universe {
  G::Newton newton_;
  std::vector<G::PlanetState> copy_;
  G::PlanetState solve(G::PlanetState const &ps, long double fx, long double fy,
                       double delta_t) const;

 public:
  std::vector<G::PlanetState> galaxy_;

  Universe(G::Newton const &newton);
  void push_back(G::PlanetState const &ps);
  unsigned int size() const;
  void evolve(double delta_t);
  void remove(G::PlanetState const &ps);

  std::vector<G::PlanetState> const &state() const;

  int findNearestPlanet(sf::Vector2i point);

  G::PlanetState &operator[](unsigned int index);
  const G::PlanetState &operator[](unsigned int index) const;
};

class FileUniverse : public Universe {
  std::string file_;
  bool isValidFile(const std::string &filename);
  unsigned int countPlanets(const std::string &filename);
  std::vector<G::PlanetState> copy_;

 public:
  FileUniverse(G::Newton const &newton, std::string str, bool a);
  void push_back(G::PlanetState const &ps);
  void remove(G::PlanetState const &ps);
  void save();
  void download();
};

}  // namespace U
#endif
