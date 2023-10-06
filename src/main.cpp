#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Controller controller2;
  Game game(kGridWidth, kGridHeight);
  game.Run(controller, controller2, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "P1 Score: " << game.GetP1Score() << "\n";
  std::cout << "P1 Size: " << game.GetP1Size() << "\n";
  std::cout << "P2 Score: " << game.GetP2Score() << "\n";
  std::cout << "P2 Size: " << game.GetP2Size() << "\n";
  return 0;
}