#include "GameEngine.h"

//Приватные функции
void GameEngine::initVars()
{
    this->MainGame = nullptr;
    this->texture.loadFromFile("texture.png");    // ИГРОВАЯ ЛОГИКА
    this->points = 0;
    this->Left0Right1 = 0;
    this->enemySpawnTimerMax = 5.f;
    this->enemySpawnTimer = this->enemySpawnTimerMax;
    this->maxEnemies = 1;
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

//Конструктор и деконструктор
GameEngine::GameEngine() {
    this->initVars();
    this->initWindow();
    this->initEnemies();
}

GameEngine::~GameEngine() {
    delete this->MainGame;
}

//Аксессор
const bool GameEngine::running() const
{
    return this->MainGame->isOpen();
}



//Функции

void GameEngine::spawnEnemy()
{
    /* @return void
    * Спавнит врагов и устанавливает цвет с позициями
    * - ставит рандомную позицию (у меня потом будет НЕ рандомная??)
    * - ставит рандомный цвет
    * - добавляет в вектор врага
    */

    this->enemy.setPosition({
            static_cast<float>(rand() % static_cast<int>(this->MainGame->getSize().x - this->enemy.getSize().x)),
            0.f });
    this->enemy.setFillColor(sf::Color::Green);
    this->enemy.setOutlineColor(sf::Color::Red);
    this->enemy.setOutlineThickness(5.f);

    //Спавн врага
    this->enemies.push_back(this->enemy);
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


//Функции

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
    //Таймер по спавну врагов (снесётся позже, когда я пройду туториал с ютаба, потому чт нафиг ненужон
    if (this->enemies.size() < this->maxEnemies) {
        if (this->enemySpawnTimer >= this->enemySpawnTimerMax) {
            //спавн перса + сброс таймера
            this->spawnEnemy();
            this->enemySpawnTimer = 0.f;
        }
        else
            this->enemySpawnTimer += 1.f;
    }

    for (auto &e : this->enemies)
    {
        //Коллизия
        //Право
        if (this->Left0Right1 == 0) {
            e.move({ -2.f, 0.f });
            if (e.getPosition().x < 0.f) this->Left0Right1 = 1;
        }
        if (this->Left0Right1 == 1) {
            e.move({ 2.f, 0.f });
            if ((e.getPosition().x + 50) > 640.f) this->Left0Right1 = 0;
        }
        //Вверх
    }
}

void GameEngine::renderEnemies()
{
    //рендер врагов
    for (auto& e : this->enemies)
    {
        this->MainGame->draw(e);
    }
}


void GameEngine::render() {
    this->MainGame->clear();
    //объекты
    this->renderEnemies();
    this->MainGame->display();
}

/*sf::RectangleShape player({ 50, 50 });
  this->player.setFillColor(sf::Color::Green);
  this->player.setPosition({ 300, 300 });

  sf::RectangleShape bullet({ 10,30 });
  this->bullet.setFillColor(sf::Color::Red);

  this->MainGame->draw(player);
  this->MainGame->draw(bullet);*/
