//
// Created by Kevin Godell on 2019-08-22.
//

#include "Player.hpp"
#include <iostream>

Player::Player(int x, int y, int w, int h) : RectBase(x, y, w, h) {}

void Player::render(SDL_Renderer *t_renderer) {
    SDL_SetRenderDrawColor(t_renderer, 255, 255, 0, 255);
    SDL_RenderFillRect(t_renderer, this);
    SDL_SetRenderDrawColor(t_renderer, 0, 0, 255, 255);
    SDL_RenderDrawRect(t_renderer, this);
}