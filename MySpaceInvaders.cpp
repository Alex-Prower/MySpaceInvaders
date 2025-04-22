#include "GameEngine.h"

int main() {
    system("chcp 1251");

    //иниц. времени srand
    std::srand(static_cast<unsigned>(time(NULL)));


    //инициализация игрульки
    GameEngine game;

    while (game.running()) {
        game.update();
        game.render();
    }

    return 0;
}
