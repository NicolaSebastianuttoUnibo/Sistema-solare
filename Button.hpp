#ifndef BUTTON_HPP
#define BUTTON_HPP


#include <SFML/Graphics.hpp>


class Button {
public:
   Button(const sf::Vector2f& position, const sf::Vector2f& size, const std::string& text,
          const sf::Color& buttonColor, const sf::Color& textColor, const sf::Font& fontconst, bool b);


   void draw(sf::RenderWindow& window);
   bool isClicked(const sf::Vector2i& mousePosition);


void show();
void hide();
void setText(std::string s);
bool isVisible();

private:


   sf::RectangleShape shape_;
   sf::Text buttonText_;
   bool show_;
};


#endif // BUTTON_HPP




