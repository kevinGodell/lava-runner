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

    //SDL_Set
    std::cout << "constructed game" << std::endl;
}

Game::~Game() {
    SDL_DestroyWindow(m_window);
    SDL_DestroyRenderer(m_renderer);
    SDL_Quit();
    std::cout << "destructed game" << std::endl;
}

void Game::start() {
    std::cout << "start" << std::endl;

    const Uint32 frame_delay = 1000 / m_fps;

    Uint32 frame_start;
    Uint32 frame_duration;

    m_running = SDL_TRUE;

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
    m_player.y = m_height - m_player.h - 10;
    m_player.x = 150;// todo random x value
}

void Game::input() {
    //std::cout << "input" << std::endl;
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                std::cout << "quit1" << std::endl;
                m_running = SDL_FALSE;
                std::cout << "quit2" << std::endl;
                return;
                //break;
            default:
                break;
        }
    }

    //std::cout << "after" << std::endl;

    if (m_controls.escapeKey()) {
        m_running = SDL_FALSE;
        return;
    }

    if (m_controls.upKey()) {
        m_player.y -= 1;
    }

    if (m_controls.downKey()) {
        m_player.y += 10;
    }

    if (m_controls.rightKey()) {
        m_player.x += 10;
    }

    if (m_controls.leftKey()) {
        m_player.x -= 10;
    }
}

void Game::update() {
    //std::cout << "update" << std::endl;
    //std::cout << m_player.y << " " << m_goal.y + m_goal.h << std::endl;
    if (SDL_HasIntersection(&m_player, &m_goal)) {
        //std::cout << m_player.y << " " << m_goal.y + m_goal.h << std::endl;
        m_new_level = SDL_TRUE;
    }

    //if (m_player.y < 20) {
    //  m_new_level = SDL_TRUE;
    //}
}

void Game::render() {
    //std::cout << "render" << std::endl;
    SDL_RenderClear(m_renderer);

    m_player.render(m_renderer);

    m_goal.render(m_renderer);

    SDL_SetRenderDrawColor(m_renderer, 200, 200, 200, 255);

    SDL_RenderPresent(m_renderer);
}
