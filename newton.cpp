#include "newton.hpp"
#include <cmath>

   void G::Newton::operator()(const G::PlanetState& a, const G::PlanetState& b){
   double d_2{(a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y)};
   double f=G_*a.m*b.m/(d_2);


if(d_2==0){f_x=0;f_y=0;return;}
   f_x=f*(b.x-a.x)/std::sqrt(d_2);
   f_y=f*(b.y-a.y)/std::sqrt(d_2);

   //f_x=d_2; 
   //f_y=f;
   }