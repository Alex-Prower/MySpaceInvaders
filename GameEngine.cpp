#include "GameEngine.h"
#include "Enemy.h"

//Приватные функции
void GameEngine::initVars()
{
    this->font.openFromFile("Sprites/msdos2.ttf"); // ДА, Я ЗНАЮ, ЛЕНИВО
    this->youWon = new sf::Text(font); // менять шрифт здесь
    this->youWon->setString("You won!!! Press ESCAPE to exit! :)");
    this->youWon->setPosition({ 60, 150 });
    this->MainGame = nullptr;   // ИГРОВАЯ ЛОГИКА
    this->enemySpeed = 1.f; //если надо чекнуть место спрайтов, пиши 0
    this->points = 0;
    this->Left0Right1 = 1;

    this->playerTexture.loadFromFile("Sprites/ship.png");
    this->playerDeadTexture.loadFromFile("Sprites/death.png");
    this->invaderTexture.loadFromFile("Sprites/invader.png");
    this->invaderDiedTexture.loadFromFile("Sprites/invaderdeath.png");
    this->invaderShootTexture.loadFromFile("Sprites/invadershoot.png");
    this->player = new sf::Sprite(playerTexture);

    this->enemiesSpawned = false;
    this->bulletInAir = false;
    this->isPlayerDead = false;
}

void GameEngine::initWindow()
{
    this->videomode.size = { 640, 640 };
    this->MainGame = new sf::RenderWindow(this->videomode, "Space Invaders", sf::Style::Close);
    this->MainGame->setFramerateLimit(30);
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
{
    this->initVars();
    this->initWindow();
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
    * - добавляет в вектор врага
    */
    //Спавн врага
    if (!enemiesSpawned) {
        const int dist = 75;
        for (int i = 1; i < 10; i++) {
            if (i <= 7) {
                for (float y : {30.f, 130.f}) {
                    enemies.emplace_back(invaderTexture, invaderDiedTexture, invaderShootTexture); // создаём
                    enemies.back().spawn((dist * i) - ((int)y % 2 ? 10 : 30), y); // настраиваем
                }
                for (float y : {80.f, 180.f}) {
                    enemies.emplace_back(invaderTexture, invaderDiedTexture, invaderShootTexture); // создаём
                    enemies.back().spawn((dist * i) - ((int)y % 2 ? 10 : 5), y); // настраиваем
                }
            }
        }
        enemiesSpawned = true;
    }
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
void GameEngine::updateEnemies()
{
    this->spawnEnemy();
  
    for (auto& e : enemies) {
        if (e.checkCollision()) {
            needToChangeDirection = true;
            break;
        }
    }

    if (needToChangeDirection) {
        for (auto& e : enemies) {
            e.changeDirection();
        }
        needToChangeDirection = false;
    }

    for (auto& e : enemies) {
        e.update(playerBullet);
    }

    this->enemies.erase(
        std::remove_if(this->enemies.begin(), this->enemies.end(),
            [](const Enemy& e) {
                return e.getState() == EnemyState::Dead;
            }),
        this->enemies.end()
    );
}

void GameEngine::updatePlayer()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A)) // влево
        if (!isPlayerDead)
        player->move({ -4.f, 0.f });
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D)) // вправо
        if (!isPlayerDead)
        player->move({ 4.f, 0.f });
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Z) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Enter))// стрелять
        if (!isPlayerDead)
            spawnPlayerBullet();

    if (player->getPosition().x <= 0.f) {
        player->setPosition({ 0.f, 600.f });
    }
    else if (player->getPosition().x + player->getGlobalBounds().size.x >= 640.f) {
        player->setPosition({640.f - player->getGlobalBounds().size.x, 600.f});
    }

    for (auto& e : enemies) {
        if (isPlayerDead) break; 
        else for (auto& k : e.getBullets()) {
            if (k.getBounds().getGlobalBounds().findIntersection(player->getGlobalBounds())) {
                player->setTexture(playerDeadTexture);
                isPlayerDead = true;
          }

        }
    }
}

void GameEngine::updateBullets()
{
    //ПУЛЯ ИГРОКА
    if (bulletInAir) {
        playerBullet.move({ 0.f, -15.f }); // вверх по экрану
        if (playerBullet.getPosition().y < -60.f) {
            bulletInAir = false;
            playerBullet.setPosition({ -100.f, -100.f }); // убираем за экран
        }
    }
}

void GameEngine::renderEnemies()
{
    //рендер врагов
    for (auto& e : this->enemies)
    {
        e.draw(*MainGame);
    }
}


void GameEngine::render() {
    this->MainGame->clear();
    //объекты
    if (enemies.empty()) {
        this->MainGame->draw(*youWon);
    }
    this->renderEnemies();
    this->MainGame->draw(*player);
    this->MainGame->draw(playerBullet);
    this->MainGame->display();
}

void GameEngine::update() {
    this->pollEvents();
    this->updateEnemies();
    this->updatePlayer();
    this->updateBullets();
}

