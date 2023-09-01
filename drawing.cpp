#include "Graphic.hpp"

void gr::drawing::drawArrow(sf::Vector2f start, sf::Vector2f tip,
                            sf::Vector2f direction, const sf::Color& c,
                            sf::RenderWindow& window) {
  // Drawing the first segment
  sf::Vertex line1[] = {sf::Vertex(start, c), sf::Vertex(tip, c)};
  window.draw(line1, 2, sf::Lines);

  // Drawing the first part of the tip
  float rotationAngle = 160.0f;
  sf::Transform transformation;
  transformation.rotate(rotationAngle);
  sf::Vector2f firstvector = transformation.transformPoint(0.1f * direction);
  sf::Transform translate;
  translate.translate(tip);
  firstvector = translate.transformPoint(firstvector);
  sf::Vertex line2[] = {sf::Vertex(tip, c), sf::Vertex(firstvector, c)};
  window.draw(line2, 2, sf::Lines);

  // Drawing the second part of the tip
  float angle = 200.0f;
  sf::Transform transf;
  transf.rotate(angle);
  sf::Vector2f secondvector = transf.transformPoint(0.1f * direction);
  secondvector = translate.transformPoint(secondvector);
  sf::Vertex line3[] = {sf::Vertex(tip, c), sf::Vertex(secondvector, c)};
  window.draw(line3, 2, sf::Lines);
}

void gr::drawing::drawPlanet(const G::PlanetState& planet,
                             sf::Vector2f translate, const sf::Color* color,
                             sf::RenderWindow& window,
                             sf::FloatRect& visibleArea, bool boolean) {
  sf::CircleShape circle(0.f);
  float r = planet.r;

  sf::FloatRect planetBounds(planet.x + translate.x - r,
                             planet.y + translate.y - r, 2 * r, 2 * r);
  if (planetBounds.intersects(visibleArea)) {
    circle.setPosition(planet.x + translate.x, planet.y + translate.y);

    /// drawing side
    if (color != nullptr) {
      circle.setRadius(r + 3);
      circle.setOrigin(r + 3, r + 3);
      circle.setFillColor(*color);
      window.draw(circle);
    }

    /// draw planet
    circle.setRadius(r);
    circle.setOrigin(r, r);
    circle.setFillColor(sf::Color::White);
    circle.setTexture(planet.texture);
    window.draw(circle);

    ////drawing arrow
    sf::Vector2f start(static_cast<float>(planet.x + translate.x),
                       static_cast<float>(planet.y + translate.y));
    sf::Vector2f end(
        static_cast<float>(planet.x + 500 * planet.v_x + translate.x),
        static_cast<float>(planet.y + 500 * planet.v_y + translate.y));
    sf::Vector2f dir(static_cast<float>(500 * planet.v_x),
                     static_cast<float>(500 * planet.v_y));
    if (boolean) {
      if (color != nullptr) {
        drawArrow(start, end, dir, *color, window);
      } else {
        drawArrow(start, end, dir, sf::Color::White, window);
      }
    }
  }
}
