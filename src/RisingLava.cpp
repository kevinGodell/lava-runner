//
// Created by Kevin Godell on 2019-08-28.
//

#include "RisingLava.hpp"
#include "Sprite.hpp"
#include "Lava.hpp"
#include "SDL.h"
#include <thread>
#include <mutex>

RisingLava::RisingLava(int t_x, int t_y, int t_w, int t_h) :
        Lava(t_x, t_y, t_w, t_h),
        m_rise_interval(100),
        m_rise_value(1),
        m_is_rising(SDL_FALSE) {}

RisingLava::~RisingLava() {
    stopRising();
}

const SDL_Rect &RisingLava::rect() const {
    std::lock_guard<std::mutex> lock_guard(m_mutex);
    return m_rect;
}

// check if sprites collide
SDL_bool RisingLava::isCollide(const Sprite &t_other_sprite) const {
    std::lock_guard<std::mutex> lock_guard(m_mutex);
    return SDL_HasIntersection(&m_rect, &t_other_sprite.rect());
}

// reset rising lava to start y and h
void RisingLava::resetRect() {
    std::lock_guard<std::mutex> lock_guard(m_mutex);
    m_rect.y = m_start_y;
    m_rect.h = m_start_h;
}

// start thread that grows lava upward on interval
void RisingLava::startRising() {
    if (m_is_rising) return;
    m_is_rising = SDL_TRUE;
    m_rising_thread = std::thread([this]() {
        while (m_is_rising) {
            SDL_Delay(m_rise_interval);
            std::lock_guard<std::mutex> lock_guard(m_mutex);
            m_rect.y -= m_rise_value;
            m_rect.h += m_rise_value;
        }
    });
    m_rising_thread.detach();// detached thread will be destroyed when !m_is_rising
}

// cause detached thread to be destroyed and stop lava rising
void RisingLava::stopRising() {
    if (!m_is_rising) return;
    m_is_rising = SDL_FALSE;
}

// value that will alter m_rect.y and m_rect.h
void RisingLava::setRiseValue(Uint32 t_rise_value) {
    std::lock_guard<std::mutex> lock_guard(m_mutex);
    if (t_rise_value > 5) {
        m_rise_value = 5;
    } else if (t_rise_value < 1) {
        m_rise_value = 1;
    } else {
        m_rise_value = t_rise_value;
    }
}

// check if lava is rising
SDL_bool RisingLava::isRising() const {
    std::lock_guard<std::mutex> lock_guard(m_mutex);
    return m_is_rising;
}