//
// Created by Kevin Godell on 2019-08-26.
//

#ifndef LAVA_RUNNER_SPRITE_HPP
#define LAVA_RUNNER_SPRITE_HPP

#include "SDL.h"

class Sprite {
public:
    Sprite(int t_x, int t_y, int t_w, int t_h);// constructor with values to define hit area rect

    virtual ~Sprite();// virtual destructor

    virtual void render(SDL_Renderer *t_renderer) const = 0;// pure virtual method to render sprite

    virtual const SDL_Rect &rect() const;// const ref to hit area rect

    virtual SDL_bool isCollide(const Sprite &t_other_sprite) const;// check if sprites collide

protected:
    SDL_Rect m_rect;// hit area rect
};

#endif //LAVA_RUNNER_SPRITE_HPP