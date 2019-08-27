//
// Created by Kevin Godell on 2019-08-26.
//

#include "LavaPool.hpp"

LavaPool::LavaPool(int t_x, int t_y, int t_w, int t_h) : Sprite(t_x, t_y, t_w, t_h) {}

void LavaPool::render(SDL_Renderer *t_renderer) const {
    SDL_SetRenderDrawColor(t_renderer, 255, 255, 0, 255);
    SDL_RenderFillRect(t_renderer, &rect());
    SDL_SetRenderDrawColor(t_renderer, 0, 0, 255, 255);
    SDL_RenderDrawRect(t_renderer, &rect());
}