#include "universe.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <numeric>

U::Universe::Universe(G::Newton const &newton) : newton_{newton} {}
unsigned int U::Universe::size() const { return galaxy_.size(); }

void U::Universe::push_back(G::PlanetState const &ps) { galaxy_.push_back(ps); }

void U::Universe::remove(G::PlanetState const &ps) {
  auto it = std::find(galaxy_.begin(), galaxy_.end(), ps);
  if (it != galaxy_.end()) {
    galaxy_.erase(it);
  }
}

G::PlanetState &U::Universe::operator[](unsigned int index) {
  assert(index < galaxy_.size());
  return galaxy_[index];
}
const G::PlanetState &U::Universe::operator[](unsigned int index) const {
  assert(index < galaxy_.size());
  return galaxy_[index];
}

void U::Universe::evolve(double delta_t) {
  assert(galaxy_.size() >= 1);
  copy_ = galaxy_;
  assert(copy_.size() == galaxy_.size());
  for (auto it = copy_.begin(); it < copy_.end(); ++it) {
    int idx = std::distance(copy_.begin(), it);

    std::pair<long double, long double> forza =
        std::accumulate(copy_.begin(), copy_.end(), std::make_pair(0.0, 0.0),
                        [this, it](std::pair<long double, long double> sums,
                                   const G::PlanetState &ci) {
                          newton_(*it, ci);
                          sums.first += newton_.f_x;
                          sums.second += newton_.f_y;
                          return sums;
                        });

    galaxy_[idx] = solve(*it, forza.first, forza.second, delta_t);
  }
  // galaxy_[0].x+=1000;
}

std::vector<G::PlanetState> const &U::Universe::state() const {
  return galaxy_;
}
G::PlanetState U::Universe::solve(G::PlanetState const &ps, long double fx,
                                  long double fy, double delta_t) const {
  long double ax = fx / ps.m;
  long double vx = ps.v_x + ax * delta_t;
  long double x = ps.x + ps.v_x * delta_t + 0.5 * ax * delta_t * delta_t;

  long double ay = fy / ps.m;
  long double vy = ps.v_y + ay * delta_t;
  long double y = ps.y + ps.v_y * delta_t + 0.5 * ay * delta_t * delta_t;

  G::PlanetState r{ps.m, x, y, vx, vy, ps.r, ps.stringtexture, ps.texture};
  return r;
}

int U::Universe::findNearestPlanet(sf::Vector2i point) {
  auto compareDistance = [&point](const G::PlanetState &planet1,
                                  const G::PlanetState &planet2) {
    float distance1 = std::hypot(planet1.x - point.x, planet1.y - point.y);
    float distance2 = std::hypot(planet2.x - point.x, planet2.y - point.y);
    return distance1 < distance2;
  };

  auto nearestPlanetIterator =
      std::min_element(galaxy_.begin(), galaxy_.end(), compareDistance);

  if (nearestPlanetIterator != galaxy_.end()) {
    int nearestIndex =
        static_cast<int>(std::distance(galaxy_.begin(), nearestPlanetIterator));
    return nearestIndex;
  } else {
    return -1;  // Nessun pianeta nel vettore
  }
}
