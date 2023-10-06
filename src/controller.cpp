#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "snake.h"

void Controller::ChangeDirection(Snake &snake, Snake::Direction input,
                                 Snake::Direction opposite) const {
  if (snake.direction != opposite || snake.size == 1) snake.direction = input;
  return;
}

void Controller::HandleInput(bool &running, Snake &snake, Snake &snake2) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      HandleSnake(e, snake);
      HandleSnake(e, snake2);
    }
  }
}

void Controller::HandleSnake(SDL_Event &e, Snake &snake) const {
  if (e.key.keysym.sym == snake.up) {
    ChangeDirection(snake, Snake::Direction::kUp, Snake::Direction::kDown);
  } else if (e.key.keysym.sym == snake.down) {
    ChangeDirection(snake, Snake::Direction::kDown, Snake::Direction::kUp);
  } else if (e.key.keysym.sym == snake.left) {
    ChangeDirection(snake, Snake::Direction::kLeft, Snake::Direction::kRight);
  } else if (e.key.keysym.sym == snake.right) {
    ChangeDirection(snake, Snake::Direction::kRight, Snake::Direction::kLeft);
  }
}