//
// Created by Kevin Godell on 2019-08-26.
//

#include "LavaPools.hpp"
#include "Sprite.hpp"
#include "LavaPool.hpp"
#include "SDL.h"
#include <utility>

LavaPools::LavaPools(int t_x, int t_y, int t_w, int t_h, Uint32 t_row_count, Uint32 t_count_per_row) :
        m_green_level{255},
        m_x{t_x},
        m_y{t_y},
        m_w{t_w},
        m_h{t_h},
        m_row_count{t_row_count},
        m_count_per_row{t_count_per_row} {
    m_lava_pools.emplace_back(SDL_Rect{30, 30, 20, 20});
    m_lava_pools.emplace_back(SDL_Rect{70, 130, 20, 20});
    m_lava_pools.emplace_back(SDL_Rect{120, 230, 20, 20});
    m_lava_pools.emplace_back(SDL_Rect{30, 330, 20, 20});
    m_lava_pools.emplace_back(SDL_Rect{300, 30, 20, 20});

    m_lava_pools2.emplace_back(LavaPool{100,200,30,40});
    m_lava_pools2.emplace_back(LavaPool{150,250,50,80});


}

void LavaPools::render(SDL_Renderer *t_renderer) const {
    SDL_RenderFillRects(t_renderer, m_lava_pools.data(), m_lava_pools.size());

    for (const LavaPool& lava_pool : m_lava_pools2) {
        lava_pool.render(t_renderer);
    }
}

SDL_bool LavaPools::isCollide(const Sprite &t_other_sprite) const {
    for (const SDL_Rect& rect : m_lava_pools) {
        if (SDL_HasIntersection(&rect, &t_other_sprite.rect())) return SDL_TRUE;
    }

    for (const LavaPool& lava_pool : m_lava_pools2) {
        if (lava_pool.isCollide(t_other_sprite)) return SDL_TRUE;
    }

    return SDL_FALSE;
}