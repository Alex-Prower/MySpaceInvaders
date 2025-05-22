#pragma once
#include <iostream>
#include <vector>
#include <ctime>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Window/Event.hpp>
#include "Enemy.h"

//Ну это типо движка

class GameEngine
{
private:
	//Переменные
	//Окошко
	sf::RenderWindow* MainGame;
	sf::VideoMode videomode;
	sf::Clock clockAlien;
	sf::Clock alienShoot;
	sf::Clock alienAnimation;
	sf::Time timerAnimationAlienDeath;

	//Игровые объекты
	//sf::RectangleShape enemy;
	sf::Texture playerTexture;
	sf::Texture playerDeadTexture;
	sf::Texture invaderTexture;
	sf::Texture invaderDiedTexture;
	sf::Texture invaderShootTexture;
	std::vector<Enemy> enemies;
	sf::RectangleShape playerBullet;
	sf::Sprite* player;

	//ИГРОВАЯ ЛОГИКА (ода бейби)
	int points;
	int dist;

	bool needToChangeDirection;
	bool Left0Right1;
	bool enemiesSpawned;
	bool bulletInAir;
	bool isPlayerDead;

	float enemySpeed;

	//Приватные функции
	void initVars();
	void initWindow();
	void initPlayer();
	void spawnEnemy();
	void pollEvents();
	void updateEnemies();
	void updatePlayer();
	void renderEnemies();
	void spawnPlayerBullet();
	void updateBullets();
public:
	// Конструкторы и деконструкторы

	GameEngine();
	virtual ~GameEngine();

	// Accessors (хз че это, позже разберусь)
	const bool running() const;

	//Функции
	void update();
	void render();


};
