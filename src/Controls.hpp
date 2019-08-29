//
// Created by Kevin Godell on 2019-08-22.
//

#ifndef LAVA_RUNNER_CONTROLS_HPP
#define LAVA_RUNNER_CONTROLS_HPP

#include "SDL.h"

class Controls final {
public:

    explicit Controls(const Uint8 *t_keyboard_state);

    SDL_bool upKey() const;

    SDL_bool rightKey() const;

    SDL_bool downKey() const;

    SDL_bool leftKey() const;

    SDL_bool spaceKey() const;

    SDL_bool escapeKey() const;

    SDL_bool returnKey() const;

private:
    const Uint8 *m_keyboard_state;
};

#endif //LAVA_RUNNER_CONTROLS_HPP