#include "game.h"
#include <iostream>
#include "SDL.h"
#include "playerq.h"

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(Player::plyr1, grid_width, grid_height, grid_width * 3 / 4, grid_height, SDLK_UP, SDLK_DOWN, SDLK_LEFT, SDLK_RIGHT),
      snake2(Player::plyr2, grid_width , grid_height, grid_width / 4 , grid_height, SDLK_w, SDLK_s, SDLK_a, SDLK_d),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)) {
  PlaceFood();
  PlaceLandmine();
  PlacePoison();
  PlaceMotivation();
}

void Game::Run(Controller const &controller, Controller const &controller2, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake, snake2);
    Update();
    renderer.Render(snake, snake2, food, landmine, poison, motivation);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y)) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

void Game::PlaceLandmine() {
    int x, y;
    while (true) {
        x = random_w(engine);
        y = random_h(engine);
        // Check that the location is not occupied by a snake item or food before placing
        // landmine.
        if (!snake.SnakeCell(x, y) && !(food.x == x && food.y == y)) {
            landmine.x = x;
            landmine.y = y;
            return;
        }
    }
}

void Game::PlacePoison() {
    int x, y;
    while (true) {
        x = random_w(engine);
        y = random_h(engine);
        // Check that the location is not occupied by a snake item or food or landmine before placing
        // poison.
        if (!snake.SnakeCell(x, y) && !(food.x == x && food.y == y) && !(landmine.x == x && landmine.y == y)) {
            poison.x = x;
            poison.y = y;
            return;
        }
    }
}

void Game::PlaceMotivation() {
    int x, y;
    while (true) {
        x = random_w(engine);
        y = random_h(engine);
        // Check that the location is not occupied by a snake item or food or landmine or poison before placing
        // motivation.
        if (!snake.SnakeCell(x, y) && !(food.x == x && food.y == y) && !(landmine.x == x && landmine.y == y) && !(poison.x == x && poison.y == y)) {
            motivation.x = x;
            motivation.y = y;
            return;
        }
    }
}

void Game::Update() {
  if (!snake.alive || !snake2.alive) return;

  snake.Update();
  snake2.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    score++;
    PlaceFood();
    PlaceLandmine();
    PlacePoison();
    PlaceMotivation();
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.02;
  }
  // Check if there's landmine over here
  if (landmine.x == new_x && landmine.y == new_y) {
      snake.alive = false;
      return;
  }
  if (poison.x == new_x && poison.y == new_y) {
      PlaceFood();
      PlaceLandmine();
      PlacePoison();
      PlaceMotivation();
      snake.speed -= 0.05;
  }
  if (motivation.x == new_x && motivation.y == new_y) {
      PlaceFood();
      PlaceLandmine();
      PlacePoison();
      PlaceMotivation();
      snake.speed += 0.05;
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }