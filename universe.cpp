
#include "universe.hpp"
#include <cmath>


#include <algorithm>
#include <cassert>
#include <numeric>
#include <iostream>
#include <iomanip>128








U::Universe::Universe(U::Newton const &newton) : newton_{newton} {
      mpfr_init2(initial_energy_,128);
        mpfr_init2(cinetic_energy_,128);
        mpfr_init2(potential_energy_,128);
        mpfr_init2(mechanic_energy_,128);
        mpfr_init2(lost_energy_,128);
        mpfr_init2(total_energy_,128);
   




}
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



mpfr_t before;
mpfr_init2(before, 128);
calculateenergy();
mpfr_init_set(before, total_energy_, MPFR_RNDN);

unsigned int s = copy_.size();
if (newton_.d_2((*it),(*jt))<=newton_.r_2 ((*it),(*jt))){
double M = ((*it).m+(*jt).m);
double X = ((*it).m*(*it).x+(*jt).m*(*jt).x);
double Y = ((*it).m*(*it).y+(*jt).m*(*jt).y);
double VX=  (((*it).m*(*it).v_x)  + ((*jt).m*(*jt).v_x));
double VY = (((*it).m*(*it).v_y)  + ((*jt).m*(*jt).v_y));
  double R{std::hypot((*it).r,(*jt).r)};


G::PlanetState p{M,X/M, Y/M, VX/M, VY/M, R, (  ((*it).m > (*jt).m) ? (*it).stringtexture : (*jt).stringtexture), (  ((*it).m > (*jt).m) ? (*it).texture : (*jt).texture)};
//G::PlanetState p{0,0,0,0,0,0};
 

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

 galaxy_=copy_;

 mpfr_t after;
mpfr_init2(after, 128);
calculateenergy();
mpfr_init_set(after, total_energy_, MPFR_RNDN);
assert(mpfr_cmp(before, after) >= 0);
mpfr_sub(lost_energy_, before, after, MPFR_RNDN);

        mpfr_clear(before);
        mpfr_clear(after);


goto end;
  }
}
}
end:

return;
}

void U::Universe::calculateenergy() {
  /*

mpfr_t sum;
mpfr_init2(sum, 128);
    mpfr_set_zero(sum, 0);  // Inizializza la somma a 0

    for (const G::PlanetState &gi : galaxy_) {

        mpfr_t mass;
mpfr_init2(mass, 128);
        mpfr_init_set_d(mass, gi.m, MPFR_RNDN);



        mpfr_t vx;
mpfr_init2(vx, 128);
        mpfr_init_set_d(vx, gi.v_x, MPFR_RNDN);

        mpfr_t vy;
mpfr_init2(vy, 128);
        mpfr_init_set_d(vy, gi.v_y, MPFR_RNDN);

 mpfr_mul(vx, vx, vx, MPFR_RNDN);// vx*vx
 mpfr_mul(vy, vy, vy, MPFR_RNDN); //vy*vy
 mpfr_add(vx, vx, vy, MPFR_RNDN);//vx*vx+vy*vy=v*v
 mpfr_mul(mass, mass, vx, MPFR_RNDN); //m*v*v
 mpfr_mul_d(mass, mass, 0.5, MPFR_RNDN);//0.5*m*v*v



mpfr_add(sum, sum, mass, MPFR_RNDN);

        mpfr_clear(mass);
        mpfr_clear(vx);
        mpfr_clear(vy);

    }
 mpfr_mul_d(sum, sum, 1e3, MPFR_RNDN);
    mpfr_set(cinetic_energy_, sum, MPFR_RNDN); // Assegna il valore di sum a cinetic_energy_

  mpfr_set_zero(sum, 0); 

    for (const G::PlanetState &gi : galaxy_) {
    for (const G::PlanetState &hi : galaxy_) {
if (!(gi == hi)) {


      mpfr_t G;
      mpfr_init2(G, 128);
      mpfr_init_set_d(G, newton_.G_, MPFR_RNDN);

      mpfr_t m;
      mpfr_init2(m, 128);
      mpfr_init_set_d(m, gi.m, MPFR_RNDN);

      mpfr_t M;
      mpfr_init2(M, 128);
      mpfr_init_set_d(M, hi.m, MPFR_RNDN);


      mpfr_t x;
      mpfr_init2(x, 128);
      mpfr_init_set_d(x, gi.x, MPFR_RNDN);

      mpfr_t X;
      mpfr_init2(X, 128);
      mpfr_init_set_d(X, hi.x, MPFR_RNDN);


          mpfr_t y;
      mpfr_init2(y, 128);
      mpfr_init_set_d(y, gi.y, MPFR_RNDN);

      mpfr_t Y;
      mpfr_init2(Y, 128);
      mpfr_init_set_d(Y, hi.y, MPFR_RNDN);

      mpfr_sub(x, x, X, MPFR_RNDN);
      mpfr_mul(x, x, x, MPFR_RNDN);
      mpfr_sub(y, y, Y, MPFR_RNDN);
      mpfr_mul(y, y, y, MPFR_RNDN);

       mpfr_add(x, x, y, MPFR_RNDN);



      mpfr_sqrt(x, x, MPFR_RNDN);

      mpfr_mul(G, G, m, MPFR_RNDN);
      mpfr_mul(G, G, M, MPFR_RNDN);
     mpfr_div(G, G, x, MPFR_RNDN);


mpfr_add(sum, sum, G, MPFR_RNDN);

        mpfr_clear(x);
        mpfr_clear(X);
        mpfr_clear(y);
        mpfr_clear(Y);
        mpfr_clear(m);
        mpfr_clear(M);
        mpfr_clear(G);


        }
    }}

     mpfr_div_d(sum, sum, 2, MPFR_RNDN);
 mpfr_mul_d(sum, sum, -1e3, MPFR_RNDN);
    mpfr_set(potential_energy_, sum, MPFR_RNDN); 

    mpfr_set_zero(sum, 0); 
    mpfr_add(sum, cinetic_energy_, potential_energy_, MPFR_RNDN);
    mpfr_set(mechanic_energy_, sum, MPFR_RNDN); 
    mpfr_add(sum, mechanic_energy_, lost_energy_, MPFR_RNDN);
    mpfr_set(total_energy_, sum, MPFR_RNDN); 
    
        mpfr_clear(sum);



}
void U::Universe::setInitialEnergy(){
   mpfr_set(initial_energy_, mechanic_energy_, MPFR_RNDN); 
    mpfr_set_zero(lost_energy_, 0); 
*/

}