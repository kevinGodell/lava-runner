//
// Created by Kevin Godell on 2019-08-28.
//

#ifndef LAVA_RUNNER_RISINGLAVA_HPP
#define LAVA_RUNNER_RISINGLAVA_HPP

#include "Lava.hpp"
#include "SDL.h"
#include <thread>
#include <mutex>

class RisingLava : public Lava {
public:
    RisingLava(int t_x, int t_y, int t_w, int t_h, Uint32 t_rise_rate = 1, Uint32 t_rise_interval = 100);

    ~RisingLava();

    const SDL_Rect &rect() const override;

    SDL_bool isCollide(const Sprite &t_other_sprite) const override;

    void startRising();

    void stopRising();

    void resetRising();

    void setRiseRate(Uint32 t_rise_rate);

    SDL_bool isRising() const;


private:
    Uint32 m_rise_rate;
    Uint32 m_rise_interval;
    SDL_bool m_is_rising;
    std::thread m_rising_thread;
    mutable std::mutex m_mutex;
    const Uint32 m_rise_start_y;
    const Uint32 m_rise_start_h;
};


#endif //LAVA_RUNNER_RISINGLAVA_HPP
