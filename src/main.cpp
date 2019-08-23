#include <iostream>
#include "Game.hpp"
#include <memory>

constexpr int WIDTH = 600;
constexpr int HEIGHT = 600;
constexpr int FPS = 60;

int main() {
    auto game = std::make_unique<Game>(WIDTH, HEIGHT, FPS);
    game->start();
    std::cout << "Score: " << game->score() << std::endl;
    std::cout << "Level: " << game->level() << std::endl;
    return 0;
}