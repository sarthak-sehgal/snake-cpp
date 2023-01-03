#pragma once

#include <SDL2/SDL.h>

#include "food.hpp"
#include "snake.hpp"

#include <tuple>

class Game
{
public:
  Game();
  void start();
  void over();
  void consumeFood();
  auto getDimensions() const
  {
    return std::tuple(WIDTH, HEIGHT);
  }
  SDL_Rect getFood() const;
  int getScore() const;

private:
  SDL_Window *mWindow;     // TODO: smart ptr
  SDL_Renderer *mRenderer; // TODO: smart ptr
  Snake mSnake;
  Food mFood;
  bool mRunning = false;
  int mLevel = 0;
  static const int HEIGHT;
  static const int WIDTH;
};