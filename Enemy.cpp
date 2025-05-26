#include "Enemy.h"
#include "Bullet.h"

void Enemy::initVars()
{
    this->alien = new sf::Sprite(*alienTexture);

    this->alien->setPosition(sf::Vector2f(50.f, 10.f));
    this->alien->setScale({ 5.f,5.f });

    this->enemyBullet.setSize({ 5.f, 30.f });
    this->enemyBullet.setFillColor(sf::Color::Red);
    this->enemyBullet.setPosition({ -100.f, -100.f });

    //игровая логика
    wantToShootRangeStart = 3.f;
    wanttoShootRangeEnd = 10.f;
    shootTime = wantToShootRangeStart + static_cast<float>(rand()) / RAND_MAX * (wanttoShootRangeEnd - wantToShootRangeStart);
    enemySpeed = 1.f;
    Left0Right1 = 1;
    state = EnemyState::Alive;
    deathClock.reset();
}

void Enemy::spawn(float x, float y) {
    this->alien->setPosition({ x, y });
}

EnemyState Enemy::getState() const
{
    return state;
}

const std::vector<Bullet>& Enemy::getBullets() const {
    return enemyBullets;
}

void Enemy::RandomShoot() {
    this->enemyBullet.move({ 0.f, 5.f });
    if (shootClock.getElapsedTime().asSeconds() > shootTime) {
        float shootTime = wantToShootRangeStart + static_cast<float>(rand()) / RAND_MAX * (wanttoShootRangeEnd - wantToShootRangeStart);
        enemyBullets.emplace_back(alien->getPosition().x + 20, alien->getPosition().y);
        shootClock.restart();
    }
}

sf::Vector2f Enemy::getPosition() {
    return this->alien->getPosition();
}

void Enemy::die() {
    if (state == EnemyState::Alive) {
        state = EnemyState::Dying;
        this->alien->setTexture(*alienDiedTexture);
        deathClock.restart();
    }
}

bool Enemy::checkCollision()
{
    if ((alien->getPosition().x <= 0.f) || (alien->getPosition().x + alien->getGlobalBounds().size.x >= 640.f)) {
        return true;
    }
    else return false;
}

void Enemy::changeDirection()
{
    Left0Right1 = !Left0Right1;
}

void Enemy::update(sf::RectangleShape& bullet)
{
    //проверка на столкновение
    if (this->alien->getGlobalBounds().findIntersection(bullet.getGlobalBounds())) {
        Enemy::die();
        bullet.setPosition({ -200.f,-200.f });
    }
    //движения влево-вправо
    float direction = (this->Left0Right1 == 1) ? enemySpeed : -enemySpeed;
    alien->move({ direction, 0.02f });


    //покадровая анимация
    if (animationClock.getElapsedTime().asSeconds() > 1) {
        if (animationFrame0and1) {
            if (state == EnemyState::Alive) {
                alien->setTexture(*alienShootTexture);
                animationFrame0and1 = false;
            }
        }
        else {
            if (state == EnemyState::Alive) {
                alien->setTexture(*alienTexture);
                animationFrame0and1 = true;
            }
        }
        animationClock.restart();
    }
    
    //анимация на смерть
    if (deathClock.getElapsedTime().asSeconds() > 0.2f) {
        state = EnemyState::Dead;
    }

    //рандомная стрелялка
    RandomShoot();

    //движение пуль

    for (auto it = enemyBullets.begin(); it != enemyBullets.end(); ) {
        it->update();
        if (it->getPosition().y > 640.f) {
            it = enemyBullets.erase(it);  // erase возвращает следующий итератор
        }
        else {
            ++it;
        }
    }
}

void Enemy::draw(sf::RenderWindow& window)
{
    window.draw(*alien);
    for (auto& e : enemyBullets) {
        e.draw(window);
    }
}

//КОНСТРУКТОР И ДЕКОНСТРУКТОР

Enemy::Enemy(sf::Texture& textureAlive, sf::Texture& textureDied, sf::Texture& textureShoot)
    : alienTexture(&textureAlive), alienDiedTexture(&textureDied), alienShootTexture(&textureShoot) 
{
    initVars();
}

Enemy::~Enemy() {

}



   
   