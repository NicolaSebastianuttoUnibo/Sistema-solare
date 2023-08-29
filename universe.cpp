
#include "universe.hpp"
#include <cmath>


#include <algorithm>
#include <cassert>
#include <numeric>
#include <iostream>
#include <iomanip>



/*



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




    double ax = newton_.G_ * (*jt).m / (((*it).r + (*jt).r) * ((*it).r + (*jt).r));
    double ay = newton_.G_ * (*jt).m / (((*it).r + (*jt).r) * ((*it).r + (*jt).r));
    if (ax * ax + ay * ay > -1&&it!=jt) {///-1 così prende tutti i pianeti
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
  assert(galaxy_.size() >= 1);
  copy_ = galaxy_;
  assert(copy_.size() == galaxy_.size());
  for (auto it = importantplanet_.begin(); it < importantplanet_.end(); it+=2) {
auto jt = std::find(copy_.begin(), copy_.end(), *(*it));
    int idx = std::distance(copy_.begin(), jt);

    std::pair< double,  double> forza =
        std::accumulate(importantplanet_.begin(), importantplanet_.end(), std::make_pair(0.0, 0.0),
                        [this, it](std::pair<long double, long double> sums,
                                   const G::PlanetState* ci) {
                          newton_(*(*it), *ci);
                          sums.first += newton_.f_x;
                          sums.second += newton_.f_y;
                          return sums;
                        });
                        newton_(*(*it), *(*(it+1)));
std::pair< double,  double> forza=std::make_pair(newton_.f_x,newton_.f_y);
                          std::cout<<std::fixed << std::setprecision(10) <<forza.first<<"\n";

std::cout<<"\n";
    galaxy_[idx] = solve(*(jt), forza.first, forza.second, delta_t);
  }
  // galaxy_[0].x+=1000;
}



/*

void U::Universe::evolve(double delta_t) {
 check_Collision();

copy_=galaxy_;
 assert(copy_.size()!=0),
 assert(galaxy_.size()!=0);

for (auto it=importantplanet_.begin(); it<importantplanet_.end(); it+=2){



auto jt = std::find(copy_.begin(), copy_.end(), *(*it));
auto kt = std::find(copy_.begin(), copy_.end(), *(*(it+1)));
//auto jt=galaxy_.begin();
//auto kt=galaxy_.end()-1;
 assert(jt!=copy_.end());
 assert(kt!=copy_.end());
 int idx=std::distance(copy_.begin(),jt);
 int idx2=std::distance(copy_.begin(),kt);
  newton_(copy_[idx],  copy_[idx2]);
 // std::precision(20);
// std::cout<<std::to_string(newton_.f_y)+"\n";
// std::cout<<std::to_string(idx2)<<",";
// std::cout<<std::to_string(newton_.f_y)+"\n";


                          std::cout<<std::fixed << std::setprecision(10) <<newton_.f_y<<"\n";

G::PlanetState diff=solve(*jt,newton_.f_x,newton_.f_y,delta_t);

G::PlanetState sum{
  galaxy_[idx].m, galaxy_[idx].x+diff.x + galaxy_[idx].v_x*delta_t,   galaxy_[idx].y+diff.y+ galaxy_[idx].v_y*delta_t,
  galaxy_[idx].v_x+diff.v_x,  galaxy_[idx].v_y+diff.v_y, galaxy_[idx].r,
  galaxy_[idx].stringtexture, galaxy_[idx].texture};

 galaxy_[idx]={sum.m,sum.x,sum.y,sum.v_x,sum.v_y,sum.r,sum.stringtexture,sum.texture};




}
std::cout<<"\n";

}


G::PlanetState U::Universe::solve(G::PlanetState const &ps,  double fx,
                                   double fy, double delta_t) const {///calcola la variazione
   double ax = fx / ps.m;
   double vx = ax * delta_t;
   double x =  0.5 * ax * delta_t * delta_t;

   double ay = fy / ps.m;
   double vy = ay * delta_t;
   double y =  0.5 * ay * delta_t * delta_t;

  G::PlanetState r{ps.m, x, y, vx, vy, ps.r, ps.stringtexture, ps.texture};
  return r;
}



void U::Universe::check_Collision(){
  for (auto it = copy_.begin(); it < copy_.end()-1; ++it) {
  for (auto jt = it+1; jt < copy_.end(); ++jt){
 // for (int i = 0; i<galaxy_.size()-1;++i){
 // for (int j = i+1; j<galaxy_.size();++j){
//auto it = &copy_[i];
//auto jt = &copy_[j];






//double x_2=((*it).x - (*jt).x)*((*it).x - (*jt).x);
//double y_2=((*it).y - (*jt).y)*((*it).y - (*jt).y);
//double r_2=((*it).r + (*jt).r)*((*it).r + (*jt).r);


//double d_2{x_2+ y_2};



   /////decidere se usare std::pow oppure std::sqrt-->ragionare
//if (newton_.d_2(galaxy_[i],galaxy_[j])<=newton_.r_2 (galaxy_[i],galaxy_[j])){

//assert((*it).x);

if (newton_.d_2((*it),(*jt))<=newton_.r_2 ((*it),(*jt))){
double M = (*it).m+(*jt).m;
double X = (*it).m*(*it).x+(*jt).m+(*jt).x;
double Y = (*it).m*(*it).y+(*jt).m+(*jt).y;
double VX=  (((*it).m*(*it).v_x)  + ((*jt).m*(*jt).v_x));
double VY = (((*it).m*(*it).v_y)  + ((*jt).m*(*jt).v_y));
double R = std::sqrt((*it).r*(*it).r+(*jt).r*(*jt).r);


G::PlanetState p{
M,X/M, Y/M, VX/M, VY/M,R};
//G::PlanetState p{0,0,0,0,0,0};
double before = calculateenergy();
//galaxy_.reserve(galaxy_.size()+1);
int s = galaxy_.size();
remove(*it);
remove(*jt);
push_back(p);
assert (galaxy_.size()==s-1);
double after = calculateenergy();
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
double U::Universe::calculateenergy(){
 return std::accumulate (galaxy_.begin(), galaxy_.end(),0,[](double r, const G::PlanetState &gi){
   double v=(gi).v_x*(gi).v_x + (gi).v_y*(gi).v_y ;
   r+=(0.5*(gi).m*v);
   return r;
   });

}


*/
/*



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

*/




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
                        [this, it](std::pair<long double, long double> sums,
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
double M = (*it).m+(*jt).m;
double X = (*it).m*(*it).x+(*jt).m+(*jt).x;
double Y = (*it).m*(*it).y+(*jt).m+(*jt).y;
double VX=  (((*it).m*(*it).v_x)  + ((*jt).m*(*jt).v_x));
double VY = (((*it).m*(*it).v_y)  + ((*jt).m*(*jt).v_y));
double R = std::sqrt((*it).r*(*it).r+(*jt).r*(*jt).r);


G::PlanetState p{
M,X/M, Y/M, VX/M, VY/M,R};
//G::PlanetState p{0,0,0,0,0,0};
double before = calculateenergy();
//galaxy_.reserve(galaxy_.size()+1);
int s = galaxy_.size();
remove(*it);
remove(*jt);
push_back(p);
assert (galaxy_.size()==s-1);
double after = calculateenergy();
//assert (""==(std::to_string(before)+","+std::to_string(before)));


assert(before>=after);
mechanic_energy_ = after;
lost_energy_ = before - after;
total_energy_ = before;


  }
}
}
}
double U::Universe::calculateenergy(){
 return std::accumulate (galaxy_.begin(), galaxy_.end(),0,[](double r, const G::PlanetState &gi){
   double v=(gi).v_x*(gi).v_x + (gi).v_y*(gi).v_y ;
   r+=(0.5*(gi).m*v);
   return r;
   });

}