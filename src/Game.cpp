//
// Created by Kevin Godell on 2019-08-22.
//

#include "Game.hpp"
#include <SDL.h>
#include <iostream>

Game::Game(const Uint32 t_width, const Uint32 t_height, const Uint32 t_fps) :
        m_width(t_width),
        m_height(t_height),
        m_fps(t_fps),
        m_running(SDL_FALSE),
        m_score(0),
        m_level(0),
        m_window(nullptr),
        m_renderer(nullptr),
        m_player(0, 0, 20, 20),
        m_goal(0, 0, m_width, 20),
        m_new_level(SDL_TRUE),
        m_controls(SDL_GetKeyboardState(nullptr)) {

    SDL_Log("Game::Game");

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        SDL_Quit();
    }

    m_window = SDL_CreateWindow("lava runner", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_width, m_height, SDL_WINDOW_SHOWN);

    if (!m_window) {
        SDL_Log("Unable to create window: %s", SDL_GetError());
        SDL_Quit();
    }

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);

    if (!m_renderer) {
        SDL_Log("Unable to create renderer: %s", SDL_GetError());
        SDL_Quit();
    }
}

Game::~Game() {
    SDL_Log("Game::~Game");
    SDL_DestroyWindow(m_window);
    SDL_DestroyRenderer(m_renderer);
    SDL_Quit();
}

void Game::start() {
    SDL_Log("Game::start");

    m_running = SDL_TRUE;

    const Uint32 frame_delay = 1000 / m_fps;

    Uint32 frame_start;

    Uint32 frame_duration;

    //spawnGoal();
    //spawnWalls();

    while (m_running) {
        frame_start = SDL_GetTicks();

        //if (round_starting) {
        //create user and put in random loc
        //create obstacles at random loc
        //}

        if (m_new_level) {
            ++m_level;
            spawnPlayer();
            //spawnObstacles();
            m_new_level = SDL_FALSE;
            render();
            SDL_Delay(1000);
        } else {
            input();
            update();
            render();
        }

        frame_duration = SDL_GetTicks() - frame_start;
        if (frame_delay > frame_duration) {
            SDL_Delay(frame_delay - frame_duration);
        }
    }
}

void Game::spawnPlayer() {
    SDL_Log("Game::spawnPlayer");

    m_player.y = m_height - m_player.h - 10;

    m_player.x = 150;// todo random x value
}

void Game::input() {
    //SDL_Log("input");

    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                m_running = SDL_FALSE;
                return;
            default:
                break;
        }
    }

    if (m_controls.escapeKey()) {
        m_running = SDL_FALSE;
        return;
    }

    int moveBy = m_controls.spaceKey() ? 5 : 2;

    if (m_controls.downKey() ^ m_controls.upKey()) {
        m_player.y += m_controls.downKey() ? moveBy : -moveBy;
    }

    if (m_controls.rightKey() ^ m_controls.leftKey()) {
        m_player.x += m_controls.rightKey() ? moveBy : -moveBy;
    }

}

void Game::update() {
    //SDL_Log("update");

    if (m_player.isCollide(&m_goal)) {
        m_new_level = SDL_TRUE;
        return;
    }

}

void Game::render() {
    //SDL_Log("render");

    SDL_RenderClear(m_renderer);

    m_player.render(m_renderer);

    m_goal.render(m_renderer);

    SDL_SetRenderDrawColor(m_renderer, 200, 200, 200, 255);

    SDL_RenderPresent(m_renderer);
}
