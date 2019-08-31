//
// Created by Kevin Godell on 2019-08-26.
//

#include "Sprite.hpp"
#include "SDL.h"

Sprite::Sprite(int t_x, int t_y, int t_w, int t_h) : m_rect(SDL_Rect{t_x, t_y, t_w, t_h}) {}

Sprite::~Sprite() = default;

const SDL_Rect &Sprite::rect() const {
    return m_rect;
}

SDL_bool Sprite::isCollide(const Sprite &t_other_sprite) const {
    return SDL_HasIntersection(&m_rect, &t_other_sprite.rect());
}