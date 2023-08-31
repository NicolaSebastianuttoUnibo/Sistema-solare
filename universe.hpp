
#ifndef UNIVERSE_HPP
#define UNIVERSE_HPP
#include <string>
#include <vector>
#include <cassert>



#include "newton.hpp"
namespace U {



struct Newton {
// la forza è espressa in megaNewton (10^6)N
 double f_x{};  // force x
 double f_y{};  // force y
void operator()(G::PlanetState const& a, G::PlanetState const& b);
 double d_2(G::PlanetState const& a, G::PlanetState const& b);
 double r_2(G::PlanetState const& a, G::PlanetState const& b);


///1KK=10^27kg

const double G_{6.67430*3.6*3.6*1e-5};  /// costante G (Mm^3/kg*h^2) 
};


class FileUniverse;///forward declaration
class Universe {
Newton newton_;
std::vector<G::PlanetState> copy_;
G::PlanetState solve(G::PlanetState const &ps,  double fx,  double fy,
                    double delta_t) const;
G::PlanetState solve2(G::PlanetState const &ps,
                    double delta_t) const;
                    
std::vector<G::PlanetState*> importantplanet_;
std::vector<G::PlanetState*> notimportantplanet_;

void check_Collision();


public:
  std::vector<G::PlanetState> galaxy_;

long double mechanic_energy_;
long double initial_energy_;
long double lost_energy_;
long double total_energy_;
 double calculateenergy();
void findimportantplanet();
/*double getInitialEnergy() const {
        return initial_energy_;
    }

    double getMechanicEnergy() const {
        return mechanic_energy_;
    }

    double getTotalEnergy() const {
        return total_energy_;
    }*/




Universe(Newton const &newton);


void push_back(G::PlanetState const &ps);
void remove(G::PlanetState const &ps);
unsigned int size() const;
void evolve(double delta_t);
void clear(){galaxy_.clear();}
std::vector<G::PlanetState> const &state() const;

  int findNearestPlanet(sf::Vector2i point);

  G::PlanetState &operator[](unsigned int index);
  const G::PlanetState &operator[](unsigned int index) const;









};

class FileUniverse : public Universe {
  std::string file_;
  bool isValidFile(const std::string &filename);
  unsigned int countPlanets(const std::string &filename);
  std::vector<G::PlanetState> copy_;


double ie(){return initial_energy_;}
std::vector<G::PlanetState> rg(){return galaxy_;}

 public:





     

  FileUniverse(Newton const &newton, std::string str, bool a);
  void push_back(G::PlanetState const &ps);
  void remove(G::PlanetState const &ps);
  void save();
  void download();



};
}  // namespace U
#endif




