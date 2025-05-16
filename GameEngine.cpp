#include "GameEngine.h"

//Приватные функции
void GameEngine::initVars()
{
    this->MainGame = nullptr;   // ИГРОВАЯ ЛОГИКА
    this->enemySpeed = 2.f; //если надо чекнуть место спрайтов, пиши 0
    this->points = 0;
    this->Left0Right1 = 1;
    this->alienTexture.loadFromFile("invader.png");
    this->enemy = new sf::Sprite(alienTexture);
    this->enemiesSpawned = false;
}

void GameEngine::initWindow()
{
    this->videomode.size = { 640, 640 };
    this->MainGame = new sf::RenderWindow(this->videomode, "My windowwwww", sf::Style::Close);
    this->MainGame->setFramerateLimit(30);
}

void GameEngine::initEnemies()
{
    this->enemy->setPosition(sf::Vector2f(50.f, 10.f));
    this->enemy->setScale({ 5.f, 5.f });
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
    //Спавн врага
    if (enemiesSpawned == false) {
        for (int i{ 1 }; i < 10; i++) {
            int dist = 75; //расстояние между врагами
            if (i <= 5) {
                this->enemy->setPosition({ static_cast<float>(dist * i) - 10, 30.f });
                this->enemies.push_back(*enemy);
                this->enemy->setPosition({ static_cast<float>(dist * i) + 10, 80.f });
                this->enemies.push_back(*enemy);
            }
        }
    }
    enemiesSpawned = true;
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
    this->spawnEnemy();
    for (auto &e : this->enemies)
    {
        if (e.getPosition().x <= 0.f) {
            this->Left0Right1 = 1;
            break;
        }
        else if (e.getPosition().x + e.getGlobalBounds().size.x >= 640.f) {
            this->Left0Right1 = 0;
            break;
        }
    }
    float direction = (this->Left0Right1 == 1) ? 1.f : -1.f;
    for (auto& e : this->enemies) {
        e.move({ direction * 2.f * this->enemySpeed, 0.f });
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
