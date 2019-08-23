#include <iostream>
#include "Game.hpp"

int main() {
    std::cout << "Hello, World!" << std::endl;
    Game game(600, 600, 60);
    game.start();
    std::cout << "Score: " << game.score() << std::endl;
    std::cout << "Level: " << game.level() << std::endl;
    return 0;
}