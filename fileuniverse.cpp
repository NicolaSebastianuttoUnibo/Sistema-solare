#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cassert>
#include "universe.hpp"
#include "texturemanagement.hpp"




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








U::FileUniverse::FileUniverse(G::Newton const &newton, std::string str, bool alreadyexistsfortheuser)
   : Universe(newton), file_{str + ".txt"} {
 std::ifstream file{file_};
if(alreadyexistsfortheuser){
if (file.good()) {
 download();
}
else{
   throw std::runtime_error("Il file NON esiste \n");}


}


else{///for the user the file doesn't exist
if (file.good()) {
   throw std::runtime_error("Il file esiste già\n");
   file.close();
   }






}










}














void U::FileUniverse::push_back(G::PlanetState const &ps) {
 U::Universe::push_back(ps);


 std::ofstream outputFile(file_, std::ios::app);


 if (!outputFile.is_open()) {
   throw std::runtime_error("Impossibile aprire il file per inserire pianeta" + file_ );
 }


 outputFile << "\n"
            << ps.m << " " << ps.x << " " << ps.y << " " << ps.v_x << " "
            << ps.v_y << " " << ps.r << " " << ps.stringtexture;
 outputFile.close();
}




bool U::FileUniverse::isValidFile(const std::string &filename) {
   std::ifstream inputFile(filename);


 if (!inputFile) {
   throw std::runtime_error("Impossibile aprire il file per verificare se il file è scritto correttamente");
   return false;
 }


 std::string line;
 while (std::getline(inputFile, line)) {
   if (!isValidLine(line)) {
         throw std::runtime_error("Il file contiene righe non valide");


     return false;
   }
 }


 return true;
}










void U::FileUniverse::remove(G::PlanetState const &ps) {
 U::Universe::remove(ps);
 U::FileUniverse::save();


}




int U::FileUniverse::countPlanets(const std::string &filename) {


   std::ifstream inputFile(filename);


 if (!inputFile) {
   throw std::runtime_error("Impossibile aprire il file " + file_ + "durante il conteggio");
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






void U::FileUniverse::download() {
U::FileUniverse::isValidFile(file_);
 std::string line;




   std::ifstream inputFile(file_);


 if (!inputFile) {
   throw std::runtime_error("Impossibile aprire il file durante il download");
 
 }




 while (std::getline(inputFile, line)) {
   if (!line.empty() && !onlyspaces(line)) {
     std::stringstream iss(line);
     double a, b, c, d, e, f;
     std::string s;
     iss >> a >> b >> c >> d >> e >> f >> s;
   G::PlanetState p{a, b, c, d, e, f, s};
   U::Universe::push_back(p);
   
   }  /// se la riga non è vuota




 }//fine while
if(U::FileUniverse::countPlanets(file_)==U::FileUniverse::size()){
return;
}
else {


 throw std::runtime_error("Numer");
   //throw std::runtime_error("Il numero dei pianeti nel file("+std::to_string(U::FileUniverse::countPlanets(file_))+") e nel programma("+std::to_string(U::FileUniverse::size())+") sono diversi");


}




}




void U::FileUniverse::save() {
 copy_=galaxy_;
 assert(copy_.size()==galaxy_.size());
 galaxy_.clear();
 std::ofstream outFile(file_, std::ios::trunc);
 if (outFile.is_open()) {
   for (const auto &item : copy_) {
  
    push_back(item);
   }


   outFile.close();
 } else {
   throw std::runtime_error("Impossibile aprire il file " + file_ + "\n");
 }


}




