#pragma once
#include <iostream>
#include <vector>
#include <ctime>

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

	//Игровые объекты
	sf::RectangleShape enemy;
	std::vector<sf::RectangleShape> enemies;

	//ИГРОВАЯ ЛОГИКА (ода бейби)
	int points;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;

	//Позиции мышки
	sf::Vector2i mousePosWindow;


	//Приватные функции
	void initVars();
	void initWindow();
	void initEnemies();
public:
	// Конструкторы и деконструкторы

	GameEngine();
	virtual ~GameEngine();

	// Accessors (хз че это, позже разберусь)
	const bool running() const;


	//Функции
	void spawnEnemy();
	void pollEvents();
	void update();
	void updateEnemies();
	void renderEnemies();
	void updateMousePositions();
	void render();


};
