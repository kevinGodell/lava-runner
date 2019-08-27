//
// Created by Kevin Godell on 2019-08-23.
//

#ifndef LAVA_RUNNER_GOAL_HPP
#define LAVA_RUNNER_GOAL_HPP

#include "Sprite.hpp"
#include "SDL.h"
#include <vector>

class Goal final: public Sprite {
public:
    Goal(int t_x, int t_y, int t_w, int t_h);

    void render(SDL_Renderer *t_renderer) const override;

private:
    std::vector<SDL_Rect> m_grid;
};

#endif //LAVA_RUNNER_GOAL_HPP