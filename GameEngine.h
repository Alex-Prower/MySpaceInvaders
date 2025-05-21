#pragma once
#include <iostream>
#include <vector>
#include <ctime>
#include <random>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Window/Event.hpp>

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
	sf::Texture alienTexture;
	sf::Texture alienShootTexture;
	sf::Texture alienDiedTexture;
	sf::Texture playerTexture;
	sf::Texture playerDeadTexture;

	sf::Sprite* enemy;
	std::vector<sf::Sprite> enemies;
	sf::RectangleShape enemyBullet;
	std::vector<sf::RectangleShape> bullets;
	sf::RectangleShape playerBullet;
	sf::Sprite* player;

	//ИГРОВАЯ ЛОГИКА (ода бейби)
	int points;
	int dist;
	int alienDeadID;
	int choosedAlien;
	std::mt19937 gen; // генератор случайных чисел





	bool Left0Right1;
	bool enemiesSpawned;
	bool bulletInAir;
	bool animationAlienDeath;
	bool isPlayerDead;

	float enemySpeed;


	//Позиции мышки
	sf::Vector2i mousePosWindow;


	//Приватные функции
	void initVars();
	void initWindow();
	void initEnemies();
	void initPlayer();
	void spawnEnemy();
	void pollEvents();
	void updateEnemies();
	void updatePlayer();
	void renderEnemies();
	void updateMousePositions();
	void spawnEnemyBullet(int index);
	void spawnPlayerBullet();
	void updateBullets();
	void updateAnimation();
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
