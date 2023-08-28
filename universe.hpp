
#ifndef UNIVERSE_HPP
#define UNIVERSE_HPP
#include <string>
#include <vector>


#include "newton.hpp"
namespace U {



struct Newton {
// la forza è espressa in megaNewton (10^6)N
double f_x{};  // force x
double f_y{};  // force y
void operator()(G::PlanetState const& a, G::PlanetState const& b);
double d_2(G::PlanetState const& a, G::PlanetState const& b);
double r_2(G::PlanetState const& a, G::PlanetState const& b);


const double G_{6.67430e-29*3600*3600};  /// costante G (MN*Mm^2/kg^2) our G = usual G*10^-18
};



class Universe {
Newton newton_;
std::vector<G::PlanetState> copy_;
G::PlanetState solve(G::PlanetState const &ps, double fx, double fy,
                    double delta_t) const;
std::vector<G::PlanetState*> importantplanet_;
void check_Collision();


public:
  std::vector<G::PlanetState> galaxy_;

double mechanic_energy_;
const double initial_energy_;
double lost_energy_;
double total_energy_;
double calculateenergy();
void findimportantplanet();




Universe(Newton const &newton);
void push_back(G::PlanetState const &ps);
void remove(G::PlanetState const &ps);
unsigned int size() const;
void evolve(double delta_t);

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

 public:
  FileUniverse(Newton const &newton, std::string str, bool a);
  void push_back(G::PlanetState const &ps);
  void remove(G::PlanetState const &ps);
  void save();
  void download();



};
}  // namespace U
#endif




