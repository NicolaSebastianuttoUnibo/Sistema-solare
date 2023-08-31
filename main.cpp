
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <memory>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

#include "Graphic.hpp"
#include "universe.hpp"


int main() {
  U::Newton newton{};

std::vector<sf::Color> colors = {
    sf::Color(255,255,0), sf::Color(255,0,255), sf::Color(0,255,255), sf::Color(255,100,0),
    sf::Color(100,0,255), sf::Color(100,255,0), sf::Color(100,255,0), sf::Color(255,0,100)};



  bool selecting{false}; ///the planet is surrounded by a white outline
  bool selected{false};  ///the planet is surrounded by a yellow outline
  bool choosingvalue{false};  ///the planet is surrounded by a red outline

  bool firstwindow{true}; ///the first window is shown

  bool followOnePlanet; ///during the animation the camera follows one planet
  bool followPlanets;  /// during theanimation the camera follows the centroid of a planets' set
  std::vector<G::PlanetState *> planetsfollowing;  ///vector of the planets' set
  bool createvector;  /// indicates if you are currently creating a set of planets.
  bool animation{false};  //indicates if the animation is on play(true) or pause(false)

 unsigned int planetIndex{0};  /// Index indicating the position of the planet within the vector.

  unsigned int var{0}; 
   ///Fist window: choose which variable of the planet you want to change
   ///Second window: indicating the position of the planet in the planets'set

  unsigned int index;  ///index of the nearest planet from the mouse

sf::VertexArray traj(sf::Points); ///planet trajectories

std::vector<std::string> choice = {"Set\nmass(M)",     "Set\npos(P)",
                                     "Set\nvelocity(V)", "Set\nradius(R)",
                                     "Set\ntexture(T)",  "Delete(X)"};

  sf::Vector2f camera{400, 400};  // camera position

  sf::Font font;
  sf::CircleShape planet(0.f);
  sf::CircleShape contorno(0.f);
  sf::Text text;
  sf::Text text2;

  std::shared_ptr<U::FileUniverse> ptr;
  std::shared_ptr<gr::TM> tm;

  std::string response;
  int month;
  int year;
  int day{1};
std::vector<std::string> months = {"January","Febraury","March","April","May","June","July","August","September","Optober","November","December"};



  sf::Clock clock;
  sf::Time elapsed;

  try {
    if (!font.loadFromFile("Arial.ttf")) {
      throw std::runtime_error("font non caricato");
    }

std::cout<<"Which year is this?\n";
std::cin>>year;
 if (!std::cin||year<0) {
            throw std::runtime_error("Year not valid");
        }
std::cout<<"Which month is this?(1-12)\n";
std::cin>>month;
 if (!std::cin||month<=0||month>12) {
            throw std::runtime_error("Month not valid");
        }

    std::cout << "Do you want to open an existing file (o) or do you want to "
                 "create a new one (c)?";
    std::cin >> response;
    if (response == "o" || response == "open") {
      std::cout << "\nChoose the file you want to open (WITHOUT '.txt')\n";
      std::cin >> response;
     

      ptr = std::make_shared<U::FileUniverse>(newton, response, true);

      tm = std::make_shared<gr::TM>("Texture", ptr.get());

    }

    else if (response == "c" || response == "create") {
      std::cout << "\nChoose the name of the new file(WITHOUT '.txt')\n";
      std::cin >> response;

      ptr = std::make_shared<U::FileUniverse>(newton, response, false);

      tm = std::make_shared<gr::TM>("Texture", ptr.get());

    }

    else {
      throw std::runtime_error("Invalid input. Restart.");
    }
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << "\n";
    return 1;
  }

  if ((*ptr).size() > 0) {
    camera.x = -(*ptr)[0].x + 400;
    camera.y = -(*ptr)[0].y + 400;
  }

  sf::RenderWindow window(sf::VideoMode(800, 800), response + ".txt");
  sf::FloatRect visibleArea(0, 0, window.getSize().x, window.getSize().y);
  window.setFramerateLimit(48);
  sf::RenderWindow evolvewindow(sf::VideoMode(800, 800),
                                "animation of " + response + ".txt");
  evolvewindow.setFramerateLimit(48);

  sf::RenderTexture renderTexture;
  renderTexture.create(evolvewindow.getSize().x, evolvewindow.getSize().y);

  evolvewindow.setVisible(false);

 gr::Button save_button(sf::Vector2f(0, 0), sf::Vector2f(150, 90), "Save",
                     sf::Color::Yellow, sf::Color::Black, font, true);
 gr::Button add_button(sf::Vector2f(160, 0), sf::Vector2f(150, 90), "Add\nplanet",
                    sf::Color::Yellow, sf::Color::Black, font, true);
 gr::Button select_button(sf::Vector2f(320, 0), sf::Vector2f(150, 90),
                       "Select\nplanet", sf::Color::Yellow, sf::Color::Black,
                       font, true);
 gr::Button next_button(sf::Vector2f(480, 0), sf::Vector2f(150, 90),
                     "Next\nplanet", sf::Color::Yellow, sf::Color::Black, font,
                     false);
 gr::Button data_button(sf::Vector2f(480, 90), sf::Vector2f(150, 90), "Mass",
                     sf::Color::Yellow, sf::Color::Black, font, false);
 gr::Button evolve_button(sf::Vector2f(640, 0), sf::Vector2f(150, 90), "Animation",
                       sf::Color::Yellow, sf::Color::Black, font, true);

 gr::Button error_button(
      sf::Vector2f(window.getSize().x / 2 - 100, window.getSize().y / 2 - 50),
      sf::Vector2f(200, 100), "Add a planet", sf::Color::Transparent,
      sf::Color::Red, font, false);

  text.setCharacterSize(25);
  text.setFillColor(sf::Color::White);
  text.setFont(font);
  text.setPosition(5, 90);

  text2.setCharacterSize(25);
  text2.setFillColor(sf::Color::White);
  text2.setFont(font);
  text2.setPosition(0, 0);

windows_open:
  while (window.isOpen() || window.isOpen()) {
    if (firstwindow) {
      sf::Event event;
      while (window.pollEvent(event)) {

        ///CLOSE WINDOW
        if (event.type == sf::Event::Closed) {
          window.close();
          evolvewindow.close();
        }

        if (event.type == sf::Event::MouseButtonPressed &&
            event.mouseButton.button == sf::Mouse::Left) {

          /// MOUSE LEFT IS CLICKED
          sf::Vector2i mousePosition = sf::Mouse::getPosition(window);


         ////EVOLVE BUTTON
          if (evolve_button.isClicked(mousePosition) && evolve_button.isVisible()) {
            if ((*ptr).size() == 0) {
              error_button.show();
            } 
            else {

            //  (*ptr).lost_energy_=0.;
              (*ptr).calculateenergy();
              (*ptr).setInitialEnergy();

  

              next_button.hide();
              data_button.hide();
              selecting=false;selected=false;choosingvalue=false;
              window.setVisible(false);
              evolvewindow.setVisible(true);
              firstwindow = false;
              animation = true;
                        
            }
           
          }

          evolve_button.hide();

          ////SAVE BUTTON
          if (save_button.isClicked(mousePosition) && save_button.isVisible()) {
            selected = false;
            selecting = false;
            choosingvalue=false;
            (*ptr).save();
            evolve_button.show();
          }


         ///ADD BUTTON
          else if (add_button.isClicked(mousePosition) &&
                   add_button.isVisible()) {
            G::PlanetState p{1e10, -camera.x + 400, -camera.y + 400, 0, 0,
                             100,  "default"};
            (*ptr).push_back(p);
            (*ptr).save();
            (*tm).tm("Folder", &(*ptr));
          }


         /////SELECT BUTTON
          else if (select_button.isClicked(mousePosition) &&
                   select_button.isVisible()) {
            selecting = !selecting;
            if ((*ptr).size() == 0) {
              selecting = false;
              error_button.show();
            }
            if (selecting) {
              planetIndex = 0;
              select_button.setText("Unselect\nplanet");
              next_button.show();
              selected = false;
              choosingvalue=false;

            } else {
              select_button.setText("Select\nplanet");
              selected = false;
              choosingvalue=false;
              next_button.hide();
              data_button.hide();
            }
          }
        ////NEXT BUTTON
          else if (next_button.isClicked(mousePosition) &&
                   next_button.isVisible() && (*ptr).size() > 0) {
            selected = false;
            choosingvalue = false;
            if (planetIndex < (*ptr).size() - 1) {
              planetIndex++;
            } else {
              planetIndex = 0;
            }
            camera.x = -(*ptr)[planetIndex].x + 400;
            camera.y = -(*ptr)[planetIndex].y + 400;

          }
         /////DATA BUTTON
          else if (((data_button.isClicked(mousePosition) &&
                     data_button.isVisible()))) {
            choosingvalue = !choosingvalue;
          } 
          ///ERROR BUTTON
          else if (((error_button.isClicked(mousePosition) &&
                       error_button.isVisible()))) {
            error_button.hide();
          }
         ////NO BUTTON
          else {

            ///choosingvalue
            if (choosingvalue) {
              if (var == 1) {
                (*ptr)[planetIndex].x = mousePosition.x - camera.x;
                (*ptr)[planetIndex].y = mousePosition.y - camera.y;
              }

              if (var == 2) {
                (*ptr)[planetIndex].v_x = mousePosition.x - camera.x - (*ptr)[planetIndex].x;
                (*ptr)[planetIndex].v_y = mousePosition.y - camera.y - (*ptr)[planetIndex].y;
              }

            }
          ////selecting
            else if (selecting) {
              index = (*ptr).findNearestPlanet(sf::Vector2i(
                  mousePosition.x - camera.x, mousePosition.y - camera.y));
             

              float radius = (*ptr)[index].r;
              float distance= std::hypot(mousePosition.x - ((*ptr)[index].x + camera.x),mousePosition.y - ((*ptr)[index].y + camera.y));

              if (distance < radius) {
                if (index == planetIndex) {
                  selected = !selected;
                } else {
                  selected = false;
                  planetIndex = index;
                }
              }
            }

          }

        }  /// this is the end of "MOUSE LEFT CLICKED"

        ////MOUSE RIGHT CLICKED
        if (event.type == sf::Event::MouseButtonPressed &&
            event.mouseButton.button == sf::Mouse::Right && !choosingvalue) {
          sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

          if (data_button.isClicked(mousePosition) && data_button.isVisible()) {
            if (var < choice.size() - 1) {
              var++;
            } else {
              var = 0;
            }

            data_button.setText(choice[var]);
          }

        }  /// this is the end of "MOUSE RIGHT CLICKED"

        
        
        ////KEYBOARD



/////camera
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
          camera.x += 5;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
          camera.x -= 5;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
          camera.y += 5;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
          camera.y -= 5;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
          selected = true;
        }

////SHORTCUTS


        if (selecting || selected) {
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) {
            data_button.show();
            next_button.show();

            selecting = true;
            choosingvalue = true;
            selected = true;
            var = 0;
            data_button.setText(choice[var]);
          }
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
            data_button.show();
            next_button.show();

            selecting = true;
            choosingvalue = true;
            selected = true;
            var = 1;
            data_button.setText(choice[var]);
          }
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::V)) {
            data_button.show();
            next_button.show();

            choosingvalue = true;


            selecting = true;
            selected = true;
            var = 2;
            data_button.setText(choice[var]);
          }
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
            data_button.show();
            next_button.show();

            selecting = true;
            selected = true;
            var = 3;
            data_button.setText(choice[var]);
          }
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) {
            data_button.show();
            next_button.show();
            choosingvalue = true;

            selecting = true;
            selected = true;
            var = 4;
            data_button.setText(choice[var]);
          }
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
            next_button.show();
            data_button.show();
            selecting = true;
            selected = true;
            var = 5;
            data_button.setText(choice[var]);
          }
        }

      }  ////END of pollEvent




      if (choosingvalue) {
        double a;

        std::string t;

        switch (var) {
          case 0:
            choosingvalue = true;
            window.setVisible(false);
            std::cout << "Choose mass: ";
            std::cin >> a;
            (*ptr)[planetIndex].m = a;
            choosingvalue = false;

            break;

          case 3:
            choosingvalue = true;

            window.setVisible(false);
            std::cout << "\nChoose rad: ";
            std::cin >> a;
            (*ptr)[planetIndex].r = a;
            choosingvalue = false;

            break;

          case 4:
            choosingvalue = true;

            window.setVisible(false);
            system("ls Texture");

            std::cout << "Choose texture: ";
            std::cin >> t;
            (*ptr)[planetIndex].stringtexture = t;
            (*tm).tm("Folder", &(*ptr));
            choosingvalue = false;

            break;

          case 5:
            if (planetIndex < (*ptr).size()) {
              std::cout << (*ptr).size();
              (*ptr).remove((*ptr)[planetIndex]);
            }
            if ((*ptr).size() == 0) {
             
              selected = false;
            }
            std::cout << (*ptr).size();
            choosingvalue = false;
            planetIndex = 0;
            break;
        }
        (*ptr).save();
        window.setVisible(true);

      }  /// finish getting the input

 if (selected) {
        data_button.show();
      } else {
        data_button.hide();
      }

      window.clear();

