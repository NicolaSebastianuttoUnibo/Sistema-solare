
#include "universe.hpp"


#include <algorithm>
#include <cassert>
#include <numeric>


U::Universe::Universe(U::Newton const &newton) : newton_{newton} {}
int U::Universe::size() const { return importantplanet_.size(); }


void U::Universe::push_back(G::PlanetState const &ps) { galaxy_.push_back(ps); }


void U::Universe::remove(G::PlanetState const &ps) {
 auto it = std::find(galaxy_.begin(), galaxy_.end(), ps);
  assert(it!=galaxy_.end());


  if (it != galaxy_.end()) {
   galaxy_.erase(it);
 }
}
void U::Universe::findimportantplanet() {
 for (auto it = galaxy_.begin(); it < galaxy_.end(); ++it) {
   for (auto jt = galaxy_.begin(); jt < galaxy_.end(); ++jt) {


     double ax = newton_.G_ * (*jt).m / (((*it).r + (*jt).r) * ((*it).r + (*jt).r));
     double ay = newton_.G_ * (*jt).m / (((*it).r + (*jt).r) * ((*it).r + (*jt).r));
     if (ax * ax + ay * ay > 1&&it!=jt) {
       importantplanet_.push_back(*it);
       importantplanet_.push_back(*jt);
     }
   }
 }
}
std::vector<G::PlanetState> const &U::Universe::state() const {
 return galaxy_;
}


void U::Universe::evolve(double delta_t) {
 findimportantplanet();
 copy_=galaxy_;
 assert(copy_.size()==galaxy_.size());
  assert(galaxy_.size()!=0);


 for (auto it=importantplanet_.begin(); it<importantplanet_.end(); it+=2){
  // if(it+1<importantplanet_.end()){
 
 auto jt = std::find(copy_.begin(), copy_.end(), *it);
  assert(jt!=copy_.end());
   int idx=std::distance(copy_.begin(),jt);
   newton_(*it,*(it+1));
double fx = newton_.f_x;
double fy = newton_.f_y;


   galaxy_[idx]=solve(*(it),fx,fy,delta_t);




  // }
 }
 }
G::PlanetState U::Universe::solve(G::PlanetState const &ps, double fx,
                                 double fy, double delta_t) const {
 double ax = fx / ps.m;


 double vx = ps.v_x + ax * delta_t;


 double x = ps.x + ps.v_x * delta_t + 0.5 * ax * delta_t * delta_t;


 double ay = fy / ps.m;
 double vy = ps.v_y + ay * delta_t;
 double y = ps.y + ps.v_y * delta_t + 0.5 * ay * delta_t * delta_t;


 G::PlanetState r{ps.m, x, y, vx, vy};
return r;
}


