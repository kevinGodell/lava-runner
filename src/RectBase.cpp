//
// Created by Kevin Godell on 2019-08-23.
//

#include "RectBase.hpp"

RectBase::RectBase(int x, int y, int w, int h) : SDL_Rect({x, y, w, h}) {}

SDL_bool RectBase::isCollide(const SDL_Rect *t_other_rect) {
    return SDL_HasIntersection(this, t_other_rect);
}