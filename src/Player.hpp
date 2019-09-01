//
// Created by Kevin Godell on 2019-08-22.
//

#ifndef LAVA_RUNNER_PLAYER_HPP
#define LAVA_RUNNER_PLAYER_HPP

#include "Sprite.hpp"
#include "SDL.h"

class Player : public Sprite {
public:
    Player(int t_x, int t_y, int t_w, int t_h);

    void render(SDL_Renderer *t_renderer) const override;

    void resetRect() override;

    void incX(int t_x);

    void incY(int t_y);

    void setX(int t_x);

    void setY(int t_y);
};

#endif //LAVA_RUNNER_PLAYER_HPP