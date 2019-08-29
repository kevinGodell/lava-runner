//
// Created by Kevin Godell on 2019-08-28.
//

#ifndef LAVA_RUNNER_LAVA_HPP
#define LAVA_RUNNER_LAVA_HPP

#include "Sprite.hpp"
#include "SDL.h"

class Lava : public Sprite {
public:
    Lava(int t_x, int t_y, int t_w, int t_h);

    void render(SDL_Renderer *t_renderer) const override;

private:
    mutable Uint8 m_green;
};


#endif //LAVA_RUNNER_LAVA_HPP