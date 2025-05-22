#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
#include "Bullet.h"

enum class EnemyState { Alive, Dying, Dead };

class Enemy
{
private:
	sf::Texture* alienTexture;
	sf::Texture* alienShootTexture;
	sf::Texture* alienDiedTexture;
	sf::Sprite* alien;
	sf::RectangleShape enemyBullet;
	sf::Clock animationClock;
	sf::Clock deathClock;
	sf::Clock shootClock;

	float shootTime;
	float enemySpeed;
	float wantToShootRangeStart;
	float wanttoShootRangeEnd;
	bool Left0Right1;
	bool animationFrame0and1;
	EnemyState state;
	std::vector<Bullet> enemyBullets;

	void die();
	void initVars();
	void RandomShoot();
public:
	Enemy(sf::Texture& textureAlive, sf::Texture& textureDied, sf::Texture& textureShoot);
	virtual ~Enemy();
	void changeDirection();
	bool checkCollision();

	const std::vector<Bullet>& getBullets() const;
	void update(sf::RectangleShape& bullet);
	void draw(sf::RenderWindow& window);
	sf::Vector2f getPosition();
	void spawn(float x, float y);

	EnemyState getState() const;
	bool isAliveNow() const;
	

};

