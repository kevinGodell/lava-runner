//
// Created by Kevin Godell on 2019-08-26.
//

#ifndef LAVA_RUNNER_LAVAPOOLS_HPP
#define LAVA_RUNNER_LAVAPOOLS_HPP

#include "Sprite.hpp"
#include "Lava.hpp"
#include "SDL.h"
#include <random>
#include <array>
#include <vector>
#include <memory>

template<Uint32 min, Uint32 max>
class LavaPools final : public Sprite {
public:
    LavaPools(int t_x, int t_y, int t_w, int t_h);

    void render(SDL_Renderer *t_renderer) const override;

    SDL_bool isCollide(const Sprite &t_other_sprite) const override;// check if sprites collide

    void setPoolDensity(Uint32 t_pool_density);// change density of random lava pools

    void generatePools();// create lava and add to m_lava_pools

private:
    const int m_pool_height;
    const int m_pool_width;
    const int m_vertical_gap;
    Uint32 m_pool_density;
    std::vector<std::unique_ptr<const Lava>> m_lava_pools;
};

template<Uint32 min, Uint32 max>
LavaPools<min, max>::LavaPools(int t_x, int t_y, int t_w, int t_h) :
        Sprite(t_x, t_y, t_w, t_h),
        m_pool_height(10),
        m_pool_width(50),
        m_vertical_gap(50),
        m_pool_density(min) { static_assert(min >= 1 && max <= 9 && min < max, "min must be >= 1 and max must be <= 9"); }

template<Uint32 min, Uint32 max>
void LavaPools<min, max>::render(SDL_Renderer *t_renderer) const {
    SDL_SetRenderDrawColor(t_renderer, 142, 113, 12, 255);
    SDL_RenderFillRect(t_renderer, &m_rect);
    for (const std::unique_ptr<const Lava> &lava_pool : m_lava_pools) {
        lava_pool->render(t_renderer);
    }
}

template<Uint32 min, Uint32 max>
SDL_bool LavaPools<min, max>::isCollide(const Sprite &t_other_sprite) const {
    for (const std::unique_ptr<const Lava> &lava_pool : m_lava_pools) {
        if (lava_pool->isCollide(t_other_sprite)) return SDL_TRUE;
    }
    return SDL_FALSE;
}

template<Uint32 min, Uint32 max>
void LavaPools<min, max>::setPoolDensity(const Uint32 t_pool_density) {
    if (t_pool_density > max) {
        m_pool_density = max;
        return;
    }
    if (t_pool_density < min) {
        m_pool_density = min;
        return;
    }
    m_pool_density = t_pool_density;
}

template<Uint32 min, Uint32 max>
void LavaPools<min, max>::generatePools() {
    m_lava_pools.clear();
    int rows = (m_rect.h + m_vertical_gap) / (m_pool_height + m_vertical_gap);
    int cols = m_rect.w / m_pool_width;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::array<Uint32, 2> init{10 - m_pool_density, m_pool_density};
    std::discrete_distribution<Uint32> dd(init.begin(), init.end());
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

#endif //LAVA_RUNNER_LAVAPOOLS_HPP