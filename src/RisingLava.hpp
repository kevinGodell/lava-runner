//
// Created by Kevin Godell on 2019-08-28.
//

#ifndef LAVA_RUNNER_RISINGLAVA_HPP
#define LAVA_RUNNER_RISINGLAVA_HPP

#include "Sprite.hpp"
#include "Lava.hpp"
#include "SDL.h"
#include <thread>
#include <mutex>

template<Uint32 min, Uint32 max>
class RisingLava final : public Lava {
public:
    RisingLava(int t_x, int t_y, int t_w, int t_h);

    ~RisingLava() override;

    const SDL_Rect &rect() const override;// thread-safe

    SDL_bool isCollide(const Sprite &t_other_sprite) const override;// thread-safe, check if sprites collide

    void resetRect() override;// thread-safe, reset rising lava to starting y and h

    void startRising();// start lava rising

    void stopRising();// stop lava at current position

    void setRiseValue(Uint32 t_rise_value);// thread-safe, change value of lava rising

    SDL_bool isRising() const;// thread-safe, check if lava is rising

    void doSum(uint32_t sinf);


private:
    const Uint32 m_rise_interval;
    Uint32 m_rise_value;
    SDL_bool m_is_rising;
    std::thread m_rising_thread;
    mutable std::mutex m_mutex;
};

template<Uint32 min, Uint32 max>
RisingLava<min, max>::RisingLava(int t_x, int t_y, int t_w, int t_h) :
        Lava(t_x, t_y, t_w, t_h),
        m_rise_interval(100),
        m_rise_value(min),
        m_is_rising(SDL_FALSE) { static_assert(min >= 1 && max <= 9 && min < max, "min must be >= 1 and max must be <= 9"); }

template<Uint32 min, Uint32 max>
RisingLava<min, max>::~RisingLava() {
    stopRising();
}

template<Uint32 min, Uint32 max>
const SDL_Rect &RisingLava<min, max>::rect() const {
    std::lock_guard<std::mutex> lock_guard(m_mutex);
    return m_rect;
}

// check if sprites collide
template<Uint32 min, Uint32 max>
SDL_bool RisingLava<min, max>::isCollide(const Sprite &t_other_sprite) const {
    std::lock_guard<std::mutex> lock_guard(m_mutex);
    return SDL_HasIntersection(&m_rect, &t_other_sprite.rect());
}

// reset rising lava to start y and h
template<Uint32 min, Uint32 max>
void RisingLava<min, max>::resetRect() {
    std::lock_guard<std::mutex> lock_guard(m_mutex);
    m_rect.y = m_start_y;
    m_rect.h = m_start_h;
}

// start thread that grows lava upward on interval
template<Uint32 min, Uint32 max>
void RisingLava<min, max>::startRising() {
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
template<Uint32 min, Uint32 max>
void RisingLava<min, max>::stopRising() {
    if (!m_is_rising) return;
    m_is_rising = SDL_FALSE;
}

// value that will alter m_rect.y and m_rect.h
template<Uint32 min, Uint32 max>
void RisingLava<min, max>::setRiseValue(Uint32 t_rise_value) {
    std::lock_guard<std::mutex> lock_guard(m_mutex);
    if (t_rise_value > max) {
        m_rise_value = max;
        return;
    }
    if (t_rise_value < min) {
        m_rise_value = min;
        return;
    }
    m_rise_value = t_rise_value;
}

// check if lava is rising
template<Uint32 min, Uint32 max>
SDL_bool RisingLava<min, max>::isRising() const {
    std::lock_guard<std::mutex> lock_guard(m_mutex);
    return m_is_rising;
}


#endif //LAVA_RUNNER_RISINGLAVA_HPP
