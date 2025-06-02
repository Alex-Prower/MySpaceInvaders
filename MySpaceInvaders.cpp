#include "GameEngine.h"
#include <windows.h>

int main() {
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_HIDE);
    system("chcp 1251");
    sf::RenderWindow menu(sf::VideoMode({ 640, 640 }), "Space Invaders Menu");
    menu.setFramerateLimit(10); // ФПС В МЕНЮ, НЕ В ИГРЕ
    sf::Font font("Sprites/msdos.ttf"); // менять шрифт здесь
    sf::Texture wallpaper("Sprites/wallpaper.png");
    sf::Texture arrowFrame1("Sprites/arrow1.png");
    sf::Texture arrowFrame2("Sprites/arrow2.png");

    sf::Sprite menuWallpaper(wallpaper);
    sf::Sprite arrow(arrowFrame1);


    sf::Text text(font);
    sf::Text playText(font);
    sf::Text quitText(font);
    sf::Text createdByText(font); //бог с ним, оставлю безымянным свое авторство


    text.setString("Space Invaders");
    playText.setString("Play");
    quitText.setString("Quit");

    text.setCharacterSize(40);
    playText.setCharacterSize(40);
    quitText.setCharacterSize(40);
    createdByText.setCharacterSize(40);

    text.setFillColor(sf::Color::White);
    playText.setFillColor(sf::Color::White);
    quitText.setFillColor(sf::Color::White);
    createdByText.setFillColor(sf::Color::White);

    text.setPosition({ 175, 150 });
    playText.setPosition({ 280, 250 });
    quitText.setPosition({ 280, 310 });
    createdByText.setPosition({ 1000, 1000 });

    arrow.setScale({0.5f, 0.5f});
    arrow.setPosition({ 240, 260 });

    bool frame1frame0 = true;
    bool Start1Quit0 = true;
    sf::Clock arrowAnim;

    //инициализация srand по времени
    std::srand(static_cast<unsigned>(time(NULL)));

    while (menu.isOpen())
    {

        // check all the window's events that were triggered since the last iteration of the loop
        while (const std::optional event = menu.pollEvent())
        {
            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>())
                menu.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S)) {
                arrow.setPosition({ 240, 320 });
                Start1Quit0 = false;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W)) {
                arrow.setPosition({ 240, 260 });
                Start1Quit0 = true;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Z) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Enter)) {
                if (Start1Quit0) {
                    menu.close();
                    GameEngine game;

                    while (game.running()) {
                        game.update();
                        game.render();
                    }
                }
                else menu.close();
            }
        }

        if (frame1frame0) arrow.setTexture(arrowFrame1);
        else arrow.setTexture(arrowFrame2);

        if (arrowAnim.getElapsedTime().asSeconds() > 0.7) {
            frame1frame0 = !frame1frame0;
            arrowAnim.restart();
        }

        menuWallpaper.move({ 0.f, -1.f });
        menu.clear(sf::Color::Black);
        menu.draw(menuWallpaper);
        menu.draw(text);
        menu.draw(playText);
        menu.draw(quitText);
        menu.draw(arrow);
        menu.display();
        
    }
    //инициализация игры


   

    return 0;
}
