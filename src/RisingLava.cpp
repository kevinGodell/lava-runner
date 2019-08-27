//
// Created by Kevin Godell on 2019-08-23.
//

#include "RisingLava.hpp"
#include "SDL.h"
#include <chrono>
#include <thread>
#include <mutex>

RisingLava::RisingLava(int t_x, int t_y, int t_w, int t_h, Uint32 t_rise_rate, Uint32 t_rise_interval) :
        Sprite{t_x, t_y, t_w, t_h},
        m_green_level{255},
        m_is_rising{SDL_FALSE},
        m_rise_rate{t_rise_rate},
        m_rise_interval{t_rise_interval} {}

RisingLava::~RisingLava() {
    stopRising();
}

SDL_bool RisingLava::isRising() const {
    std::lock_guard<std::mutex> lock_guard(m_mutex);
    return m_is_rising;
}

void RisingLava::render(SDL_Renderer *t_renderer) const {
    SDL_SetRenderDrawColor(t_renderer, 255, m_green_level, 0, 255);
    SDL_RenderFillRect(t_renderer, &rect());
    m_green_level ^= 255u;
}

const SDL_Rect& RisingLava::rect() const {
    std::lock_guard<std::mutex> lock_guard(m_mutex);
    return Sprite::rect();
}

SDL_bool RisingLava::isCollide(const Sprite &t_other_sprite) const {
    return SDL_HasIntersection(&rect(), &t_other_sprite.rect());
}

void RisingLava::startRising() {
    std::lock_guard<std::mutex> lock_guard(m_mutex);
    if (m_is_rising) return;
    m_is_rising = SDL_TRUE;
    m_rising_thread = std::thread([this]() {
        while (m_is_rising) {
            std::this_thread::sleep_for(std::chrono::milliseconds(m_rise_interval));
            std::lock_guard<std::mutex> lock_guard(m_mutex);
            m_rect.y -= m_rise_rate;
            m_rect.h += m_rise_rate;
        }
    });
}

void RisingLava::stopRising() {
    std::unique_lock<std::mutex> unique_lock(m_mutex);
    if (!m_is_rising) return;
    m_is_rising = SDL_FALSE;
    unique_lock.unlock();
    m_rising_thread.join();
}

void RisingLava::setRiseRate(Uint32 t_rise_rate) {
    std::lock_guard<std::mutex> lock_guard(m_mutex);
    if (t_rise_rate < 1) {
        m_rise_rate = 1;
    } else if (t_rise_rate > 10) {
        m_rise_rate = 10;
    } else {
        m_rise_rate = t_rise_rate;
    }
}

void RisingLava::setY(int t_y) {
    std::lock_guard<std::mutex> lock_guard(m_mutex);
    m_rect.y = t_y;
}

void RisingLava::setH(int t_h) {
    std::lock_guard<std::mutex> lock_guard(m_mutex);
    m_rect.h = t_h;
}