//
// Created by Kevin Godell on 2019-08-26.
//

#ifndef LAVA_RUNNER_LAVAPOOLS_HPP
#define LAVA_RUNNER_LAVAPOOLS_HPP

#include "SDL.h"
#include "Sprite.hpp"
#include "LavaPool.hpp"
#include <vector>

class LavaPools {
public:
    LavaPools(int t_x, int t_y, int t_w, int t_h, Uint32 t_row_count, Uint32 t_count_per_row);
    void render(SDL_Renderer *t_renderer) const;
    SDL_bool isCollide(const Sprite &t_other_sprite) const;

private:
    mutable Uint8 m_green_level;
    int m_x;
    int m_y;
    int m_w;
    int m_h;
    Uint32 m_row_count;
    Uint32 m_count_per_row;
    std::vector<SDL_Rect> m_lava_pools;
    std::vector<LavaPool> m_lava_pools2;
};


#endif //LAVA_RUNNER_LAVAPOOLS_HPP
