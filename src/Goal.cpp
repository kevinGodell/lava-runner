//
// Created by Kevin Godell on 2019-08-23.
//

#include "Goal.hpp"
#include <iostream>

Goal::Goal(int x, int y, int w, int h) : RectBase(x, y, w, h) {
    const int square_size = 5;
    if (w % square_size != 0 || h % square_size !=0) {
        SDL_Log("Goal::Goal: width(%d) & height(%d) must be divisible by %d", w, h, square_size);
    }
    const int num_rows = h / square_size;
    const int num_columns = w / square_size;
    for (int row = 0; row < num_rows; ++row) {
        int pos_y = row * square_size + y;
        int pos_x = row % 2 == 0 ? x : x + square_size;
        bool skip_column = row % 2 != 0;
        for (int column = 0; column < num_columns; ++column) {
            if (skip_column) {
                skip_column = false;
                continue;
            }
            m_grid.emplace_back(SDL_Rect{pos_x, pos_y, square_size, square_size});
            pos_x += square_size * 2;
            skip_column = true;
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