#include "Game.hpp"
#include "SDL.h"
#include <memory>

constexpr Uint32 WIDTH = 600;
constexpr Uint32 HEIGHT = 600;
constexpr Uint32 FPS = 60;

int main() {
    auto game = std::make_unique<Game>(WIDTH, HEIGHT, FPS);
    game->run();
    SDL_Log("Score: %d", game->currentScore());
    SDL_Log("High Score: %d", game->highScore());
    return 0;
}