#include "newton.hpp"
#include <cmath>

   void G::Newton::operator()(const G::PlanetState& a, const G::PlanetState& b){
   double d_2{(a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y)};

   if(a.x<b.x){//a si trova a sx di b
f_x=+G_*a.m*b.m/(d_2);
   }
   else if(a.x>b.x){//a si trova a dx di b
f_x=-G_*a.m*b.m/(d_2);
   }
   else{f_x=0;}

   if(a.y>b.y){//a si trova in basso di b
f_y=+G_*a.m*b.m/(d_2);
   }
   else if(a.y<b.y){//a si trova in alto di b
f_y=-G_*a.m*b.m/(d_2);
   }
   else{f_y=0;}

   }