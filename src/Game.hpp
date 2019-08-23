//
// Created by Kevin Godell on 2019-08-22.
//

#ifndef LAVA_RUNNER_GAME_HPP
#define LAVA_RUNNER_GAME_HPP

#include "Player.hpp"
#include "Goal.hpp"
#include "Controls.hpp"
#include <SDL.h>

class Game {
public:
    Game(Uint32 t_width, Uint32 t_height, Uint32 t_fps);

    ~Game();

    void start();

    Uint32 score() const { return m_score; };

    Uint32 level() const { return m_level; };

private:
    const Uint32 m_width;
    const Uint32 m_height;
    const Uint32 m_fps;
    SDL_bool m_running;
    Uint32 m_score;
    Uint32 m_level;
    SDL_Window *m_window;
    SDL_Renderer *m_renderer;
    Player m_player;
    Goal m_goal;
    SDL_bool m_new_level;
    Controls m_controls;

    //void spawnGoal();

    void spawnPlayer();

    //void spawnObstacles();

    //void spawnWalls();

    void input();

    void update();

    void render();
};

#endif //LAVA_RUNNER_GAME_HPP