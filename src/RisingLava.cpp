//
// Created by Kevin Godell on 2019-08-28.
//

#include "RisingLava.hpp"

RisingLava::RisingLava(int t_x, int t_y, int t_w, int t_h, Uint32 t_rise_rate, Uint32 t_rise_interval) :
        Lava(t_x, t_y, t_w, t_h),
        m_rise_start_y(t_y),
        m_rise_start_h(t_h),
        m_rise_rate(t_rise_rate),
        m_rise_interval(t_rise_interval),
        m_is_rising(SDL_FALSE) {}

RisingLava::~RisingLava() {
    stopRising();
}

const SDL_Rect &RisingLava::rect() const {
    std::lock_guard<std::mutex> lock_guard(m_mutex);
    return m_rect;
}

SDL_bool RisingLava::isCollide(const Sprite &t_other_sprite) const {
    std::lock_guard<std::mutex> lock_guard(m_mutex);
    return SDL_HasIntersection(&m_rect, &t_other_sprite.rect());
}

void RisingLava::startRising() {
    if (m_is_rising) return;
    m_is_rising = SDL_TRUE;
    m_rising_thread = std::thread([this]() {
        while (m_is_rising) {
            SDL_Delay(m_rise_interval);
            std::lock_guard<std::mutex> lock_guard(m_mutex);
            m_rect.y -= m_rise_rate;
            m_rect.h += m_rise_rate;
        }
    });
    m_rising_thread.detach();
}

void RisingLava::stopRising() {
    if (!m_is_rising) return;
    m_is_rising = SDL_FALSE;
}

void RisingLava::setRiseRate(const Uint32 t_rise_rate) {
    std::lock_guard<std::mutex> lock_guard(m_mutex);
    if (t_rise_rate > 5) {
        m_rise_rate = 5;
    } else if (t_rise_rate < 1) {
        m_rise_rate = 1;
    } else {
        m_rise_rate = t_rise_rate;
    }
}

SDL_bool RisingLava::isRising() const {
    std::lock_guard<std::mutex> lock_guard(m_mutex);
    return m_is_rising;
}

void RisingLava::resetRising() {
    stopRising();
    m_rect.y = m_rise_start_y;
    m_rect.h = m_rise_start_h;
}