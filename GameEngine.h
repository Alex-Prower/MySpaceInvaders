#pragma once
#include <iostream>
#include <vector>
#include <ctime>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Window/Event.hpp>

//�� ��� ���� ������

class GameEngine
{
private:
	//����������
	//������
	sf::RenderWindow* MainGame;
	sf::VideoMode videomode;

	//������� �������
	sf::RectangleShape enemy;
	std::vector<sf::RectangleShape> enemies;

	//������� ������ (��� �����)
	int points;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;

	//������� �����
	sf::Vector2i mousePosWindow;


	//��������� �������
	void initVars();
	void initWindow();
	void initEnemies();
public:
	// ������������ � ��������������

	GameEngine();
	virtual ~GameEngine();

	// Accessors (�� �� ���, ����� ���������)
	const bool running() const;


	//�������
	void spawnEnemy();
	void pollEvents();
	void update();
	void updateEnemies();
	void renderEnemies();
	void updateMousePositions();
	void render();


};