////TEXT
      std::string output = "camera_x=" + std::to_string(800 - camera.x) +
                           "\ncamera_y=" + std::to_string(800 - camera.y);

      if (selecting) {
        std::ostringstream oss;
        oss << std::scientific
            << std::setprecision(2);

        oss << "\nm=" << (*ptr)[planetIndex].m << "\nx=" << (*ptr)[planetIndex].x
            << "\ny=" << (*ptr)[planetIndex].y << "\nv_x=" << (*ptr)[planetIndex].v_x
            << "\nv_y=" << (*ptr)[planetIndex].v_y << "\nr=" << (*ptr)[planetIndex].r << "\n"
            << (*ptr)[planetIndex].stringtexture << "\ni=" << index << ",c=" << planetIndex;

        output += oss.str();
      }


      text.setString(output);



std::vector<G::PlanetState> draw=(*ptr).state();

      for (auto it = draw.begin(); it < draw.end(); ++it) {
        gr::drawing::drawPlanet(*it,camera,nullptr,window,visibleArea,selecting);
      }  ////fine for

      if (selecting) {
        if (choosingvalue) {
          gr::drawing::drawPlanet((*ptr)[planetIndex],camera,&sf::Color::Red,window,visibleArea,selecting);
        } else if (selected) {
         gr::drawing::drawPlanet((*ptr)[planetIndex],camera,&sf::Color::Yellow,window,visibleArea,selecting);
        }

      else{
gr::drawing::drawPlanet((*ptr)[planetIndex],camera,&sf::Color::White,window,visibleArea,selecting);
      }
      }
        
  

      window.draw(text);

      save_button.draw(window);
      add_button.draw(window);
      select_button.draw(window);
      next_button.draw(window);
      data_button.draw(window);
      evolve_button.draw(window);
      error_button.draw(window);

      window.display();

    }



    else {
      ///////SECONDA FINESTRA

      
      sf::Event event;
      bool pressed{false};

      while (evolvewindow.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {


          var = 0;
          firstwindow = true;
          animation = false;
          traj.clear();
          ptr = std::make_shared<U::FileUniverse>(newton, response, true);
          (*ptr).save();
          (*tm).tm("Folder", &(*ptr));
          camera.x = -(*ptr)[0].x + 400;
          camera.y = -(*ptr)[0].y + 400;
          renderTexture.clear();
          window.setVisible(true);
          evolvewindow.setVisible(false);
          goto windows_open;
        }


////STOP AND PAUSE
        if (!pressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
          animation = !animation;
          pressed = true;
        }
///CREATE VECTOR
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) {
          if (!createvector) {
            followOnePlanet = false;
            followPlanets = false;
            createvector = true;
            planetsfollowing.clear();
            var = 0;
            assert(planetIndex < (*ptr).size());
            planetsfollowing.push_back(&(*ptr)[planetIndex]);
          }
        }
        ///FINISH TO CREATE VECTOR
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
          createvector = false;
          followPlanets = true;
        }

        ////MOVE WITHIN VECTOR (GO TO LEFT)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
          if (createvector && var > 0) {
            var--;
          }
        }
        ////MOVE WITHIN VECTOR (GO TO RIGHT)

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
          if (createvector) {
            if (var < planetsfollowing.size() - 1) {
              var++;
            } else {
              assert(planetIndex < (*ptr).size());
              planetsfollowing.push_back(&(*ptr)[planetIndex]);
              var++;
              assert(var < planetsfollowing.size());
            }
          }

        }  
   ///SEE NEXT PLANET
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
          if (planetIndex < (*ptr).size() - 1) {
            planetIndex++;
          } else {
            planetIndex = 0;
          }
          assert(planetIndex < (*ptr).size());
          if (createvector) {
            assert(var < planetsfollowing.size());
            planetsfollowing[var] = &(*ptr)[planetIndex];
          }
        }
        ////SEE PREVIUOS PLANET
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
          if (planetIndex > 0) {
            planetIndex--;
          } else {
            planetIndex = (*ptr).size() - 1;
          }
          assert(planetIndex < (*ptr).size());
          if (createvector) {
            assert(var < (*ptr).size());
            planetsfollowing[var] = &(*ptr)[planetIndex];
          }
        }

        /////DELETE PLANET FROM PLANETS' SET
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
          if (planetsfollowing.size() > 1) {
            auto it = planetsfollowing.begin() + var;
            assert(it != planetsfollowing.end());
            if (planetIndex == planetsfollowing.size() - 1) {
              planetIndex--;
            }
            planetsfollowing.erase((it));
          }
        }

        ////FOLLOW THE CENTER OF PLANETS' SET
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
          followPlanets = true;
          followOnePlanet = false;
        }
        ///FOLLOW ONE PLANET
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
          followPlanets = false;
          followOnePlanet = true;
        }


