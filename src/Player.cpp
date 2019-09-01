//
// Created by Kevin Godell on 2019-08-22.
//

#include "Player.hpp"
#include "SDL.h"

Player::Player(int t_x, int t_y, int t_w, int t_h) : Sprite(t_x, t_y, t_w, t_h) {}

// render rect
void Player::render(SDL_Renderer *t_renderer) const {
    SDL_SetRenderDrawColor(t_renderer, 200, 200, 200, 255);
    SDL_RenderFillRect(t_renderer, &m_rect);
    SDL_SetRenderDrawColor(t_renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(t_renderer, &m_rect);
}

// reset player to starting x and y
void Player::resetRect() {
    m_rect.x = m_start_x;
    m_rect.y = m_start_y;
}

// increment x
void Player::incX(int t_x) {
    m_rect.x += t_x;
}

// increment y
void Player::incY(int t_y) {
    m_rect.y += t_y;
}

// set x
void Player::setX(int t_x) {
    m_rect.x = t_x;
}

// set y
void Player::setY(int t_y) {
    m_rect.y = t_y;
}