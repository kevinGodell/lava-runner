//
// Created by Kevin Godell on 2019-08-22.
//

#ifndef LAVA_RUNNER_GAME_HPP
#define LAVA_RUNNER_GAME_HPP

#include "Player.hpp"
#include "Goal.hpp"
#include "RisingLava.hpp"
#include "LavaPools.hpp"
#include "Controls.hpp"
#include "SDL.h"
#include <string>

class Game {
public:
    enum class State {
        INIT,
        PLAY,
        PAUSE,
        END
    };

    enum Config {
        PLAYER_SPEED_LOW = 2,
        PLAYER_SPEED_HIGH = 5,
        LAVA_POOLS_MIN_DENSITY = 3,
        LAVA_POOLS_MAX_DENSITY = 6,
        RISING_LAVA_MIN_RISE = 2,
        RISING_LAVA_MAX_RISE = 7,
    };

    Game(Uint32 t_width, Uint32 t_height, Uint32 t_fps);

    ~Game();

    void run();

    Uint32 currentScore() const { return m_current_score; }

    Uint32 highScore() const { return m_high_score; }

    State state() const { return m_state; };

private:
    const int m_width;
    const int m_height;
    const Uint32 m_frame_delay;
    const Controls m_controls;
    const Goal m_goal;
    Player m_player;
    LavaPools<LAVA_POOLS_MIN_DENSITY, LAVA_POOLS_MAX_DENSITY> m_lava_pools;
    RisingLava<RISING_LAVA_MIN_RISE, RISING_LAVA_MAX_RISE> m_rising_lava;
    State m_state;
    SDL_bool m_running;
    int m_frame_count;
    Uint32 m_time_stamp;
    Uint32 m_current_score;
    Uint32 m_high_score;
    SDL_Window *m_window;
    SDL_Renderer *m_renderer;

    void sdlInit();

    void onInit();

    void onPause();

    void onPlay();

    void onEnd();

    void render();

    void incScore();

    void setTitle(const std::string &title);

    void setState(State state);
};

#endif //LAVA_RUNNER_GAME_HPP