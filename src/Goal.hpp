//
// Created by Kevin Godell on 2019-08-23.
//

#ifndef LAVA_RUNNER_GOAL_HPP
#define LAVA_RUNNER_GOAL_HPP

#include "RectBase.hpp"
#include <SDL.h>
#include <vector>

class Goal : public RectBase {
public:
    Goal(int x, int y, int w, int h);

    void render(SDL_Renderer *t_renderer) override;

private:
    std::vector<SDL_Rect> m_grid;
};

#endif //LAVA_RUNNER_GOAL_HPP