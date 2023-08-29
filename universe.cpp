
#include "universe.hpp"
#include <cmath>


#include <algorithm>
#include <cassert>
#include <numeric>
#include <iostream>
#include <iomanip>








U::Universe::Universe(U::Newton const &newton) : newton_{newton} {}
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
  check_Collision();
  assert(copy_.size() == galaxy_.size());
  for (auto it = copy_.begin(); it < copy_.end(); ++it) {
    int idx = std::distance(copy_.begin(), it);

    std::pair< double,  double> forza =
        std::accumulate(copy_.begin(), copy_.end(), std::make_pair(0.0, 0.0),
                        [this, it](std::pair< double,  double> sums,
                                   const G::PlanetState &ci) {
                          newton_(*it, ci);
                          sums.first += newton_.f_x;
                          sums.second += newton_.f_y;
                          return sums;
                        });


    galaxy_[idx] = solve(*it, forza.first, forza.second, delta_t);
  }
}

std::vector<G::PlanetState> const &U::Universe::state() const {
  return galaxy_;
}
G::PlanetState U::Universe::solve(G::PlanetState const &ps,  double fx,
                                   double fy, double delta_t) const {
   double ax = fx / ps.m;
   double vx = ps.v_x + ax * delta_t;
   double x = ps.x + ps.v_x * delta_t + 0.5 * ax * delta_t * delta_t;

   double ay = fy / ps.m;
   double vy = ps.v_y + ay * delta_t;
   double y = ps.y + ps.v_y * delta_t + 0.5 * ay * delta_t * delta_t;

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

void U::Universe::check_Collision(){
  for (auto it = copy_.begin(); it < copy_.end()-1; ++it) {
  for (auto jt = it+1; jt < copy_.end(); ++jt){

if (newton_.d_2((*it),(*jt))<=newton_.r_2 ((*it),(*jt))){
double M = ((*it).m+(*jt).m);
double X = ((*it).m*(*it).x+(*jt).m*(*jt).x);
double Y = ((*it).m*(*it).y+(*jt).m*(*jt).y);
double VX=  (((*it).m*(*it).v_x)  + ((*jt).m*(*jt).v_x));
double VY = (((*it).m*(*it).v_y)  + ((*jt).m*(*jt).v_y));
  double R{std::hypot((*it).r,(*jt).r)};


G::PlanetState p{M,X/M, Y/M, VX/M, VY/M, R, (  ((*it).m > (*jt).m) ? (*it).stringtexture : (*jt).stringtexture), (  ((*it).m > (*jt).m) ? (*it).texture : (*jt).texture)};
//G::PlanetState p{0,0,0,0,0,0};
 calculateenergy();
 double before=total_energy_;
unsigned int s = copy_.size();



auto kt = std::find(copy_.begin(), copy_.end(), (*it));
 assert(kt!=copy_.end());
    copy_.erase(kt);


// copy_=galaxy_;
auto lt = std::find(copy_.begin(), copy_.end(), (*jt));
 assert(lt!=copy_.end());
    copy_.erase(lt);

 copy_.push_back(p);

 assert (copy_.size()==s-1);
assert(copy_.size()>0);
 calculateenergy();
 double after=total_energy_;

assert(true==false);
 assert(before>=after);
mechanic_energy_ = after;
lost_energy_ = before - after;
total_energy_ = before;

 galaxy_=copy_;
goto end;
  }
}
}
end:

return;
}



void  U::Universe::calculateenergy(){
 cinetic_energy_= std::accumulate (galaxy_.begin(), galaxy_.end(),0,[](double r, const G::PlanetState &gi){ 

   r+=(1e5*0.5*(gi).m*std::hypot(gi.v_x,gi.v_y)*std::hypot(gi.v_x,gi.v_y));
   return r;
   });

    potential_energy_ = -std::accumulate(galaxy_.begin(), galaxy_.end(), 0, [this](double r, const G::PlanetState &gi) {
    r += (std::accumulate(galaxy_.begin(), galaxy_.end(), 0, [this, gi](double s, const G::PlanetState &hi) {
        if (!(gi == hi)) {
            s += (1e5*newton_.G_ * gi.m * hi.m / (newton_.d_2(gi, hi)));
        }
        return s;
    }));
    return r;
});
mechanic_energy_=cinetic_energy_+potential_energy_;
total_energy_=lost_energy_+mechanic_energy_;
}