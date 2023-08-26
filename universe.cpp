
#include "universe.hpp"
#include <cmath>


#include <algorithm>
#include <cassert>
#include <numeric>




U::Universe::Universe(U::Newton const &newton) : newton_{newton},initial_energy_{calculateenergy()} {}
int U::Universe::size() const { return galaxy_.size(); }




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
auto kt = std::find(copy_.begin(), copy_.end(), *(it+1));
 assert(jt!=copy_.end());
 assert(kt!=copy_.end());
 int idx=std::distance(copy_.begin(),jt);
 int idx2=std::distance(copy_.begin(),kt);
  newton_(galaxy_[idx],galaxy_[idx2]);
double fx = newton_.f_x;
double fy = newton_.f_y;
 galaxy_[idx]=solve(*(it),fx,fy,delta_t);








 // }
}
 check_Collision();


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
void U::Universe::check_Collision(){
 copy_=galaxy_;
  //for (auto it = copy_.begin(); it < copy_.end()-1; ++it) {
  //for (auto jt = it+1; jt < copy_.end(); ++jt){
  for (int i = 0; i<galaxy_.size()-1;++i){
  for (int j = i; j<galaxy_.size();++j){
auto it = &copy_[i];
auto jt = &copy_[j];


  




//double x_2=((*it).x - (*jt).x)*((*it).x - (*jt).x);
//double y_2=((*it).y - (*jt).y)*((*it).y - (*jt).y);
//double r_2=((*it).r + (*jt).r)*((*it).r + (*jt).r);


//double d_2{x_2+ y_2};




   /////decidere se usare std::pow oppure std::sqrt-->ragionare
//if (newton_.d_2(galaxy_[i],galaxy_[j])<=newton_.r_2 (galaxy_[i],galaxy_[j])){
if (newton_.d_2((*it),(*jt))<=newton_.r_2 ((*it),(*jt))){
double M = (*it).m+(*jt).m;
double X = (*it).m*(*it).x+(*jt).m+(*jt).x;
double Y = (*it).m*(*it).y+(*jt).m+(*jt).y;
double VX= (*it).m*(*it).v_x+(*jt).m+(*jt).v_x;
double VY = (*it).m*(*it).v_y+(*jt).m+(*jt).v_y;
double R = std::sqrt((*it).r*(*it).r+(*jt).r*(*jt).r);

G::PlanetState p{
M,X/M, Y/M, VX/M, VY/M,R};
//G::PlanetState p{0,0,0,0,0,0};
double before = calculateenergy();
//galaxy_.reserve(galaxy_.size()+1);
int s = galaxy_.size();
remove(galaxy_[i]);
remove(galaxy_[j]);
push_back(p);
assert (galaxy_.size()==s-1);
double after = calculateenergy();
//assert (""==(std::to_string(before)+","+std::to_string(before)));


//assert(before>=after);
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




