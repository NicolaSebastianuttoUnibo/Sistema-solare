/// In questo programma provvisorio bisogna trovare per un modo per:
/// verificare se un file è scritto bene (ogni riga ha 6 numeri e alla fine una
/// parola)
// contare i pianeti di un file
// trovare massa, posizioni,velocità,raggio,texture per ogni pianeta di un file
// modificare dati di un file
/// creare un file con dei pianeti da zero

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

bool isValidLine(const std::string &line) {
  std::istringstream iss(line);
  double number;  // Utilizziamo un double per i numeri scientifici

  if (!(iss >> std::scientific >> number)) {
    return false;  // Non è stato possibile estrarre un numero scientifico
  }

  int count = 1;  // Contatore inizia da 1 (primo elemento letto)
  while (count < 6 && iss >> number) {
    if (iss.fail()) {
      return false;  // Non è un numero valido
    }
    count++;
  }

  std::string lastWord;
  if (count == 6 && (iss >> lastWord) && iss.eof()) {
    return true;  // La riga è valida
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
      std::cerr << "Il file contiene righe non valide: " << line << std::endl;
      return false;
    }
  }

  return true;
}

int countLines(const std::string &filename) {
  std::ifstream inputFile(filename);

  if (!inputFile) {
    std::cerr << "Impossibile aprire il file " << filename << std::endl;
    return -1;  // Valore negativo per indicare errore
  }

  int lineCount = 0;
  std::string line;
  while (std::getline(inputFile, line)) {
    lineCount++;
  }

  return lineCount;
}

int main() {
  std::string filename = "file.txt";  // Sostituisci con il nome del tuo file

  int lines = countLines(filename);
  if (lines >= 0) {
    std::cout << "Il numero di righe nel file è: " << lines << std::endl;
  } else {
    std::cout << "Errore durante l'apertura del file." << std::endl;
  }

  if (isValidFile(filename)) {
    std::cout << "Il file è scritto correttamente." << std::endl;
  } else {
    std::cout << "Il file non è scritto correttamente." << std::endl;
  }

  return 0;
}
