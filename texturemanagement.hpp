#ifndef TEXTUREMANAGEMENT_HPP
#define TEXTUREMANAGEMENT_HPP


#include <SFML/Graphics.hpp>
#include "universe.hpp"
#include <string>
#include <algorithm>
#include <vector>
#include <filesystem>
#include <cassert>








class TM {
   std::vector<sf::Texture> texture_vector_;
   std::vector<std::string> texture_name_;
U::FileUniverse *u_;
const std::string s_;








void findAllTexture(std::string s){
assert(texture_name_.size()==0);
if(std::filesystem::is_directory(s)){
for(const auto& entry : std::filesystem::directory_iterator(s)){
   if(entry.is_regular_file()&&(entry.path().extension()==".png"||entry.path().extension()==".jpg")){
   texture_name_.push_back(entry.path().filename().string());
   }


}
}
else{
   throw std::runtime_error("NOn ho trovato la cartella");
}


}////findAllTexture




int size(){
   return texture_name_.size();
}///size










void addTexture(sf::Texture &t){
texture_vector_.push_back(t);


}///addTexture


bool checkSize(){
return texture_vector_.size()==texture_name_.size();
}///check size


void assignTexture(U::Universe *u){
   assert(texture_vector_.size()!=0);


for(int i=0;i<(*u).size();++i){
unsigned int idx=std::distance(texture_name_.begin(),std::find(texture_name_.begin(),texture_name_.end(),  (*u)[i].stringtexture));


if(idx<texture_name_.size()){
(*u)[i].setPlanetTexture((*u)[i].stringtexture,&texture_vector_[idx]);
}
else {
   std::string standardimage="standard.jpg";////+ controllo (nessun errore di battitura)
   assert( (*u)[i].stringtexture!=standardimage);
  (*u)[i].stringtexture=standardimage;
   i--;
}




}


}///assignTexture










void savetexture(std::string folder, U::Universe *universe){


   if(texture_name_.size()==0){
   findAllTexture(folder);
  
   for(unsigned int i=0;i<texture_name_.size();++i){
sf::Texture texture;


  if (!texture.loadFromFile(folder+"/"+texture_name_[i]))
{
  throw std::runtime_error("Failed to load texture a texture from the  folder"+folder); // Throw an exception to handle the error.
 }


addTexture(texture);
}
   }


if(!checkSize()){
  throw std::runtime_error("Error on size"); // Throw an exception to handle the error.


}


assignTexture(universe);///metto la texture nei pianeti


}///saveTeture














public:
//TM(const std::string& str,  U::Universe* u): : u_{u},s_{str} {savetexture(str,u);}


TM(const std::string& str, U::FileUniverse* u) : u_{u}, s_{str} { savetexture(s_, u_); }


void tm(){
   savetexture(s_,u_);
}
void tm(const std::string& str, U::FileUniverse* u){
   savetexture(str,u);
}






std::string showAllNameImages(){
std::string s;
for(const auto& img : texture_name_){
  
s+=img+"\n";


}
s+=("size of vector_txe"+std::to_string(texture_vector_.size())+"\n");
return s;


}////showAllNameImages


};
#endif // TEXTUREMANAGEMENT_HPP
