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


private:
    const Uint32 m_rise_interval;
    Uint32 m_rise_value;
    SDL_bool m_is_rising;
    std::thread m_rising_thread;
    mutable std::mutex m_mutex;
};


#endif //LAVA_RUNNER_RISINGLAVA_HPP
