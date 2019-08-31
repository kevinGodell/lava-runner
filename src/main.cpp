#include <iostream>
#include "Game.hpp"
#include <memory>

constexpr Uint32 WIDTH = 600;
constexpr Uint32 HEIGHT = 600;
constexpr Uint32 FPS = 60;

int main() {
    auto game = std::make_unique<Game>(WIDTH, HEIGHT, FPS);
    game->run();
    std::cout << "Score: " << game->currentScore() << std::endl;
    std::cout << "High Score: " << game->highScore() << std::endl;
    return 0;
}