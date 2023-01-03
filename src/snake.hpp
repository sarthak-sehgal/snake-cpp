#pragma once

#include <SDL2/SDL.h>

#include "direction.hpp"
#include "sdl_object.hpp"

#include <deque>
#include <random>

class Game;

class Snake : public SDLObject
{
public:
    Snake();
    void render(SDL_Renderer *renderer) const override;
    void handleDirectionChange(Direction newDir, Game &game);

private:
    bool isOppositeDirection(Direction const &dir);
    bool isCollision(SDL_Rect const &point);
    SDL_Rect getNewHead(Direction const &newDir, Game const &game);

    Direction mCurrDirection;
    std::deque<SDL_Rect> mBody;
    unsigned mSize = 1;
};

inline bool operator==(const SDL_Rect &a, const SDL_Rect &b)
{
    return a.x == b.x && a.y == b.y && a.w == b.w && a.h == b.h;
}
