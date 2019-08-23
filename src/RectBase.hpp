//
// Created by Kevin Godell on 2019-08-23.
//

#ifndef LAVA_RUNNER_RECTBASE_HPP
#define LAVA_RUNNER_RECTBASE_HPP

#include <SDL.h>

class RectBase : public SDL_Rect {
public:
    RectBase(int x, int y, int w, int h);

    virtual void render(SDL_Renderer *t_renderer) = 0;

    SDL_bool isCollide(const SDL_Rect *t_other_rect);
};

#endif //LAVA_RUNNER_RECTBASE_HPP