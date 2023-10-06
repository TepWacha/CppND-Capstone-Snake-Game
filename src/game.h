#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Controller const &controller,Controller const &controller2, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetP1Score() const;
  int GetP1Size() const;
  int GetP2Score() const;
  int GetP2Size() const;

 private:
  Snake snake;
  Snake snake2;
  SDL_Point food;
  SDL_Point landmine;
  SDL_Point poison;
  SDL_Point motivation;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;


  void PlaceFood();
  void PlaceLandmine();
  void PlacePoison();
  void PlaceMotivation();
  void Update();
  void SnakeUpdate(Snake &snake);
};

#endif