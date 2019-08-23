//
// Created by Kevin Godell on 2019-08-22.
//

#ifndef LAVA_RUNNER_PLAYER_HPP
#define LAVA_RUNNER_PLAYER_HPP

#include "RectBase.hpp"
#include <SDL.h>

class Player : public RectBase {
public:
    Player(int x, int y, int w, int h);

    void render(SDL_Renderer *t_renderer) override;
};

#endif //LAVA_RUNNER_PLAYER_HPP