#pragma once
#include <SFML/Graphics.hpp>

class Bullet {
    sf::RectangleShape shape;
    float speed;

public:
    bool isPlayerDamaged(sf::Sprite player);
    Bullet(float x, float y);
    void update();
    void draw(sf::RenderWindow& window);
    sf::RectangleShape getBounds() const;
    sf::Vector2f getPosition();
};

