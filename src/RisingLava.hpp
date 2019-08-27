//
// Created by Kevin Godell on 2019-08-23.
//

#ifndef LAVA_RUNNER_RISINGLAVA_HPP
#define LAVA_RUNNER_RISINGLAVA_HPP


#include "Sprite.hpp"
#include "SDL.h"
#include <thread>
#include <mutex>

class RisingLava : public Sprite {
public:
    RisingLava(int t_x, int t_y, int t_w, int t_h, Uint32 t_rise_rate = 1, Uint32 t_rise_interval = 100);

    ~RisingLava();

    void render(SDL_Renderer *t_renderer) const override;

    const SDL_Rect &rect() const override;// const ref to hit area rect

    SDL_bool isCollide(const Sprite &t_other_sprite) const override;// check if sprites collide

    void startRising();

    void stopRising();

    void setRiseRate(Uint32 t_rise_rate);

    SDL_bool isRising() const;

    void setY(int t_y);

    void setH(int t_h);

private:
    mutable Uint8 m_green_level;
    SDL_bool m_is_rising;
    std::thread m_rising_thread;
    mutable std::mutex m_mutex;
    Uint32 m_rise_rate;
    Uint32 m_rise_interval;
};

#endif //LAVA_RUNNER_RISINGLAVA_HPP