//
// Created by Kevin Godell on 2019-08-26.
//

#include "LavaPools.hpp"
#include "Sprite.hpp"
#include "SDL.h"
#include <utility>
#include <string>
#include <iostream>
#include <random>
#include <map>


LavaPools::LavaPools(int t_x, int t_y, int t_w, int t_h, double t_pool_density) :
        m_x(t_x),
        m_y(t_y),
        m_w(t_w),
        m_h(t_h),
        m_pool_density(t_pool_density) {}

void LavaPools::render(SDL_Renderer *t_renderer) const {
    for (const Lava &lava_pool : m_lava_pools) {
        lava_pool.render(t_renderer);
    }
}

SDL_bool LavaPools::isCollide(const Sprite &t_other_sprite) const {
    for (const Lava &lava_pool : m_lava_pools) {
        if (lava_pool.isCollide(t_other_sprite)) return SDL_TRUE;
    }
    return SDL_FALSE;
}

void LavaPools::setPoolDensity(double t_pool_density) {
    if (t_pool_density < 1) {
        m_pool_density = 1;
    } else if (t_pool_density > 6) {
        m_pool_density = 6;
    } else {
        m_pool_density = t_pool_density;
    }
}

void LavaPools::generatePools() {
    m_lava_pools.clear();
    Uint32 pool_height = 10;
    Uint32 pool_width = 50;
    Uint32 row_gap = 50;
    Uint32 rows = m_h / (pool_height + row_gap);
    Uint32 cols = m_w / pool_width;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::discrete_distribution<int> dd({10 - m_pool_density, m_pool_density});
    for (int row = 0, y = m_y; row < rows; ++row, y += pool_height + row_gap) {
        for (int col = 0, x = m_x; col < cols; ++col, x += pool_width) {
            if (dd(gen)) {
                m_lava_pools.emplace_back(Lava(x, y, pool_width, pool_height));
            }
        }
    }
}