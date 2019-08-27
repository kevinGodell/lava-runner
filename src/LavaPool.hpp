//
// Created by Kevin Godell on 2019-08-26.
//

#ifndef LAVA_RUNNER_LAVAPOOL_HPP
#define LAVA_RUNNER_LAVAPOOL_HPP

#include "Sprite.hpp"
#include "SDL.h"

class LavaPool : public Sprite {
public:
    LavaPool(int t_x, int t_y, int t_w, int t_h);
    void render(SDL_Renderer *t_renderer) const override;
};


#endif //LAVA_RUNNER_LAVAPOOL_HPP
