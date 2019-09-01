//
// Created by Kevin Godell on 2019-08-26.
//

#include "LavaPools.hpp"
#include "Sprite.hpp"
#include "Lava.hpp"
#include "SDL.h"
#include <random>
#include <array>
#include <vector>
#include <memory>

LavaPools::LavaPools(int t_x, int t_y, int t_w, int t_h) :
        Sprite(t_x, t_y, t_w, t_h),
        m_pool_height(10),
        m_pool_width(50),
        m_vertical_gap(50),
        m_pool_density(1) {}

void LavaPools::render(SDL_Renderer *t_renderer) const {
    SDL_SetRenderDrawColor(t_renderer, 142, 113, 12, 255);
    SDL_RenderFillRect(t_renderer, &m_rect);
    for (const std::unique_ptr<const Lava> &lava_pool : m_lava_pools) {
        lava_pool->render(t_renderer);
    }
}

SDL_bool LavaPools::isCollide(const Sprite &t_other_sprite) const {
    for (const std::unique_ptr<const Lava> &lava_pool : m_lava_pools) {
        if (lava_pool->isCollide(t_other_sprite)) return SDL_TRUE;
    }
    return SDL_FALSE;
}

void LavaPools::setPoolDensity(const int t_pool_density) {
    if (t_pool_density > 7) {
        m_pool_density = 7;
        return;
    }
    if (t_pool_density < 1) {
        m_pool_density = 1;
        return;
    }
    m_pool_density = t_pool_density;
}

void LavaPools::generatePools() {
    m_lava_pools.clear();
    int rows = (m_rect.h + m_vertical_gap) / (m_pool_height + m_vertical_gap);
    int cols = m_rect.w / m_pool_width;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::array<int, 2> init{10 - m_pool_density, m_pool_density};
    std::discrete_distribution<int> dd(init.begin(), init.end());
    for (int row = 0, y = m_rect.y; row < rows; ++row, y += (m_pool_height + m_vertical_gap)) {
        bool row_has_space = false;//make sure that entire row is not filled with lava blocking safe passage
        for (int col = 0, x = m_rect.x; col < cols; ++col, x += m_pool_width) {
            if (dd(gen)) {
                m_lava_pools.emplace_back(std::make_unique<const Lava>(x, y, m_pool_width, m_pool_height));
            } else {
                row_has_space = true;
            }
        }
        if (!row_has_space) {
            m_lava_pools.pop_back();
        }
    }
}