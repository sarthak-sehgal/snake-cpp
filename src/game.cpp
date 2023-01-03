#include "direction.hpp"
#include "food.hpp"
#include "game.hpp"
#include "snake.hpp"

#include <iostream>

Game::Game() : mWindow{SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0)}, mRenderer{SDL_CreateRenderer(mWindow, -1, 0)}, mSnake{}, mFood{WIDTH, HEIGHT}
{
  SDL_Init(SDL_INIT_EVERYTHING);
}

std::ostream &operator<<(std::ostream &os, Direction const &dir)
{
  if (dir == Direction::DOWN)
    os << "DOWN";
  if (dir == Direction::UP)
    os << "UP";
  if (dir == Direction::LEFT)
    os << "LEFT";
  if (dir == Direction::RIGHT)
    os << "RIGHT";
  return os;
}

void Game::start()
{
  SDL_Event e;
  mRunning = true;
  Direction dir{Direction::RIGHT};
  for (;;)
  {
    if (SDL_PollEvent(&e))
    {
      if (e.type == SDL_QUIT)
      {
        over();
        break;
      }

      if (e.type == SDL_KEYDOWN)
      {
        switch (e.key.keysym.sym)
        {
        case SDLK_DOWN:
          dir = Direction::DOWN;
          break;
        case SDLK_UP:
          dir = Direction::UP;
          break;
        case SDLK_LEFT:
          dir = Direction::LEFT;
          break;
        case SDLK_RIGHT:
          dir = Direction::RIGHT;
          break;
        default:
          break;
        }
      }

      std::cout << "received keystroke, dir = " << dir << "\n";
    }
    mSnake.handleDirectionChange(dir, *this);

    if (!mRunning)
      break;

    // clear window
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
    SDL_RenderClear(mRenderer);

    mSnake.render(mRenderer);
    mFood.render(mRenderer);

    SDL_RenderPresent(mRenderer);
    SDL_Delay(std::max(25, 80 - mLevel * 3));
  }
}

void Game::over()
{
  std::cout << "Game over.\n";
  mRunning = false;
}

void Game::consumeFood()
{
  mLevel += 1;
  mFood.consume();
}

SDL_Rect Game::getFood() const
{
  return mFood.get();
}

int Game::getScore() const
{
  return mLevel * 5;
}

const int Game::HEIGHT = 500;
const int Game::WIDTH = 500;