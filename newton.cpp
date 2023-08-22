#include "universe.hpp"


#include <cmath>


void U::Newton::operator()(const G::PlanetState& a, const G::PlanetState& b) {
 double d_2{(a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)};
 double f = G_ * a.m * b.m / (d_2);


 if (d_2 == 0) {
   f_x = 0;
   f_y = 0;
   return;
 }
 f_x = f * (b.x - a.x) / std::sqrt(d_2);
 f_y = f * (b.y - a.y) / std::sqrt(d_2);




}


void U::Newton::operator()(Universe* u,const G::PlanetState& a, const G::PlanetState& b) {
double d_2{(a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)};




if((a.r+b.r)*(a.r+b.r)>=d_2){///decidere se usare std::pow oppure std::sqrt-->ragionare
G::PlanetState p{a.m+b.m, (a.m*a.x+b.m+b.x)/(a.m+b.m), (a.m*a.y+b.m+b.y)/(a.m+b.m), (a.m*a.v_x+b.m+b.v_x)/(a.m+b.m), (a.m*a.v_y+b.m+b.v_y)/(a.m+b.m),std::sqrt(a.r*a.r+b.r*b.r)};
u->push_back(p);
 u->remove(a);
 u->remove(b);
 
return;


}


 double f = G_ * a.m * b.m / (d_2);
 f_x = f * (b.x - a.x) / std::sqrt(d_2);
 f_y = f * (b.y - a.y) / std::sqrt(d_2);




}
