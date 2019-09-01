//
// Created by Kevin Godell on 2019-08-26.
//

#include "Sprite.hpp"
#include "SDL.h"

Sprite::Sprite(int t_x, int t_y, int t_w, int t_h) :
        m_start_x(t_x),
        m_start_y(t_y),
        m_start_w(t_w),
        m_start_h(t_h),
        m_rect(SDL_Rect{t_x, t_y, t_w, t_h}) {}

Sprite::~Sprite() = default;

// const ref to hit area rect
const SDL_Rect &Sprite::rect() const {
    return m_rect;
}

// check if sprites collide
SDL_bool Sprite::isCollide(const Sprite &t_other_sprite) const {
    return SDL_HasIntersection(&m_rect, &t_other_sprite.rect());
}

// reset rect to starting values
void Sprite::resetRect() {
    m_rect.x = m_start_x;
    m_rect.y = m_start_y;
    m_rect.w = m_start_w;
    m_rect.h = m_start_h;
}