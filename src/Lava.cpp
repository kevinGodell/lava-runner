//
// Created by Kevin Godell on 2019-08-28.
//

#include "Lava.hpp"
#include "SDL.h"

Lava::Lava(int t_x, int t_y, int t_w, int t_h) : Sprite(t_x, t_y, t_w, t_h), m_green(0) {}

void Lava::render(SDL_Renderer *t_renderer) const {
    SDL_SetRenderDrawColor(t_renderer, 255, m_green, 0, 255);
    SDL_RenderFillRect(t_renderer, &m_rect);
    m_green ^= 255u;
}