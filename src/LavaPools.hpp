//
// Created by Kevin Godell on 2019-08-26.
//

#ifndef LAVA_RUNNER_LAVAPOOLS_HPP
#define LAVA_RUNNER_LAVAPOOLS_HPP

#include "SDL.h"
#include "Sprite.hpp"
//#include "LavaPool.hpp"
#include "Lava.hpp"
#include <vector>

class LavaPools {
public:
    LavaPools(int t_x, int t_y, int t_w, int t_h, double t_pool_density = 1.0);

    void render(SDL_Renderer *t_renderer) const;

    SDL_bool isCollide(const Sprite &t_other_sprite) const;

    void generatePools();

    void setPoolDensity(double t_pool_density);

private:
    int m_x;
    int m_y;
    int m_w;
    int m_h;
    std::vector<Lava> m_lava_pools;
    double m_pool_density;
};

#endif //LAVA_RUNNER_LAVAPOOLS_HPP