#include <fstream>
/// #include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

bool onlyspaces(const std::string &s) {
  return s.find_first_not_of(' ') == std::string::npos;
}

bool isValidLine(const std::string &line) {
  if (line.empty() || onlyspaces(line)) {
    return true;
  }

  std::istringstream iss(line);
  double d;
  std::string s;
  if (iss >> d >> d >> d >> d >> d >> d >> s && iss.eof()) {
    return true;
  }

  return false;
}

bool isValidFile(const std::string &filename) {
  std::ifstream inputFile(filename);

  if (!inputFile) {
    std::cerr << "Impossibile aprire il file " << filename << std::endl;
    return false;
  }

  std::string line;
  while (std::getline(inputFile, line)) {
    if (!isValidLine(line)) {
      std::cerr << "Il file contiene righe non valide.\n";
      return false;
    }
  }

  return true;
}

int countPlanets(const std::string &filename) {
  std::ifstream inputFile(filename);

  if (!inputFile) {
    std::cerr << "Impossibile aprire il file " << filename << "\n";
    return -1;  // Valore negativo per indicare errore
  }

  int planetCount = 0;
  std::string line;
  while (std::getline(inputFile, line)) {
    if (!line.empty() && !onlyspaces(line)) {
      planetCount++;
    }  /// se la riga non è vuota
  }

  return planetCount;
}

void addPlanet(const std::string &filename) {
  std::ofstream outputFile(filename, std::ios::app);

  if (!outputFile.is_open()) {
    std::cerr << "Impossibile aprire il file " << filename << "\n";
  }

  outputFile << "\n0 0 0 0 0 0 texture";
  outputFile.close();
}

void addPlanet(const std::string &filename, double a, double b, double c,
               double d, double e, double f, std::string s) {
  std::ofstream outputFile(filename, std::ios::app);

  if (!outputFile.is_open()) {
    std::cerr << "Impossibile aprire il file " << filename << "\n";
  }

  outputFile << "\n"
             << a << " " << b << " " << c << " " << d << " " << e << " " << f
             << " " << s;
  outputFile.close();
}

void removePlanet(const std::string &filename, const int &index) {
  if (index >= countPlanets(filename)) {
    std::cerr << "Index not valid.\n";
    return;
  }
  std::ifstream inputFile(filename);
  if (!inputFile.is_open()) {
    std::cerr << "Impossibile aprire il file di input " << filename << "\n";
  }
  std::vector<std::string> lines;
  std::string line;
  int currentLine = -1;
  while (std::getline(inputFile, line)) {
    if (!line.empty() && !onlyspaces(line)) {
      currentLine++;
    }
    if (currentLine != index) {
      lines.push_back(line);
    }
  }
  inputFile.close();

  std::ofstream outputFile(filename);
  if (!outputFile.is_open()) {
    std::cerr << "Impossibile aprire il file di output" << filename << "\n";
  }

  for (const std::string &line : lines) {
    outputFile << line << "\n";
  }
  outputFile.close();
}

double getMass(const std::string &filename, const int &index) {
  if (index >= countPlanets(filename)) {
    std::cerr << "Index not valid.\n";
    return -1;
  }

  std::ifstream inputFile(filename);

  if (!inputFile) {
    std::cerr << "Impossibile aprire il file " << filename << "\n";
    return -1;  // Valore negativo per indicare errore
  }

  int planetCount = 0;
  std::string line;
  while (std::getline(inputFile, line)) {
    if (!line.empty() && !onlyspaces(line)) {
      planetCount++;
    }  /// se la riga non è vuota
    if (planetCount == index + 1) {
      std::istringstream iss(line);
      double d, r;
      std::string s;
      iss >> r >> d >> d >> d >> d >> d >> s;
      return r;
    }
  }

  return -1;
}

void setMass(const std::string &filename, const int &index,
             const double &value) {
  if (index >= countPlanets(filename)) {
    std::cerr << "Index not valid.\n";
    return;
  }
  std::ifstream inputFile(filename);
  if (!inputFile.is_open()) {
    std::cerr << "Impossibile aprire il file di input " << filename << "\n";
  }
  std::vector<std::string> lines;
  std::string line;
  int currentLine = -1;
  while (std::getline(inputFile, line)) {
    if (!line.empty() && !onlyspaces(line)) {
      currentLine++;
    }
    if (currentLine != index) {
      lines.push_back(line);
    } else {
      std::stringstream iss(line);
      double a, b, c, d, e, f;
      std::string s;
      iss >> a >> b >> c >> d >> e >> f >> s;
      line = std::to_string(value) + " " + std::to_string(b) + " " +
             std::to_string(c) + " " + std::to_string(d) + " " +
             std::to_string(e) + " " + std::to_string(f) + " " + s;
      lines.push_back(line);
    }
  }
  inputFile.close();

  std::ofstream outputFile(filename);
  if (!outputFile.is_open()) {
    std::cerr << "Impossibile aprire il file di output" << filename << "\n";
  }

  for (const std::string &line : lines) {
    outputFile << line << "\n";
  }
  outputFile.close();
}

int main() {
  std::string filename = "file.txt";  // Sostituisci con il nome del tuo file

  int numberplanet = countPlanets(filename);
  if (numberplanet >= 0) {
    std::cout << "Il numero di pianeti nel file è: " << numberplanet << "\n";
  } else {
    std::cout << "Il file non contiene pianeti.\n";
  }

  if (isValidFile(filename)) {
    std::cout << "Il file è scritto correttamente."
              << "\n";
  } else {
    std::cout << "Il file non è scritto correttamente."
              << "\n";
  }

  setMass(filename, 1, 638);
  std::cout << "mass=" << getMass(filename, 1) << "\n";

  std::string nomefile = "file";
  std::ifstream file(nomefile + ".txt");
  if (file.good()) {
    std::cerr << "Esiste già il file \n";
  } else {
    std::ofstream prova(nomefile + ".txt");
    if (!prova.is_open()) {
      std::cerr << "Impossibile creare il file \n";
    }
    prova.close();
    std::cout << "File prova.txt creato con successo!\n";
  }
  return 0;
}