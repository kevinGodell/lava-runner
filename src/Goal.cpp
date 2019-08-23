//
// Created by Kevin Godell on 2019-08-23.
//

#include "Goal.hpp"
#include <iostream>

Goal::Goal(int x, int y, int w, int h) : RectBase(x, y, w, h) {
    int columns = w / 5;
    for (int row = 0; row < 4; row++) {
        int y_ = row * 5;
        int x_ = (row % 2) == 0 ? 0 : 5;
        for (int column = 0; column < columns; column++) {
            m_grid.emplace_back(SDL_Rect{x_, y_, 5, 5});
            x_ += 10;
        }
    }
}

void Goal::render(SDL_Renderer *t_renderer) {
    SDL_SetRenderDrawColor(t_renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(t_renderer, this);
    SDL_SetRenderDrawColor(t_renderer, 0, 0, 0, 255);
    SDL_RenderFillRects(t_renderer, m_grid.data(), m_grid.size());
    SDL_RenderDrawRect(t_renderer, this);
}