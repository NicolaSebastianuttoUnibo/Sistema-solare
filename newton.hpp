#ifndef FORZA_G_HPP
#define FORZA_G_HPP

namespace G {

struct PlanetState {
  double m{};//mass
  double x{};//pos_x 1x=1000km
  double y{};//pos_y
  double v_x{};//vel x
  double v_y{};//vel y
};



struct Newton{
    //la forza è espressa in nanoNewton (10^-12)N
  double f_x{};//force x
  double f_y{};//force y
void  operator()(PlanetState const& a, PlanetState const& b) ;
    private:
    double G_{6.67430e-11};///costante G

};

}

#endif