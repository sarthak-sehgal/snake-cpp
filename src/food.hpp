#pragma once

#include <SDL2/SDL.h>

#include "sdl_object.hpp"

#include <random>

class Food : public SDLObject
{
public:
    Food(int width, int height);
    void consume();
    SDL_Rect get() const;
    void render(SDL_Renderer *renderer) const override;

private:
    SDL_Rect produceFood();
    int roundDown(int num, int base) const;

    std::uniform_int_distribution<int> mXDistribution;
    std::uniform_int_distribution<int> mYDistribution;
    std::random_device mRd;
    std::mt19937 mEngine;
    SDL_Rect mFood;
};
