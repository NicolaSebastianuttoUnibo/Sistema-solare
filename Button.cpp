#include "Graphic.hpp"


gr::Button::Button(const sf::Vector2f& position, const sf::Vector2f& size, const std::string& text,
              const sf::Color& buttonColor, const sf::Color& textColor, const sf::Font& font, bool b)  {
 show_=b;


   shape_.setPosition(position);
   shape_.setSize(size);
   shape_.setFillColor(buttonColor);


   buttonText_.setString(text);
   buttonText_.setCharacterSize(20);
   buttonText_.setFillColor(textColor);
   buttonText_.setFont(font);


   // Calculate text position to center it within the button
   buttonText_.setPosition(position.x + size.x / 2 - buttonText_.getLocalBounds().width / 2,
                          position.y + size.y / 2 - buttonText_.getLocalBounds().height / 2);
}


void gr::Button::draw(sf::RenderWindow& window) {
   if(show_){
   window.draw(shape_);
   window.draw(buttonText_);
   }
}


bool gr::Button::isClicked(const sf::Vector2i& mousePosition) {
   sf::FloatRect buttonBounds = shape_.getGlobalBounds();
   return buttonBounds.contains(sf::Vector2f(mousePosition));
}


void gr::Button::hide(){
   show_=false;
}
void gr::Button::show(){
   show_=true;
}
bool gr::Button::isVisible(){
   return show_;
}


void gr::Button::setText(std::string s){
   buttonText_.setString(s);
}
