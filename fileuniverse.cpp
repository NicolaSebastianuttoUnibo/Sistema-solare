#include <fstream>
#include <iostream>

#include "universe.hpp"

U::FileUniverse::FileUniverse(G::Newton const &newton, std::string str)
    : Universe(newton), file_{str + ".txt"} {
  std::ifstream file{file_};
  if (file.good()) {
    file.close();
    throw std::runtime_error("Il file esiste già\n");

  } else {
    std::ofstream creafile(file_);

    if (!creafile.is_open()) {
      throw std::runtime_error("Impossibile aprire il file " + file_ + "\n");
    } else {
      creafile.close();
    }
  }
}

void U::FileUniverse::push_back(G::PlanetState const &ps) {
  U::Universe::push_back(ps);

  std::ofstream outputFile(file_, std::ios::app);

  if (!outputFile.is_open()) {
    throw std::runtime_error("Impossibile aprire il file " + file_ + "\n");
  }

  outputFile << "\n"
             << ps.m << " " << ps.x << " " << ps.y << " " << ps.v_x << " "
             << ps.v_y << " " << ps.r << " " << ps.texture;
  outputFile.close();
}

void U::FileUniverse::remove(G::PlanetState const &ps) {}
void U::FileUniverse::save() {
  std::ofstream outFile(file_, std::ios::trunc);
  if (outFile.is_open()) {
    for (const auto &item : galaxy_) {
      push_back(item);
    }

    outFile.close();
  } else {
    throw std::runtime_error("Impossibile aprire il file " + file_ + "\n");
  }
}
