#include "GameEngine.h"

//Приватные функции
void GameEngine::initVars()
{
    this->MainGame = nullptr;   // ИГРОВАЯ ЛОГИКА
    this->enemySpeed = 1.f; //если надо чекнуть место спрайтов, пиши 0
    this->points = 0;
    this->Left0Right1 = 1;
    this->alienDeadID = 0;
    this->choosedAlien = NULL;
    this->timerAnimationAlienDeath = sf::seconds(0.5f);
    


    this->alienTexture.loadFromFile("invader.png");
    this->alienDiedTexture.loadFromFile("invaderdeath.png");
    this->alienShootTexture.loadFromFile("invadershoot.png");
    this->playerTexture.loadFromFile("ship.png");
    this->playerDeadTexture.loadFromFile("death.png");

    this->enemy = new sf::Sprite(alienTexture);
    this->player = new sf::Sprite(playerTexture);

    this->enemiesSpawned = false;
    this->bulletInAir = false;
    this->animationAlienDeath = false;
    this->isPlayerDead = false;
}

void GameEngine::initWindow()
{
    this->videomode.size = { 640, 640 };
    this->MainGame = new sf::RenderWindow(this->videomode, "Space Invaders", sf::Style::Close);
    this->MainGame->setFramerateLimit(30);
}

void GameEngine::initEnemies()
{
    this->enemy->setPosition(sf::Vector2f(50.f, 10.f));
    this->enemy->setScale({ 5.f, 5.f });

    this->enemyBullet.setSize({ 5.f, 30.f });
    this->enemyBullet.setFillColor(sf::Color::Red);
}

void GameEngine::initPlayer() {
    this->player->setPosition({ 280.f, 600.f });
    this->player->setScale({ 5.f, 5.f });

    this->playerBullet.setPosition({ -100.f, -100.f }); //будет висеть в неизведанности пока не будет нужен 
    this->playerBullet.setSize({ 5.f, 40.f });
    this->playerBullet.setFillColor(sf::Color::Green);
}

//Конструктор и деконструктор
GameEngine::GameEngine()
    : gen(std::random_device{}()) // ← инициализация генератора
{
    this->initVars();
    this->initWindow();
    this->initEnemies();
    this->initPlayer();
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
            if (i <= 7) {
                this->enemy->setPosition({ static_cast<float>(dist * i) - 10, 30.f });
                this->enemies.push_back(*enemy);
                this->enemy->setPosition({ static_cast<float>(dist * i) - 30, 80.f });
                this->enemies.push_back(*enemy);
                this->enemy->setPosition({ static_cast<float>(dist * i) - 10, 130.f });
                this->enemies.push_back(*enemy);
                this->enemy->setPosition({ static_cast<float>(dist * i) - 30, 180.f });
                this->enemies.push_back(*enemy);
            }
        }
    }
    enemiesSpawned = true;
}

void GameEngine::spawnEnemyBullet(int index)
{
    enemyBullet.setPosition({ enemies[index].getPosition().x+20, enemies[index].getPosition().y});
    bullets.push_back(enemyBullet);
}

void GameEngine::spawnPlayerBullet()
{
    if (!bulletInAir) {
        playerBullet.setPosition({ player->getPosition().x + 30, player->getPosition().y });
        bulletInAir = true;
    }
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

void GameEngine::updateEnemies()
{
    this->spawnEnemy();
    for (auto &e : this->enemies)
    {
        std::uniform_int_distribution<> rangeRandBullet(1, 2);
        if (alienShoot.getElapsedTime().asSeconds() > rangeRandBullet(gen)) {


            std::uniform_int_distribution<> dist(0, enemies.size() - 1);
            int choosedAlien = (dist(gen));  // СПАВН ПУЛИ РАНДОМНОМУ ВРАГУ
            spawnEnemyBullet(choosedAlien); 

            enemies[choosedAlien].setTexture(alienShootTexture);
            alienAnimation.restart();
            std::cout << "Выбранный чел:" << choosedAlien << "\n";
            alienShoot.restart();
            

        }
        if (alienAnimation.getElapsedTime().asSeconds() > 0.5) {
            enemies[choosedAlien].setTexture(alienTexture);
            alienAnimation.reset();
        }
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

void GameEngine::updatePlayer()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A)) // влево
        if (!isPlayerDead)
        player->move({ -4.f, 0.f });
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D)) // вправо
        if (!isPlayerDead)
        player->move({ 4.f, 0.f });
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Z)) // стрелять
        if (!isPlayerDead)
        spawnPlayerBullet();

    if (player->getPosition().x <= 0.f) {
        player->setPosition({ 0.f, 600.f });
    }
    else if (player->getPosition().x + player->getGlobalBounds().size.x >= 640.f) {
        player->setPosition({640.f - player->getGlobalBounds().size.x, 600.f});
    }
}

void GameEngine::updateBullets()
{
    //ПУЛЯ ВРАГА
    for (auto it = bullets.begin(); it != bullets.end(); ) {
        it->move({ 0.f, 10.f });
  
        if (it->getGlobalBounds().size.y < 0.f)
            bullets.erase(it);
        if (it->getGlobalBounds().findIntersection(player->getGlobalBounds())) {
            player->setTexture(playerDeadTexture);
            isPlayerDead = true;
        }

        else {
            ++it;
        }
    }

    //ПУЛЯ ИГРОКА
    if (bulletInAir) {
        playerBullet.move({ 0.f, -15.f }); // вверх по экрану
        for (size_t i = 0; i < enemies.size(); ) {
            if (playerBullet.getGlobalBounds().findIntersection(enemies[i].getGlobalBounds())) {
                std::cout << "есть пробитие \n";
                playerBullet.setPosition({ -100.f, -100.f });// убираем за экран пуд.
                enemies[i].setTexture(alienDiedTexture);
                clockAlien.restart();
                alienDeadID = i;
                animationAlienDeath = true;
            }
            else {
                ++i;
            }
        }


        if (playerBullet.getPosition().y < -60.f) {
            bulletInAir = false;
            playerBullet.setPosition({ -100.f, -100.f }); // убираем за экран
        }
    }
}

void GameEngine::updateAnimation()
{
    if (animationAlienDeath) {
        if (clockAlien.getElapsedTime().asSeconds() > timerAnimationAlienDeath.asSeconds()) {
            enemies.erase(enemies.begin() + alienDeadID); // удалить по индексу
            animationAlienDeath = false;
        }
    }
  
}

void GameEngine::renderEnemies()
{
    //рендер врагов
    for (auto& e : this->enemies)
    {
        this->MainGame->draw(e);
    }

    for (auto& k : this->bullets)
    {
        this->MainGame->draw(k);
    }
}


void GameEngine::render() {
    this->MainGame->clear();
    //объекты
    this->renderEnemies();
    this->MainGame->draw(*player);
    this->MainGame->draw(playerBullet);
    this->MainGame->display();
}

void GameEngine::update() {
    this->pollEvents();

    this->updateMousePositions();
    this->updateAnimation();
    this->updateEnemies();
    this->updatePlayer();
    this->updateBullets();
}