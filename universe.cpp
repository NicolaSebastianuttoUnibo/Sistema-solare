
#include "universe.hpp"
#include <cmath>


#include <algorithm>
#include <cassert>
#include <numeric>




U::Universe::Universe(U::Newton const &newton) : newton_{newton},initial_energy_{calculateenergy()} {}



unsigned int U::Universe::size() const { return galaxy_.size(); }




void U::Universe::push_back(G::PlanetState const &ps) {
 //assert(galaxy_.size() < galaxy_.capacity());
 galaxy_.push_back(ps); }




void U::Universe::remove(G::PlanetState const &ps) {
auto it = std::find(galaxy_.begin(), galaxy_.end(), ps);
 assert(it!=galaxy_.end());




 if (it != galaxy_.end()) {
  galaxy_.erase(it);
}
}
void U::Universe::findimportantplanet() {
  copy_=galaxy_;
importantplanet_.clear();

for (auto it = copy_.begin(); it < copy_.end(); ++it) {
  for (auto jt = copy_.begin(); jt < copy_.end(); ++jt) {




     double ax = newton_.G_ * (*jt).m / newton_.r_2(*it,*jt);
     double ay = newton_.G_ * (*jt).m / newton_.r_2(*it,*jt);
    if (ax*ax+ay*ay>=0.01&&it!=jt) {
      importantplanet_.push_back(&(*it));
      importantplanet_.push_back(&(*jt));
    }
  }
}
assert(importantplanet_.size()%2==0);
}
std::vector<G::PlanetState> const &U::Universe::state() const {
return galaxy_;
}




void U::Universe::evolve(double delta_t) {
  assert(copy_.size()!=0),
 assert(galaxy_.size()!=0);
 check_Collision();

  assert(galaxy_.size() >= 1);
  copy_ = galaxy_;
  assert(copy_.size() == galaxy_.size());
  // for (auto it = copy_.begin(); it < copy_.end(); ++it) {
  //   int idx = std::distance(copy_.begin(), it);

  //   std::pair<long double, long double> forza =
  //       std::accumulate(copy_.begin(), copy_.end(), std::make_pair(0.0, 0.0),
  //                       [this, it](std::pair<long double, long double> sums,
  //                                  const G::PlanetState &ci) {
  //                         newton_(*it, ci);
  //                         sums.first += newton_.f_x;
  //                         sums.second += newton_.f_y;
  //                         return sums;
  //                       });

 
 if(importantplanet_.size()>0){
 for (auto it=importantplanet_.begin(); it<importantplanet_.end(); it+=2){



auto jt = std::find(copy_.begin(), copy_.end(), *(*it));
auto kt = std::find(copy_.begin(), copy_.end(), *(*(it+1)));

  int idx=std::distance(copy_.begin(),jt);
  newton_(*jt,  *kt);

long double fx = newton_.f_x;
long double fy = newton_.f_y;



 galaxy_[idx]=solve((*jt),fx,fy,delta_t);




}
}
}
G::PlanetState U::Universe::solve(G::PlanetState const &ps,long double fx,
                                long double fy, double delta_t) const {

//assert(fx==fy);


long double ax = fx / ps.m;
long double vx = ps.v_x + ax * delta_t;
long double x = ps.x + ps.v_x * delta_t + 0.5 * ax * delta_t * delta_t;

long double ay = fy / ps.m;
long double vy = ps.v_y + ay * delta_t;
long double y = ps.y + ps.v_y * delta_t + 0.5 * ay * delta_t * delta_t;

 


//G::PlanetState r;
return {ps.m, x, y, vx, vy,ps.r,ps.stringtexture,ps.texture};
}




void U::Universe::check_Collision(){
  for (auto it = copy_.begin(); it < copy_.end()-1; ++it) {
  for (auto jt = it+1; jt < copy_.end(); ++jt){




if (newton_.d_2((*it),(*jt))<=newton_.r_2 ((*it),(*jt))){
double M = (*it).m+(*jt).m;
long double X = (*it).m*(*it).x+(*jt).m+(*jt).x;
long double Y = (*it).m*(*it).y+(*jt).m+(*jt).y;
long double VX=  (((*it).m*(*it).v_x)  + ((*jt).m*(*jt).v_x));
long double VY = (((*it).m*(*it).v_y)  + ((*jt).m*(*jt).v_y));
double R = std::sqrt((*it).r*(*it).r+(*jt).r*(*jt).r);


G::PlanetState p{
M,X/M, Y/M, VX/M, VY/M,R};
//G::PlanetState p{0,0,0,0,0,0};
long double before = calculateenergy();
//galaxy_.reserve(galaxy_.size()+1);
unsigned int s = galaxy_.size();
remove(*it);
remove(*jt);
push_back(p);
assert (galaxy_.size()==s-1);
long double after = calculateenergy();
//assert (""==(std::to_string(before)+","+std::to_string(before)));


assert(before>=after);
mechanic_energy_ = after;
lost_energy_ = before - after;
total_energy_ = before;


findimportantplanet();
  }
}
}
}
long double U::Universe::calculateenergy(){
 return std::accumulate (galaxy_.begin(), galaxy_.end(),0,[](double r, const G::PlanetState &gi){
   double v=(gi).v_x*(gi).v_x + (gi).v_y*(gi).v_y ;
   r+=(0.5*(gi).m*v);
   return r;
   });

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

G::PlanetState &U::Universe::operator[](unsigned int index) {
  assert(index < galaxy_.size());
  return galaxy_[index];
}
const G::PlanetState &U::Universe::operator[](unsigned int index) const {
  assert(index < galaxy_.size());
  return galaxy_[index];
}






