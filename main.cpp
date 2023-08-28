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

#include "Button.hpp"
#include "texturemanagement.hpp"
#include "universe.hpp"

std::vector<sf::Vertex> drawArrow(sf::Vector2f start, sf::Vector2f punta,
                                  sf::Vector2f direction, const sf::Color &c) {
  std::vector<sf::Vertex> arrow(6);  // Creazione di un vettore di vertici

  arrow[0] = sf::Vertex(start);
  arrow[0].color = c;
  arrow[1] = sf::Vertex(punta);
  arrow[1].color = c;

  float rotationAngle = 160.0f;
  sf::Vector2f firstvector(0.1f * direction);
  sf::Transform transformation;
  transformation.rotate(rotationAngle);
  firstvector = transformation.transformPoint(firstvector);

  sf::Transform translate;
  translate.translate(punta);
  firstvector = translate.transformPoint(firstvector);

  float angle = 200.0f;
  sf::Vector2f secondvector(0.1f * direction);

  sf::Transform transf;
  transf.rotate(angle);
  secondvector = transf.transformPoint(secondvector);

  secondvector = translate.transformPoint(secondvector);

  arrow[2] = sf::Vertex(firstvector);
  arrow[2].color = c;

  arrow[3] = sf::Vertex(punta);
  arrow[3].color = c;

  arrow[4] = sf::Vertex(punta);
  arrow[4].color = c;

  arrow[5] = sf::Vertex(secondvector);
  arrow[5].color = c;

  // Restituzione del vettore di vertici
  return arrow;
}

