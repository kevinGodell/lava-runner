#include <iostream>
#include "Game.hpp"
#include <memory>

constexpr int WIDTH = 600;
constexpr int HEIGHT = 600;
constexpr int FPS = 60;

int main() {
    auto game = std::make_unique<Game>(WIDTH, HEIGHT, FPS);
    game->run();
    std::cout << "Score: " << game->currentScore() << std::endl;
    std::cout << "High Score: " << game->highScore() << std::endl;
    return 0;
}