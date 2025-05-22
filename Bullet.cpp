#include "Bullet.h"

bool Bullet::isPlayerDamaged(sf::Sprite player)
{
    if (this->shape.getGlobalBounds().findIntersection(player.getGlobalBounds())) {
        return true;
    }
    return false;
}

Bullet::Bullet(float x, float y)
{
    this->shape.setSize({ 5.f, 30.f });
    this->shape.setFillColor(sf::Color::Red);
    this->shape.setPosition({ x, y });
    this->speed = 8.f;
}

void Bullet::update() {
    shape.move({ 0.f, speed });
}

void Bullet::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

sf::Vector2f Bullet::getPosition()
{
    return this->shape.getPosition();
}

sf::RectangleShape Bullet::getBounds() const
{
    return shape;
}
