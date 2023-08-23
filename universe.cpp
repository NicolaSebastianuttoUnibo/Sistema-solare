#include "universe.hpp"

#include <algorithm>
#include <cassert>
#include <numeric>

U::Universe::Universe(U::Newton const &newton) : newton_{newton} {}
int U::Universe::size() const { return galaxy_.size(); }

void U::Universe::push_back(G::PlanetState const &ps) { galaxy_.push_back(ps); }

void U::Universe::remove(G::PlanetState const &ps) {
  auto it = std::find(galaxy_.begin(), galaxy_.end(), ps);
  if (it != galaxy_.end()) {
    galaxy_.erase(it);
  }
}
void U::Universe::findimportantplanet() {
  for (auto it = galaxy_.begin(); it < galaxy_.end(); ++it) {
    for (auto jt = galaxy_.begin(); jt < galaxy_.end(); ++jt) {
      double ax = newton_.G_ * (*jt).m / (((*it).x - (*jt).x) * ((*it).x - (*jt).x));
      double ay = newton_.G_ * (*jt).m / (((*it).y - (*jt).y) * ((*it).y - (*jt).y));
      if (ax * ax + ay * ay > 1) {
        push_back(*it);
        push_back(*jt);
      }
    }
  }
}
 std::vector<G::PlanetState> const &U::Universe::state() const {
  return galaxy_;
 }

void U::Universe::evolve(double delta_t) {
  copy_=galaxy_;
  assert(copy_.size()==galaxy_.size());
  for (auto it=copy_.begin(); it<copy_.end()-2; it+=2){
    //if(it>=copy.end)
    int idx=std::distance(galaxy_.begin(),it);
    newton_(*it,*(it+1)); 
double fx = newton_.f_x; 
double fy = newton_.f_y; 

    galaxy_[idx]=solve(*(it+1),fx,fy,delta_t);
  }
  }
G::PlanetState U::Universe::solve(G::PlanetState const &ps, double fx,
                                  double fy, double delta_t) const {
  double ax = fx / ps.m; 
  if(ax<100) {
    std::__throw_runtime_error("a<1");
  }
  double vx = ps.v_x + ax * delta_t;
  if(vx<10) {
    std::__throw_runtime_error("v<1");
  }
  double x = ps.x + ps.v_x * delta_t + 0.5 * ax * delta_t * delta_t;

  double ay = fy / ps.m;
  double vy = ps.v_y + ay * delta_t;
  double y = ps.y + ps.v_y * delta_t + 0.5 * ay * delta_t * delta_t;

  G::PlanetState r{ps.m, x, y, vx, vy};
  return r;
}
