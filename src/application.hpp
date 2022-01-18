#pragma once

#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>

#include "ball.hpp"
#include "paddle.hpp"
#include "window.hpp"
#include "clock.hpp"
#include "input.hpp"
#include "func.hpp"
#include "text.hpp"

class Application {
    Window m_window;
    double max_fps = 240;
    double max_delta = 0.1;

    Clock deltaclock;
    double delta = 0.;

    bool player2 = 1;

    Ball ball;
    Paddle paddle_left;
    Paddle paddle_right;
    Text score_text;
    int score_left = 0;
    int score_right = 0;

    bool init() {
        bool success = true;

        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << "\n";
            success = false;
        } else {
            if (IMG_Init(IMG_INIT_PNG) < 0) {
                std::cout << "SDL_image could not initialize! SDL Error: " << SDL_GetError() << "\n";
            }
            if (TTF_Init() < 0) {
                std::cout << "SDL_ttf could not initialize! SDL Error: " << SDL_GetError() << "\n";
            }

            //             m_window.reset(SDL_CreateWindow("Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            //                                             800, 600, SDL_WINDOW_SHOWN));
            //             if (m_window.get() == nullptr) {
            //                 std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << "\n";
            //                 success = false;
            //             }
            //             else {
            //
            //             }
        }

