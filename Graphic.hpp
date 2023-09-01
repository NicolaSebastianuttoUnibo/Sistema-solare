#ifndef BUTTON_HPP
#define BUTTON_HPP
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <cassert>
#include <filesystem>
#include <string>
#include <vector>

#include "Graphic.hpp"
#include "universe.hpp"

namespace gr {

class Button {
 public:
  Button(const sf::Vector2f& position, const sf::Vector2f& size,
         const std::string& text, const sf::Color& buttonColor,
         const sf::Color& textColor, const sf::Font& fontconst, bool b);

  void draw(sf::RenderWindow& window);
  bool isClicked(const sf::Vector2i& mousePosition);

  void show();
  void hide();
  void setText(std::string s);
  bool isVisible();

 private:
  sf::Vector2f pos_;
  sf::Vector2f size_;

  sf::RectangleShape shape_;
  sf::Text buttonText_;
  bool show_;
};  /// class Button

class TM {
  std::vector<sf::Texture> texture_vector_;
  std::vector<std::string> texture_name_;
  U::FileUniverse* u_;
  const std::string s_;

  void loadAndAssignTextures(std::string folder, U::Universe* universe);

 public:
  TM(const std::string& str, U::FileUniverse* u);
  void tm(const std::string& str, U::FileUniverse* u);
  std::string showAllNameImages();

};  ////class TM

struct drawing {
  static void drawArrow(sf::Vector2f start, sf::Vector2f punta,
                        sf::Vector2f direction, const sf::Color& c,
                        sf::RenderWindow& window);
  static void drawPlanet(const G::PlanetState& planet, sf::Vector2f translate,
                         const sf::Color* color, sf::RenderWindow& window,
                         sf::FloatRect& visibleArea, bool check);

};  ////class drawing

}  // namespace gr

#endif