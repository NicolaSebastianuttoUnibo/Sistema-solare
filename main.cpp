#include <SFML/Graphics.hpp>
#include "universe.hpp"
#include "texturemanagement.hpp"
#include "Button.hpp"




#include <iostream>
#include <string>
#include <sstream>
#include <fstream>


#include <memory>


#include <cmath>





int main()
{   




 bool selecting;
 bool selected;
 int choose;
 std::vector<std::string> choice1={"Set\nmass","Set\npos","Set\nvelocity","Set\nradius"};


 sf::Vector2<double> camera {400,400};//camera




sf::Font font;
sf::CircleShape planet(0.f);
sf::CircleShape contorno(0.f);
 




  std::shared_ptr<U::FileUniverse> ptr;
  std::shared_ptr<TM> vettoreditexture;




   try{






 if (!font.loadFromFile("Arial.ttf")) {
     throw std::runtime_error("font non caricato");


   }


   std::cout<<"Do you want to open an existing file (o) or do you want to create a new one (c)?";
   std::string response;
   std::cin>>response;
if(response=="o"||response=="open"){
std::cout<<"\nChoose the file you want to open (WITHOUT '.txt')\n";
std::cin>>response;
G::Newton newton{};


ptr = std::make_shared<U::FileUniverse>(newton, response, true);


vettoreditexture = std::make_shared<TM>("Texture",ptr.get());




}


else if(response=="c"||response=="create"){
    std::cout<<"\nChoose the name of the new file(WITHOUT '.txt')\n";
std::cin>>response;
G::Newton newton{};


ptr = std::make_shared<U::FileUniverse>(newton, response, false);


vettoreditexture = std::make_shared<TM>("Texture",ptr.get());


   
  


}






else{
throw std::runtime_error("Invalid input");
}
   }
   catch(const std::exception& e){
std::cerr<<"Error: "<<e.what()<<"\n";
return 1;
   }


   U::FileUniverse u=*ptr;
   TM tm=*vettoreditexture;
  Button save_button(sf::Vector2f(0, 0), sf::Vector2f(150, 90), "Save",
                 sf::Color::Yellow, sf::Color::Black, font, true);
 Button add_button(sf::Vector2f(160, 0), sf::Vector2f(150, 90), "Add\nplanet",
                 sf::Color::Yellow, sf::Color::Black, font,true);
 Button select_button(sf::Vector2f(320, 0), sf::Vector2f(150, 90), "Select\nplanet",
                 sf::Color::Yellow, sf::Color::Black, font,true);
 Button next_button(sf::Vector2f(480, 0), sf::Vector2f(150, 90), "Next\planet",
                 sf::Color::Yellow, sf::Color::Black, font,false);
 Button data_button(sf::Vector2f(640, 0), sf::Vector2f(150, 90), "Mass",
                 sf::Color::Yellow, sf::Color::Black, font,false);
    Button set_button(sf::Vector2f(0, 0), sf::Vector2f(150, 90), "Set value",
                 sf::Color::Yellow, sf::Color::Black, font, false);              
/*Button set_button(sf::Vector2f(0, 0), sf::Vector2f(150, 90), "OK",
                 sf::Color::Yellow, sf::Color::Black, font, false);*/




sf::RenderWindow window(sf::VideoMode(800, 800), "UNIVERSE");
   while (window.isOpen())
   {
       sf::Event event;
       while (window.pollEvent(event))
       {
           if (event.type == sf::Event::Closed)
               window.close();




                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
              ///MOUSE IS CLICKED
              sf::Vector2i mousePosition = sf::Mouse::getPosition(window);




               if (save_button.isClicked(mousePosition)&&save_button.isVisible()) {


                   u.save();
                 
               }
          




               else if (add_button.isClicked(mousePosition)&&add_button.isVisible()) {
               G::PlanetState p{1e10, -camera.x+400, -camera.y+400, 0, 0,100,"default"};
               u.push_back(p);
               u.save();
               tm.tm("Folder", &u);
               }
          






               else if (select_button.isClicked(mousePosition)&&select_button.isVisible()) {
                  selecting=!selecting;
                  if(selecting){choose=0;
                   select_button.setText("Unselect\nplanet");
               next_button.show();
               set_button.show();


                  }
                  else{
                   select_button.setText("Select\nplanet");
                   next_button.hide();
                   set_button.hide();




                  }
               }


               else if (next_button.isClicked(mousePosition)&&next_button.isVisible()&&!selected) {
                if(choose<u.size()-1){choose++;}
                else {choose=0;}
               camera.x=-u[choose].x+400;
               camera.y=-u[choose].y+400;
               }
else{if (selecting){for (int i=0; i<u.size();++i){
    /*sf::FloatCircle buttonBounds = shape_.getGlobalBounds();
   return buttonBounds.contains(sf::Vector2f(mousePosition));*/

float radius=u[i].r;
float distance=std::sqrt(std::pow(mousePosition.x-(-u[i].x-camera.x),2)+std::pow(mousePosition.x-(-u[i].y-camera.y),2));
if (distance<radius) {if (i==choose){selected=!selected;} else{choose=i;} break;}
}


}}



           }






////MOVING CAMERA
if(!selecting){
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))   {   camera.x+=5;  }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){ camera.x-=5;  }
               if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){camera.y+=5; }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))    {camera.y-=5;  }
}








       }




window.clear();




sf::FloatRect visibleArea(0, 0, window.getSize().x, window.getSize().y);


for(int i=0;i<u.size();++i){
 float r=u[i].r;




   
   


sf::FloatRect planetBounds(u[i].x + camera.x - r, u[i].y + camera.y - r, 2 * r, 2 * r);


if (planetBounds.intersects(visibleArea)) {if(i==choose&&selecting){
    contorno.setRadius(1.05*r);
    contorno.setOrigin(1.05*r, 1.05*r);
    contorno.setFillColor(sf::Color::White); if (selected) {contorno.setFillColor(sf::Color::Yellow);}
    contorno.setPosition(u[i].x+camera.x,u[i].y+camera.y);
    window.draw(contorno);
}
    
    
    
    planet.setPosition(u[i].x+camera.x,u[i].y+camera.y);
    planet.setOrigin(r,r);
    planet.setRadius(r);
planet.setTexture(u[i].texture);
window.draw(planet);

   
}

}


      
       save_button.draw(window);
       add_button.draw(window);
       select_button.draw(window);
       next_button.draw(window);
       set_button.draw(window);


       window.display();
   }




}
