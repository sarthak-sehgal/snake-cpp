#include "food.hpp"

#include <random>

// TODO: add width/height checks
Food::Food(int width, int height) : mXDistribution{std::uniform_int_distribution<int>(10, width - 20)},
                                    mYDistribution{std::uniform_int_distribution<int>(10, height - 20)},
                                    mRd{},
                                    mEngine{mRd()},
                                    mFood(produceFood())
{
}

void Food::consume()
{
  mFood = produceFood();
}

SDL_Rect Food::get() const
{
  return mFood;
}

void Food::render(SDL_Renderer *renderer) const
{
  SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // TODO: use some config to get color
  SDL_RenderFillRect(renderer, &mFood);
}

// TODO: fix hard coded dimensions
// TODO: add check that food should not be on snake body
SDL_Rect Food::produceFood()
{
  int x = roundDown(mXDistribution(mEngine), 10);
  int y = roundDown(mYDistribution(mEngine), 10);

  return SDL_Rect{x, y, 10, 10};
}

int Food::roundDown(int num, int base) const
{
  return num - num % base;
}