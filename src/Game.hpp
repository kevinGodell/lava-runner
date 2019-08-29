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
        PAUSE,
        START,
        PLAY,
        END
    };

    enum Speed {
        LOW = 2,
        HIGH = 5
    };

    Game(Uint32 t_width, Uint32 t_height, Uint32 t_fps);

    ~Game();

    void run();

    Uint32 currentScore() const { return m_current_score; }

    Uint32 highScore() const { return m_high_score; }

    State state() const { return m_state; };

private:
    const Uint32 m_width;
    const Uint32 m_height;
    const Uint32 m_fps;
    const Uint32 m_frame_delay;
    SDL_bool m_running;
    State m_state;
    Uint32 m_current_score;
    Uint32 m_high_score;
    SDL_Window *m_window;
    SDL_Renderer *m_renderer;
    Player m_player;
    const Goal m_goal;
    RisingLava m_rising_lava;
    const Controls m_controls;
    LavaPools m_lava_pools;
    std::string m_window_title;

    void onInit();

    void onPause();

    void onStart();

    void onPlay();

    void onEnd();

    void render();

    void incScore();
};

#endif //LAVA_RUNNER_GAME_HPP