        return success;
    }

    void handle_events() {
        gm::Input::prepare();

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            gm::Input::update(event);

            if (event.type == SDL_QUIT) {
                m_window.close();
            }
        }
    }

    void draw() {
        paddle_left.draw(m_window.renderer());
        paddle_right.draw(m_window.renderer());
        ball.draw(m_window.renderer());
        score_text.draw(m_window.renderer());
    }

    void process_input() {
        //// Paddle left
        {
            if (gm::Input::isKeyPressed(SDLK_w)) {
                paddle_left.velocity.y = -paddle_left.speed;
            } else if (gm::Input::isKeyPressed(SDLK_s)) {
                paddle_left.velocity.y = paddle_left.speed;
            } else {
                paddle_left.velocity.y = 0;
            }
        }

        //// Paddle right
        if (player2) {
            if (gm::Input::isKeyPressed(SDLK_UP)) {
                paddle_right.velocity.y = -paddle_right.speed;
            } else if (gm::Input::isKeyPressed(SDLK_DOWN)) {
                paddle_right.velocity.y = paddle_right.speed;
            } else {
                paddle_right.velocity.y = 0;
            }
        }
    }

    void ball_reset() {
        ball.position = {800.f / 2, 600.f / 2};

        do {
            // Make sure the ball initial angle is not too much vertical
            ball.rotation = (std::rand() % 360) * pi / 180;
        } while (std::abs(std::cos(ball.rotation)) < 0.5f);
        ball.rotation /= pi / 180;
    }

    void move() {
        //// Paddle left
        {
            paddle_left.position.y += paddle_left.velocity.y * delta;
            if (paddle_left.position.y > 584 - paddle_left.center.y) {
                paddle_left.position.y = 584 - paddle_left.center.y;
            } else if (paddle_left.position.y < 16 + paddle_left.center.y) {
                paddle_left.position.y = 16 + paddle_left.center.y;
            }
        }

        //// Paddle right
        {
            paddle_right.position.y += paddle_right.velocity.y * delta;
            if (paddle_right.position.y > 584 - paddle_right.center.y) {
                paddle_right.position.y = 584 - paddle_right.center.y;
            } else if (paddle_right.position.y < 16 + paddle_right.center.y) {
                paddle_right.position.y = 16 + paddle_right.center.y;
            }
        }

        //// Ball
        {
            ball.velocity = rotate_vector({ball.speed, 0}, ball.rotation);
            ball.position.x += ball.velocity.x * delta;
            ball.position.y += ball.velocity.y * delta;

            if (ball.position.y > 600 - ball.center.y) {
                // ball.rotation -= 10 + (rand() % 70);
                // ball.rotation = -ball.rotation;
                do {
                    ball.rotation = rand() % 360;
                } while (abs(cos(ball.rotation * (pi / 180))) < 0.5);

                ball.position.y = 600 - ball.center.y;
            }
            if (ball.position.y < 0 + ball.center.y) {
                // ball.rotation -= 10 + (rand() % 70);
                // ball.rotation = -ball.rotation;
                do {
                    ball.rotation = rand() % 360;
                } while (abs(cos(ball.rotation * (pi / 180))) < 0.5);

                ball.position.y = 0 + ball.center.y;
            }

            if (intersects(ball, paddle_right)) {
                // ball.rotation -= 10 + (rand() % 70);
                do {
                    ball.rotation = rand() % 360;
                } while (cos(ball.rotation * (pi / 180)) > -0.5);

            } else if (ball.position.x > 800 - ball.center.x) {
                score_left += 1;
                ball_reset();
            }

            if (intersects(ball, paddle_left)) {
                // ball.rotation -= 10 + (rand() % 70);
                do {
                    ball.rotation = rand() % 360;
                } while (cos(ball.rotation * (pi / 180)) < 0.5);

            } else if (ball.position.x < 0 + ball.center.x) {
                score_right += 1;
                ball_reset();
            }
        }
    }

  public:
    Application() {
        std::srand(std::time(0));

        //     : m_window(nullptr, SDL_DestroyWindow), m_renderer(nullptr, SDL_DestroyRenderer) {
        init();

        m_window.create("Pong", 800, 600);

        //// Ball
        {
            ball.loadFromFile(m_window.renderer(), "./data/ball.svg");
            ball.center = {(float)ball.size.x / 2, (float)ball.size.y / 2};
            ball.position = {800.f / 2, 600.f / 2};

            do {
                ball.rotation = rand() % 360;
            } while (abs(cos(ball.rotation * (pi / 180))) < 0.5);
        }

        //// Paddle left
        {
            paddle_left.loadFromFile(m_window.renderer(), "./data/paddle.svg");
            paddle_left.center = {(float)paddle_left.size.x / 2, (float)paddle_left.size.y / 2};
            paddle_left.position.x = paddle_left.center.x + 16;
            paddle_left.position.y = 300;
        }

        //// Paddle right
        {
            paddle_right.loadFromFile(m_window.renderer(), "./data/paddle.svg");
            paddle_right.center = {(float)paddle_right.size.x / 2, (float)paddle_right.size.y / 2};
            paddle_right.position.x = 800 - paddle_right.center.x - 16;
            paddle_right.position.y = 300;
        }

        /// Score Text
        {
            score_text.loadFont("./data/RMSSans.otf", 48);
            score_text.position.y = 16;
        }
    }
    ~Application() {
        // TTF_Quit();
        IMG_Quit();
        SDL_Quit();
    }

    int start() {
        bool is_playing = 0;
        deltaclock.restart();
        while (m_window.isOpen()) {
            delta = deltaclock.restart();
            delta = delta > max_delta ? max_delta : delta;
            handle_events();

            if (is_playing) {
                process_input();
                move();
                score_text.setString(std::to_string(score_left) + " : " + std::to_string(score_right));                
            }
            else {
                score_text.setString("Press space to start.");
                if (gm::Input::isKeyJustPressed(SDLK_SPACE)) {
                    is_playing = 1;
                }
            }
            
            score_text.center.x = score_text.size.x / 2.f;
            score_text.position.x = 800.f / 2.f;

            m_window.clear({64, 128, 64, 255});

            draw();

            m_window.present();

            //             std::cout << "fps: " << 1 / delta << "\n";
            double sub = 1 / max_fps - deltaclock.elapsed();
            if (sub > 0) {
                sleep(sub / 1.01);
            }
        }

        return 0;
    }
};