int main() {
  G::Newton newton{};

  U::Universe universo(newton);
  bool selecting{false};
  bool selected;
  bool firstwindow{true};
  bool choosingvalue{false};
  bool followPlanets;
  bool followOnePlanet;
  std::vector<G::PlanetState *> planetsfollowing;

  bool createvector;
  bool animation{false};
  std::string input;
  unsigned int choose{0};
  unsigned int index;
  unsigned int choose2{0};
  std::vector<sf::VertexArray> traj(sf::LineStrip);

  std::vector<std::string> choice = {"Set\nmass(M)",     "Set\npos(P)",
                                     "Set\nvelocity(V)", "Set\nradius(R)",
                                     "Set\ntexture(T)",  "Delete(X)"};

  sf::Vector2<double> camera{400, 400};  // camera

  sf::Font font;
  sf::CircleShape planet(0.f);
  sf::CircleShape contorno(0.f);
  sf::Text text;
  sf::Text text2;

  std::shared_ptr<U::FileUniverse> ptr;
  std::shared_ptr<TM> vettoreditexture;

  std::string response;
  sf::Clock clock;
  sf::Time elapsed;

  try {
    if (!font.loadFromFile("Arial.ttf")) {
      throw std::runtime_error("font non caricato");
    }

    std::cout << "Do you want to open an existing file (o) or do you want to "
                 "create a new one (c)?";
    std::cin >> response;
    if (response == "o" || response == "open") {
      std::cout << "\nChoose the file you want to open (WITHOUT '.txt')\n";
      std::cin >> response;

      ptr = std::make_shared<U::FileUniverse>(newton, response, true);

      vettoreditexture = std::make_shared<TM>("Texture", ptr.get());

    }

    else if (response == "c" || response == "create") {
      std::cout << "\nChoose the name of the new file(WITHOUT '.txt')\n";
      std::cin >> response;

      ptr = std::make_shared<U::FileUniverse>(newton, response, false);

      vettoreditexture = std::make_shared<TM>("Texture", ptr.get());

    }

    else {
      throw std::runtime_error("Invalid input");
    }
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << "\n";
    return 1;
  }

  U::FileUniverse u = *ptr;
  TM tm = *vettoreditexture;
  if (u.size() > 0) {
    camera.x = -u[0].x + 400;
    camera.y = -u[0].y + 400;
  }

  sf::RenderWindow window(sf::VideoMode(800, 800), response + ".txt");
  sf::FloatRect visibleArea(0, 0, window.getSize().x, window.getSize().y);
  window.setFramerateLimit(48);
  sf::RenderWindow evolvewindow(sf::VideoMode(800, 800),
                                "animation of " + response + ".txt");
  sf::FloatRect visibleArea2(0, 0, window.getSize().x, window.getSize().y);
  evolvewindow.setFramerateLimit(48);

  sf::RenderTexture renderTexture;
  renderTexture.create(evolvewindow.getSize().x, evolvewindow.getSize().y);

  evolvewindow.setVisible(false);

  Button save_button(sf::Vector2f(0, 0), sf::Vector2f(150, 90), "Save",
                     sf::Color::Yellow, sf::Color::Black, font, true);
  Button add_button(sf::Vector2f(160, 0), sf::Vector2f(150, 90), "Add\nplanet",
                    sf::Color::Yellow, sf::Color::Black, font, true);
  Button select_button(sf::Vector2f(320, 0), sf::Vector2f(150, 90),
                       "Select\nplanet", sf::Color::Yellow, sf::Color::Black,
                       font, true);
  Button next_button(sf::Vector2f(480, 0), sf::Vector2f(150, 90),
                     "Next\nplanet", sf::Color::Yellow, sf::Color::Black, font,
                     false);
  Button data_button(sf::Vector2f(480, 90), sf::Vector2f(150, 90), "Mass",
                     sf::Color::Yellow, sf::Color::Black, font, false);
  Button evolve_button(sf::Vector2f(640, 0), sf::Vector2f(150, 90), "Animation",
                       sf::Color::Yellow, sf::Color::Black, font, true);

  Button error_button(
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

finestre_aperte:
  while (window.isOpen() || window.isOpen()) {
    if (firstwindow) {
      sf::Event event;
      while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
          window.close();
          evolvewindow.close();
        }

        if (event.type == sf::Event::MouseButtonPressed &&
            event.mouseButton.button == sf::Mouse::Left) {
          /// MOUSE IS CLICKED
          sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

          if (evolve_button.isClicked(mousePosition) &&
              evolve_button.isVisible()) {
            if (u.size() == 0) {
              error_button.show();
            } else {
              window.setVisible(false);
              evolvewindow.setVisible(true);
              firstwindow = false;
              animation = true;
              universo = u;
            }
            traj.resize(u.size());
          }

          evolve_button.hide();

          if (save_button.isClicked(mousePosition) && save_button.isVisible()) {
            selected = false;
            selecting = false;
            u.save();
            evolve_button.show();

          }

          else if (add_button.isClicked(mousePosition) &&
                   add_button.isVisible()) {
            G::PlanetState p{1e10, -camera.x + 400, -camera.y + 400, 0, 0,
                             100,  "default"};
            u.push_back(p);
            u.save();
            tm.tm("Folder", &u);
          }

          else if (select_button.isClicked(mousePosition) &&
                   select_button.isVisible()) {
            selecting = !selecting;
            if (u.size() == 0) {
              selecting = false;
              error_button.show();
            }
            if (selecting) {
              choose = 0;
              select_button.setText("Unselect\nplanet");
              next_button.show();
              selected = false;

            } else {
              select_button.setText("Select\nplanet");
              selected = false;
              next_button.hide();
              data_button.hide();
            }
          }

          else if (next_button.isClicked(mousePosition) &&
                   next_button.isVisible() && u.size() > 0) {
            selected = false;
            choosingvalue = false;
            if (choose < u.size() - 1) {
              choose++;
            } else {
              choose = 0;
            }
            camera.x = -u[choose].x + 400;
            camera.y = -u[choose].y + 400;

          }

          else if (((data_button.isClicked(mousePosition) &&
                     data_button.isVisible()))) {
            choosingvalue = !choosingvalue;

          } else if (((error_button.isClicked(mousePosition) &&
                       error_button.isVisible()))) {
            error_button.hide();
          }

          else {
            if (choosingvalue) {
              if (choose2 == 1) {
                u[choose].x = mousePosition.x - camera.x;
                u[choose].y = mousePosition.y - camera.y;
              }

              if (choose2 == 2) {
                u[choose].v_x = mousePosition.x - camera.x - u[choose].x;
                u[choose].v_y = mousePosition.y - camera.y - u[choose].y;
              }

            }

            else if (selecting) {
              index = u.findNearestPlanet(sf::Vector2i(
                  mousePosition.x - camera.x, mousePosition.y - camera.y));
              /*sf::FloatCircle buttonBounds = shape_.getGlobalBounds();
             return buttonBounds.contains(sf::Vector2f(mousePosition));*/

              float radius = u[index].r;
              float distance = std::sqrt(
                  std::pow(mousePosition.x - (u[index].x + camera.x), 2) +
                  std::pow(mousePosition.y - (u[index].y + camera.y), 2));

              if (distance < radius) {
                if (index == choose) {
                  selected = !selected;
                } else {
                  selected = false;
                  choose = index;
                }
              }
            }

          }  /// fine else

        }  /// fine click sinistra
        if (event.type == sf::Event::MouseButtonPressed &&
            event.mouseButton.button == sf::Mouse::Right && !choosingvalue) {
          sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

          if (data_button.isClicked(mousePosition) && data_button.isVisible()) {
            if (choose2 < choice.size() - 1) {
              choose2++;
            } else {
              choose2 = 0;
            }

            data_button.setText(choice[choose2]);
          }

        }  /// fine click destra

        ////MOVING CAMERA

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
        if (selecting || selected) {
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) {
            data_button.show();
            next_button.show();

            selecting = true;
            choosingvalue = true;
            selected = true;
            choose2 = 0;
            data_button.setText(choice[choose2]);
          }
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
            data_button.show();
            next_button.show();

            selecting = true;
            choosingvalue = true;
            selected = true;
            choose2 = 1;
            data_button.setText(choice[choose2]);
          }
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::V)) {
            data_button.show();
            next_button.show();

            choosingvalue = true;

            selecting = true;
            selected = true;
            choose2 = 2;
            data_button.setText(choice[choose2]);
          }
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
            data_button.show();
            next_button.show();

            selecting = true;
            selected = true;
            choose2 = 3;
            data_button.setText(choice[choose2]);
          }
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) {
            data_button.show();
            next_button.show();
            choosingvalue = true;

            selecting = true;
            selected = true;
            choose2 = 4;
            data_button.setText(choice[choose2]);
          }
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
            next_button.show();
            data_button.show();
            selecting = true;
            selected = true;
            choose2 = 5;
            data_button.setText(choice[choose2]);
          }
        }

      }  ////poll event

      if (choosingvalue) {
        double a;

        std::string t;

        switch (choose2) {
          case 0:
            choosingvalue = true;
            window.setVisible(false);
            std::cout << "Choose mass: ";
            std::cin >> a;
            u[choose].m = a;
            choosingvalue = false;

            break;

          case 3:
            choosingvalue = true;

            window.setVisible(false);
            std::cout << "\nChoose rad: ";
            std::cin >> a;
            u[choose].r = a;
            choosingvalue = false;

            break;

          case 4:
            choosingvalue = true;

            window.setVisible(false);
            system("ls Texture");

            std::cout << "Choose texture: ";
            std::cin >> t;
            u[choose].stringtexture = t;
            tm.tm("Folder", &u);
            choosingvalue = false;

            break;

          case 5:
            if (choose < u.size()) {
              std::cout << u.size();
              u.remove(u[choose]);
            }
            if (u.size() == 0) {
              selecting = false;
              selected = false;
            }
            std::cout << u.size();
            choosingvalue = false;
            choose = 0;
            break;
        }
        u.save();
        window.setVisible(true);

      }  /// choosing value

      std::string output = "camera_x=" + std::to_string(800 - camera.x) +
                           "\ncamera_y=" + std::to_string(800 - camera.y);

      if (selecting) {
        std::ostringstream oss;
        oss << std::scientific
            << std::setprecision(2);  // Set precision as needed

        oss << "\nm=" << u[choose].m << "\nx=" << u[choose].x
            << "\ny=" << u[choose].y << "\nv_x=" << u[choose].v_x
            << "\nv_y=" << u[choose].v_y << "\nr=" << u[choose].r << "\n"
            << u[choose].stringtexture << "\ni=" << index << ",c=" << choose;

        output += oss.str();
      }

      // ...

      text.setString(output);

      window.clear();

      if (selected) {
        data_button.show();
      } else {
        data_button.hide();
      }

      for (unsigned int i = 0; i < u.size(); ++i) {
        float r = u[i].r;

        sf::FloatRect planetBounds(u[i].x + camera.x - r, u[i].y + camera.y - r,
                                   2 * r, 2 * r);

        if (planetBounds.intersects(visibleArea)) {
          planet.setPosition(u[i].x + camera.x, u[i].y + camera.y);
          planet.setOrigin(r, r);
          planet.setRadius(r);
          planet.setTexture(u[i].texture);
          window.draw(planet);

          sf::Vector2f start(static_cast<float>(u[i].x + camera.x),
                             static_cast<float>(u[i].y + camera.y));
          sf::Vector2f end(static_cast<float>(u[i].x + u[i].v_x + camera.x),
                           static_cast<float>(u[i].y + u[i].v_y + camera.y));
          sf::Vector2f dir(static_cast<float>(u[i].v_x),
                           static_cast<float>(u[i].v_y));

          if (selecting) {
            std::vector<sf::Vertex> arrow =
                drawArrow(start, end, dir, sf::Color::White);

            window.draw(arrow.data(), arrow.size(), sf::Lines);
          }

        }  /// se dentro l'area

      }  ////fine for

      if (selecting) {
        float r = u[choose].r;
        sf::Vector2f start(static_cast<float>(u[choose].x + camera.x),
                           static_cast<float>(u[choose].y + camera.y));
        sf::Vector2f end(
            static_cast<float>(u[choose].x + u[choose].v_x + camera.x),
            static_cast<float>(u[choose].y + u[choose].v_y + camera.y));
        sf::Vector2f dir(static_cast<float>(u[choose].v_x),
                         static_cast<float>(u[choose].v_y));

        contorno.setRadius(r + 3);
        contorno.setOrigin(r + 3, r + 3);

        contorno.setFillColor(sf::Color::White);
        if (choosingvalue) {
          contorno.setFillColor(sf::Color::Red);
        } else if (selected) {
          contorno.setFillColor(sf::Color::Yellow);
        }
        contorno.setPosition(u[choose].x + camera.x, u[choose].y + camera.y);
        window.draw(contorno);
        planet.setPosition(u[choose].x + camera.x, u[choose].y + camera.y);
        planet.setOrigin(r, r);
        planet.setRadius(r);
        planet.setTexture(u[choose].texture);
        window.draw(planet);

        std::vector<sf::Vertex> arrow =
            drawArrow(start, end, dir, sf::Color::Green);

        window.draw(arrow.data(), arrow.size(), sf::Lines);
      }  /// seletcing

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
          window.setVisible(true);
          evolvewindow.setVisible(false);
          choose2 = 0;
          firstwindow = true;
          animation = false;
          camera.x = -u[0].x + 400;
          camera.y = -u[0].y + 400;
          traj.clear();
          renderTexture.clear();
          goto finestre_aperte;
        }

        if (!pressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
          animation = !animation;
          pressed = true;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) {
          if (!createvector) {
            followOnePlanet = false;
            followPlanets = false;
            createvector = true;
            planetsfollowing.clear();
            choose2 = 0;
            assert(choose < universo.size());
            planetsfollowing.push_back(&universo[choose]);
          }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
          createvector = false;
          followPlanets = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
          if (createvector && choose2 > 0) {
            choose2--;
          }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
          if (createvector) {
            if (choose2 < planetsfollowing.size() - 1) {
              choose2++;
            } else {
              assert(choose < universo.size());
              planetsfollowing.push_back(&universo[choose]);
              choose2++;
              assert(choose2 < planetsfollowing.size());
            }
          }

        }  /// devi essere nel penultimo elemento altrimenti pushback

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
          if (choose < universo.size() - 1) {
            choose++;
          } else {
            choose = 0;
          }
          assert(choose < universo.size());
          if (createvector) {
            assert(choose2 < planetsfollowing.size());
            planetsfollowing[choose2] = &universo[choose];
          }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
          if (choose > 0) {
            choose--;
          } else {
            choose = universo.size() - 1;
          }
          assert(choose < u.size());
          if (createvector) {
            assert(choose2 < u.size());
            planetsfollowing[choose2] = &universo[choose];
          }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
          if (planetsfollowing.size() > 1) {
            auto it = planetsfollowing.begin() + choose2;
            assert(it != planetsfollowing.end());
            if (choose == planetsfollowing.size() - 1) {
              choose--;
            }
            planetsfollowing.erase((it));
          }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
          followPlanets = true;
          followOnePlanet = false;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
          followPlanets = false;
          followOnePlanet = true;
        }

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

      }  /// poll event
      renderTexture.clear();

      elapsed = clock.restart();
      std::cout << std::to_string(1.0f / elapsed.asSeconds()) + "\n";

      evolvewindow.clear();

      if (animation) {
        unsigned int s = universo.size();
        universo.evolve(1);
        if (s < universo.size()) {
          if (choose >= universo.size()) {
            choose--;
            assert(choose < u.size());
          }
          followPlanets = false;
        }
      }
      if (followOnePlanet) {
        camera.x = 400 - universo[choose].x;
        camera.y = 400 - universo[choose].y;
      }

      else if (followPlanets) {
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

      else if (createvector) {
        std::string s;
        if (choose2 == 0) {
          s = "st";
        } else if (choose2 == 1) {
          s = "nd";
        } else if (choose2 == 2) {
          s = "rd";
        } else {
          s = "th";
        }

        text2.setString("You are following " +
                        std::to_string(planetsfollowing.size()) +
                        " planet(s) and you are choosing the " +
                        std::to_string(choose2 + 1) + s + " planet");

        camera.x = 400 - (*planetsfollowing[choose2]).x;
        camera.y = 400 - (*planetsfollowing[choose2]).y;
        text2.setPosition(universo[choose].x - 400, universo[choose].y - 400);
        renderTexture.draw(text2);
      }

      planet.setTexture(universo[0].texture);

      for (unsigned int i = 0; i < universo.size(); ++i) {
        if (animation) {
          traj[i].append(sf::Vertex(sf::Vector2f(universo[i].x, universo[i].y),
                                    sf::Color::Yellow));
        }

        float r = u[i].r;

        sf::FloatRect planetBounds(universo[i].x + camera.x - r,
                                   universo[i].y + camera.y - r, 2 * r, 2 * r);

        renderTexture.draw(traj[i]);

        if (planetBounds.intersects(visibleArea2)) {
          planet.setPosition(universo[i].x, universo[i].y);

          planet.setOrigin(r, r);
          planet.setRadius(r);
          planet.setTexture(universo[i].texture);
          renderTexture.draw(planet);

        }  /// i pianeti visibili

      }  ////il for per disegnare i pianeti

      renderTexture.display();

      sf::View customView = evolvewindow.getDefaultView();
      customView.move(-camera.x, -camera.y);
      renderTexture.setView(customView);

      sf::Sprite sprite(renderTexture.getTexture());

      evolvewindow.draw(sprite);

      evolvewindow.display();

      renderTexture.clear();

      // customView.move(camera.x, camera.y);
    }

  }  /// while window e evolvewindow

  return 0;
}
