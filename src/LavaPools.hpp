//
// Created by Kevin Godell on 2019-08-26.
//

#ifndef LAVA_RUNNER_LAVAPOOLS_HPP
#define LAVA_RUNNER_LAVAPOOLS_HPP

#include "SDL.h"
#include "Sprite.hpp"
#include "Lava.hpp"
#include <vector>
#include <memory>

class LavaPools : public Sprite {
public:
    LavaPools(int t_x, int t_y, int t_w, int t_h);

    void render(SDL_Renderer *t_renderer) const override;

    SDL_bool isCollide(const Sprite &t_other_sprite) const override;

    void generatePools();

    void setPoolDensity(int t_pool_density);

private:
    const int m_pool_height;
    const int m_pool_width;
    const int m_vertical_gap;
    int m_pool_density;
    std::vector<std::unique_ptr<const Lava>> m_lava_pools;
};

#endif //LAVA_RUNNER_LAVAPOOLS_HPP