/////camera
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
          camera.x += 5;
          followPlanets = false;
          followOnePlanet = false;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
          camera.x -= 5;
          followPlanets = false;
          followOnePlanet = false;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
          camera.y += 5;
          followPlanets = false;
          followOnePlanet = false;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
          camera.y -= 5;
          followPlanets = false;
          followOnePlanet = false;
        }

      }  ////END of pollEvent
      
      elapsed = clock.restart();

      evolvewindow.clear();
      renderTexture.clear();
  // if(day%50){
  //            (*ptr).calculateenergy();
  // }
    



       if (animation) {///the animation is on play
   day++;///

for(int i=0;i<100;i++){
    unsigned int s = (*ptr).size();
     assert( (*ptr).size()>0);
        (*ptr).evolve(0.01);
        if (s > (*ptr).size()) {

          followPlanets = false;

          if (planetIndex >= (*ptr).size()) {
            planetIndex--;
            assert(planetIndex < (*ptr).size());
          }
        }}
       }

  
      if (followOnePlanet) {
        camera.x = 400 - (*ptr)[planetIndex].x;
        camera.y = 400 - (*ptr)[planetIndex].y;
      }

      else if (followPlanets) {

        ///CENTROID

        std::pair<double, double> translation = std::accumulate(
            planetsfollowing.begin(), planetsfollowing.end(),
            std::make_pair(0.0, 0.0),
            [](std::pair<double, double> sums, const G::PlanetState *ci) {
              sums.first += (*ci).x;
              sums.second += (*ci).y;
              return sums;
            });

        camera.x = 400 - translation.first / planetsfollowing.size();
        camera.y = 400 - translation.second / planetsfollowing.size();

      }


      else if (createvector) {////text to guide the user to create the planets' set vector
        std::string s;
        if (var == 0) {
          s = "st";
        } else if (var == 1) {
          s = "nd";
        } else if (var == 2) {
          s = "rd";
        } else {
          s = "th";
        }

        text2.setString("You are following " +
                        std::to_string(planetsfollowing.size()) +
                        " planet(s) and you are choosing the " +
                        std::to_string(var + 1) + s + " planet");

        camera.x = 400 - (*planetsfollowing[var]).x;
        camera.y = 400 - (*planetsfollowing[var]).y;
        text2.setPosition((*ptr)[planetIndex].x - 400, (*ptr)[planetIndex].y - 400);
        renderTexture.draw(text2);
      }
