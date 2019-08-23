//
// Created by Kevin Godell on 2019-08-22.
//

#include "Controls.hpp"
#include <SDL.h>

Controls::Controls(const Uint8 *t_keyboard_state) : m_keyboard_state(t_keyboard_state) {}

SDL_bool Controls::upKey() const {
    return static_cast<SDL_bool>(m_keyboard_state[SDL_SCANCODE_UP]);
}

SDL_bool Controls::rightKey() const {
    return static_cast<SDL_bool>(m_keyboard_state[SDL_SCANCODE_RIGHT]);
}

SDL_bool Controls::downKey() const {
    return static_cast<SDL_bool>(m_keyboard_state[SDL_SCANCODE_DOWN]);
}

SDL_bool Controls::leftKey() const {
    return static_cast<SDL_bool>(m_keyboard_state[SDL_SCANCODE_LEFT]);
}

SDL_bool Controls::spaceKey() const {
    return static_cast<SDL_bool>(m_keyboard_state[SDL_SCANCODE_SPACE]);
}

SDL_bool Controls::escapeKey() const {
    return static_cast<SDL_bool>(m_keyboard_state[SDL_SCANCODE_ESCAPE]);
}

SDL_bool Controls::returnKey() const {
    return static_cast<SDL_bool>(m_keyboard_state[SDL_SCANCODE_RETURN]);
}