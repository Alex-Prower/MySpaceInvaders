#include "GameEngine.h"

//��������� �������
void GameEngine::initVars()
{
    this->MainGame = nullptr;

    // ������� ������
    this->points = 0;
    this->enemySpawnTimerMax = 1000.f;
    this->enemySpawnTimer = this->enemySpawnTimer;
    this->maxEnemies = 5;
}

void GameEngine::initWindow()
{
    this->videomode.size = { 640, 640 };
    this->MainGame = new sf::RenderWindow(this->videomode, "My windowwwww", sf::Style::Close);
    this->MainGame->setFramerateLimit(60);
}

void GameEngine::initEnemies()
{
    this->enemy.setPosition(sf::Vector2f(10.f, 10.f));
    this->enemy.setSize(sf::Vector2f(100.f, 100.f));
    this->enemy.setScale(sf::Vector2f(0.5f, 0.5f));
    this->enemy.setFillColor(sf::Color::Cyan);
    this->enemy.setOutlineColor(sf::Color::Green);
    this->enemy.setOutlineThickness(1.f);
}

//����������� � �������������
GameEngine::GameEngine() {
    this->initVars();
    this->initWindow();
    this->initEnemies();
}

GameEngine::~GameEngine() {
    delete this->MainGame;
}

//��������
const bool GameEngine::running() const
{
    return this->MainGame->isOpen();
}



//�������

void GameEngine::spawnEnemy()
{
    /* @return void
    * ������� ������ � ������������� ���� � ���������
    * - ������ ��������� ������� (� ���� ����� ����� �� ���������??)
    * - ������ ��������� ����
    * - ��������� � ������ �����
    */

    this->enemy.setPosition(
        sf::Vector2f(
            static_cast<float>(rand() % static_cast<int>(this->MainGame->getSize().x - this->enemy.getSize().x)),
            static_cast<float>(rand() % static_cast<int>(this->MainGame->getSize().y - this->enemy.getSize().y))
        )
    );



}

void GameEngine::pollEvents()
{
    while (const std::optional event = MainGame->pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            MainGame->close();
        }
        else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                MainGame->close();
        }
    }
}


//�������

void GameEngine::updateMousePositions()
{
    this->mousePosWindow = sf::Mouse::getPosition(*this->MainGame);
}

void GameEngine::update() {
    this->pollEvents();

    this->updateMousePositions();

    this->updateEnemies();
}

void GameEngine::updateEnemies()
{
    //������ �� ������ ������ (������� �����, ����� � ������ �������� � �����, ������ �� ����� �������
    if (this->enemies.size() < this->maxEnemies) {
        if (this->enemySpawnTimer >= this->enemySpawnTimerMax) {
            //����� ����� + ����� �������
            this->spawnEnemy();
            this->enemySpawnTimer = 0.f;
        }
        else
            this->enemySpawnTimer += 1.f;
    }
}

void GameEngine::renderEnemies()
{

}


void GameEngine::render() {
    this->MainGame->clear();
    //�������
    this->renderEnemies();
    this->MainGame->draw(this->enemy);
    this->MainGame->display();
}

/*sf::RectangleShape player({ 50, 50 });
  this->player.setFillColor(sf::Color::Green);
  this->player.setPosition({ 300, 300 });

  sf::RectangleShape bullet({ 10,30 });
  this->bullet.setFillColor(sf::Color::Red);

  this->MainGame->draw(player);
  this->MainGame->draw(bullet);*/