///drawing text
 std::string output;
  //  assert((*ptr).cinetic_energy_>=0);
  //  assert((*ptr).potential_energy_<=0);
        std::ostringstream oss;
        oss << std::scientific
            << std::setprecision(20);

            output=months[month-1]+" "+std::to_string(year)+"\nFPS: "+std::to_string(1.0f / elapsed.asSeconds());
if(followOnePlanet){
        oss << "\nm=" << (*ptr)[planetIndex].m
            << "\nvx=" << (*ptr)[planetIndex].v_x << "\nvy=" << (*ptr)[planetIndex].v_y
            << "\n"<<(*ptr)[planetIndex].stringtexture;

        
}else {
  //  oss       << "\ninitial energy=" << (*ptr).initial_energy_
  //           << "\ntotal energy=" << (*ptr).total_energy_
  //           << "\nmechanic energy=" << (*ptr).mechanic_energy_
  //           << "\ncinetic energy=" << (*ptr).cinetic_energy_
  //           << "\npotential energy=" << (*ptr).potential_energy_
  //           << "\nlost energy=" << (*ptr).lost_energy_;

// size_t str_size = mpfr_snprintf(nullptr, 0, "%.Rf", (*ptr).initial_energy_);
// char *str_initial_energy = new char[str_size + 1];
// mpfr_snprintf(str_initial_energy, str_size + 1, "%.Rf", (*ptr).initial_energy_);
// std::string result_initial_energy(str_initial_energy);
// output += ("\n"+result_initial_energy + "\n");
// delete[] str_initial_energy;

// str_size = mpfr_snprintf(nullptr, 0, "%.Rf", (*ptr).total_energy_);
// char *str_total_energy = new char[str_size + 1];
// mpfr_snprintf(str_total_energy, str_size + 1, "%.Rf", (*ptr).total_energy_);
// std::string result_total_energy(str_total_energy);
// output += (result_total_energy + "\n");
// delete[] str_total_energy;

//   str_size = mpfr_snprintf(nullptr, 0, "%.Rf", (*ptr).cinetic_energy_);
// char *str_cinetic_energy = new char[str_size + 1];
// mpfr_snprintf(str_cinetic_energy, str_size + 1, "%.Rf", (*ptr).cinetic_energy_);
// std::string result_cinetic_energy(str_cinetic_energy);
// output += (result_cinetic_energy + "\n");
// delete[] str_cinetic_energy;

//   str_size = mpfr_snprintf(nullptr, 0, "%.Rf", (*ptr).potential_energy_);
// char *str_potential_energy = new char[str_size + 1];
// mpfr_snprintf(str_potential_energy, str_size + 1, "%.Rf", (*ptr).potential_energy_);
// std::string result_potential_energy(str_potential_energy);
// output += (result_potential_energy + "\n");
// delete[] str_potential_energy;

//   str_size = mpfr_snprintf(nullptr, 0, "%.Rf", (*ptr).mechanic_energy_);
// char *str_mechanic_energy_ = new char[str_size + 1];
// mpfr_snprintf(str_mechanic_energy_, str_size + 1, "%.Rf", (*ptr).mechanic_energy_);
// std::string result_mechanic_energy_(str_mechanic_energy_);
// output += (result_mechanic_energy_ + "\n");
// delete[] str_mechanic_energy_;

//   str_size = mpfr_snprintf(nullptr, 0, "%.Rf", (*ptr).lost_energy_);
// char *str_lost_energy_ = new char[str_size + 1];
// mpfr_snprintf(str_lost_energy_, str_size + 1, "%.Rf", (*ptr).lost_energy_);
// std::string result_lost_energy_(str_lost_energy_);
// output += (result_lost_energy_ + "\n");
// delete[] str_lost_energy_;


}
output += oss.str();

      text2.setString(output);
      text2.setPosition(0,100);


