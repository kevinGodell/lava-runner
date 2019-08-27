//
// Created by Kevin Godell on 2019-08-22.
//

#include "Game.hpp"
#include "SDL.h"
#include <iostream>

Game::Game(const Uint32 t_width, const Uint32 t_height, const Uint32 t_fps) :
        m_width(t_width),
        m_height(t_height),
        m_fps(t_fps),
        m_running(SDL_FALSE),
        m_state(State::INIT),
        m_score(0),
        m_level(1),
        m_window(nullptr),
        m_renderer(nullptr),
        m_player(0, 0, 30, 30),
        m_goal(0, 0, m_width, 20),
        m_lava(0, m_height, m_width, 0, 1, 100),
        m_controls(SDL_GetKeyboardState(nullptr)),
        m_lava_pools{100, 100, 50, 50, 5, 5} {

    SDL_Log("Game::Game");

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
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

    SDL_RenderClear(m_renderer);
}

Game::~Game() {
    SDL_Log("Game::~Game");
    SDL_DestroyWindow(m_window);
    SDL_DestroyRenderer(m_renderer);
    SDL_Quit();
}

void Game::run() {

    SDL_Log("Game::run");

    if (m_running) return;

    m_running = SDL_TRUE;

    const Uint32 frame_delay = 1000 / m_fps;

    Uint32 frame_start;

    Uint32 frame_duration;

    while (m_running) {
        frame_start = SDL_GetTicks();

        switch (m_state) {
            case State::INIT:
                onInit();
                break;
            case State::PAUSE:
                onPause();
                break;
            case State::START:
                onStart();
                break;
            case State::PLAY:
                onPlay();
                break;
            case State::END:
                onEnd();
                break;
        }

        frame_duration = SDL_GetTicks() - frame_start;
        if (frame_delay > frame_duration) {
            SDL_Delay(frame_delay - frame_duration);
        }
    }
}

void Game::render() {
    SDL_Log("render start");
    SDL_SetRenderDrawColor(m_renderer, 181, 101, 29, 255);
    SDL_RenderClear(m_renderer);
    m_player.render(m_renderer);
    m_goal.render(m_renderer);
    m_lava.render(m_renderer);
    m_lava_pools.render(m_renderer);
    SDL_RenderPresent(m_renderer);
    SDL_Log("render end");
}

// initialize new level
void Game::onInit() {

    m_player.setY(m_height - m_player.rect().h - 50);
    m_player.setX((m_width - m_player.rect().w) / 2);

    m_lava.setY(m_height);
    m_lava.setH(0);

    render();
    m_state = State::PAUSE;
}

// wait for user input to play
void Game::onPause() {

    SDL_SetWindowTitle(m_window, "pause");

    m_lava.stopRising();

    SDL_Event event;
    while (SDL_WaitEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                m_running = SDL_FALSE;
                return;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        m_state = State::END;
                        return;
                    case SDLK_RETURN:
                        m_state = State::START;
                        return;
                }
        }
    }
}

void Game::onStart() {
    SDL_SetWindowTitle(m_window, "start");
    std::cout << "start" << std::endl;
    m_lava.startRising();
    m_state = State::PLAY;
}

void Game::onPlay() {
    SDL_SetWindowTitle(m_window, "play");
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                m_running = SDL_FALSE;
                return;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        m_state = State::END;
                        return;
                    case SDLK_RETURN:
                        m_state = State::PAUSE;
                        return;
                }
        }
    }

    int moveBy = m_controls.spaceKey() ? Speed::HIGH : Speed::LOW;

    if (m_controls.downKey() ^ m_controls.upKey()) {
        m_player.incY(m_controls.downKey() ? moveBy : -moveBy);
    }

    if (m_controls.rightKey() ^ m_controls.leftKey()) {
        m_player.incX(m_controls.rightKey() ? moveBy : -moveBy);
    }

    if (m_player.rect().x < 0) {
        m_player.setX(0);
    } else if (m_player.rect().x + m_player.rect().w > m_width) {
        m_player.setX(m_width - m_player.rect().w);
    }

    if (m_player.isCollide(m_goal)) {
        ++m_level;
        m_lava.setRiseRate(m_level);
        render();
        SDL_Delay(1000);
        m_state = State::INIT;
        return;
    }

    if (m_lava.isCollide(m_player) || m_lava_pools.isCollide(m_player)) {

        render();
        m_state = State::END;
        return;
    }

    render();

}

void Game::onEnd() {
    // todo show end
    // pause a little
    // change state
    //update title, high score, last score, current score, status
    SDL_SetWindowTitle(m_window, "end");

    SDL_Delay(1000);

    m_lava.stopRising();
    m_lava.setRiseRate(1);
    SDL_Delay(1000);
    m_level = 1;
    m_state = State::INIT;


}
