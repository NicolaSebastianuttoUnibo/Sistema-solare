#include <fstream>
#include <iostream>

#include "universe.hpp"

U::FileUniverse::FileUniverse(G::Newton const &newton, std::string str)
    : Universe(newton), file_{str + ".txt"} {
  std::ifstream file{file_};
  if (file.good()) {
    std::cerr << "Il file esiste già\n";
    file.close();
  } else {
    std::ofstream creafile(file_);

    if (!creafile.is_open()) {
      std::cerr << "impossibille creare il file\n";
    } else {
      creafile.close();
    }
  }
}

void U::FileUniverse::push_back(G::PlanetState const &ps) {
  U::Universe::push_back(ps);

  std::ofstream outputFile(file_, std::ios::app);

  if (!outputFile.is_open()) {
    std::cerr << "Impossibile aprire il file " << filename << "\n";
  }

  outputFile << "\n"
             << ps.m << " " << ps.x << " " << ps.y << " " << ps.v_x << " "
             << ps.v_y << " " << ps.r << " " << ps.texture;
  outputFile.close();
}

void U::FileUniverse::remove(G::PlanetState const &ps) {}
void U::FileUniverse::save(G::PlanetState const &ps) {
  std::ofstream outFile(file_, std::ios::trunc);
  if (outFile.is_open()) {
    for (const auto &item : galaxy_) {
      push_back(item);
    }

    outFile.close();
    else {
      std::cerr << "Impossibile aprire il file." << std::endl;
    }
  }