////drawing trajectory
        renderTexture.draw(traj);
      

////drawings planet
      for (unsigned int i = 0; i < (*ptr).size(); ++i) {
      if (animation) {
          traj.append(sf::Vertex(sf::Vector2f((*ptr)[i].x, (*ptr)[i].y),colors[i%colors.size()]));}


        float r = (*ptr)[i].r;

        sf::FloatRect planetBounds((*ptr)[i].x + camera.x - r,(*ptr)[i].y + camera.y - r, 2 * r, 2 * r);


        if (planetBounds.intersects(visibleArea)) {
        ////draw only visible planets

          planet.setPosition((*ptr)[i].x, (*ptr)[i].y);
          planet.setOrigin(r, r);
          planet.setRadius(r);
          planet.setTexture((*ptr)[i].texture);
          renderTexture.draw(planet);

        }

      }


     ///adjusting display
      renderTexture.display();

      sf::View customView = evolvewindow.getDefaultView();
      customView.move(-camera.x, -camera.y);
      renderTexture.setView(customView);
      sf::Sprite sprite(renderTexture.getTexture());
      evolvewindow.draw(sprite);
     evolvewindow.draw(text2);

      evolvewindow.display();

      if(day%1440==0){
        if(month<12){
          month++;
        }
        else {month=1;year++;}
      }
      
    
    }

  }  /// while window e evolvewindow

  return 0;
}
