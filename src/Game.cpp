//
// Created by Kevin Godell on 2019-08-22.
//

#include "Game.hpp"
#include "SDL.h"

Game::Game(const Uint32 t_width, const Uint32 t_height, const Uint32 t_fps) :
        m_width(t_width),
        m_height(t_height),
        m_frame_delay{1000 / t_fps},
        m_running(SDL_FALSE),
        m_state(State::INIT),
        m_current_score(0),
        m_high_score(0),
        m_window(nullptr),
        m_renderer(nullptr),
        m_player(0, 0, 20, 20),
        m_goal(0, 0, m_width, 20),
        m_rising_lava(0, m_height - 2, m_width, 2, 1, 100),
        m_controls(SDL_GetKeyboardState(nullptr)),
        m_lava_pools(0, 70, m_width, m_height - 170),
        m_frame_count(0),
        m_time_stamp(0) {

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        SDL_Quit();
        exit(1);
    }

    m_window = SDL_CreateWindow("lava runner", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_width, m_height, SDL_WINDOW_SHOWN);

    if (!m_window) {
        SDL_Log("Unable to create window: %s", SDL_GetError());
        SDL_Quit();
        exit(1);
    }

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);

    if (!m_renderer) {
        SDL_Log("Unable to create renderer: %s", SDL_GetError());
        m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_SOFTWARE);
        if (!m_renderer) {
            SDL_Log("Unable to create renderer: %s", SDL_GetError());
            SDL_Quit();
            exit(1);
        }
    }

    SDL_RenderClear(m_renderer);
}

Game::~Game() {
    SDL_DestroyWindow(m_window);
    SDL_DestroyRenderer(m_renderer);
    SDL_Quit();
}

void Game::run() {

    if (m_running) return;

    m_running = SDL_TRUE;

    while (m_running) {
        switch (m_state) {
            case State::INIT:
                onInit();
                break;
            case State::PLAY:
                onPlay();
                break;
            case State::PAUSE:
                onPause();
                break;
            case State::END:
                onEnd();
                break;
        }
    }
}

void Game::render() {
    SDL_SetRenderDrawColor(m_renderer, 154, 132, 28, 255);
    SDL_RenderClear(m_renderer);
    m_goal.render(m_renderer);
    m_lava_pools.render(m_renderer);
    m_player.render(m_renderer);
    m_rising_lava.render(m_renderer);
    SDL_RenderPresent(m_renderer);
}

// initialize new level
void Game::onInit() {

    m_player.setY(m_height - m_player.rect().h - 40);
    m_player.setX((m_width - m_player.rect().w) / 2);

    m_rising_lava.resetRising();
    m_rising_lava.setRiseRate(m_current_score + 1);

    m_lava_pools.setPoolDensity(m_current_score + 1);
    m_lava_pools.generatePools();

    render();

    setState(State::PLAY);
}

// wait for user input to un-pause
void Game::onPause() {

    m_rising_lava.stopRising();

    SDL_Event event;

    while (SDL_WaitEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                m_running = SDL_FALSE;
                return;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        setState(State::END);
                        return;
                    case SDLK_UP:
                    case SDLK_RIGHT:
                    case SDLK_DOWN:
                    case SDLK_LEFT:
                    case SDLK_SPACE:
                        setState(State::PLAY);
                        return;
                }
        }
    }
}

void Game::onPlay() {
    Uint32 frame_start = SDL_GetTicks();

    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                m_running = SDL_FALSE;
                return;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        setState(State::END);
                        return;
                    case SDLK_RETURN:
                        setState(State::PAUSE);
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

    if (m_player.rect().y + m_player.rect().h > m_height) {
        m_player.setY(m_height - m_player.rect().h);
    }

    if (!m_rising_lava.isRising() && m_player.isCollide(m_lava_pools)) {
        m_rising_lava.startRising();
    } else if (m_rising_lava.isRising() && !m_player.isCollide(m_lava_pools)) {
        m_rising_lava.stopRising();
    }

    if (m_player.isCollide(m_goal)) {
        incScore();
        render();
        setState(State::INIT);
        return;
    }

    if (m_rising_lava.isCollide(m_player) || m_lava_pools.isCollide(m_player)) {
        render();
        setState(State::END);
        return;
    }

    render();

    Uint32 frame_end = SDL_GetTicks();

    ++m_frame_count;

    Uint32 frame_duration = frame_end - frame_start;

    if (frame_end - m_time_stamp >= 1000) {
        SDL_Log("FPS: %d", m_frame_count);
        m_frame_count = 0;
        m_time_stamp = frame_end;
    }

    if (frame_duration < m_frame_delay) {
        SDL_Delay(m_frame_delay - frame_duration);
    }

}

void Game::onEnd() {
    render();
    m_rising_lava.stopRising();
    m_current_score = 0;
    setState(State::INIT);
}

void Game::incScore() {
    ++m_current_score;
    if (m_current_score > m_high_score) {
        m_high_score = m_current_score;
    }
}

void Game::setTitle(const std::string &title) {
    SDL_SetWindowTitle(m_window, title.c_str());
}

void Game::setState(const Game::State state) {
    std::string status;
    switch(state) {
        case State::INIT:
            status = "initializing";
            setTitle("Status: initializing, Score: " + std::to_string(m_current_score) + ", High Score: " + std::to_string(m_high_score));
            SDL_Delay(500);
            break;
        case State::PLAY:
            setTitle("Status: playing, Score: " + std::to_string(m_current_score) + ", High Score: " + std::to_string(m_high_score));
            SDL_Delay(100);
            break;
        case State::PAUSE:
            setTitle("Status: paused, Score: " + std::to_string(m_current_score) + ", High Score: " + std::to_string(m_high_score));
            break;
        case State::END:
            setTitle("Status: game over, Score: " + std::to_string(m_current_score) + ", High Score: " + std::to_string(m_high_score));
            SDL_Delay(1000);
            break;
    }
    m_state = state;
}
