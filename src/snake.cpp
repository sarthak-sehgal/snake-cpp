#include "game.hpp"
#include "snake.hpp"

#include <algorithm>
#include <iostream>

Snake::Snake() : mCurrDirection{Direction::RIGHT}, mBody{{SDL_Rect{500, 500, 10, 10}}}
{
}

// TODO: use shared ptr
// https://stackoverflow.com/questions/48672399/is-it-possible-to-use-sdl2-with-smart-pointers
void Snake::render(SDL_Renderer *renderer) const
{
    std::cout << "rendering snake, size=" << mBody.size() << "\n";
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // TODO: use some config to get color
    std::for_each(mBody.begin(), mBody.end(), [&](auto &snake_segment)
                  { SDL_RenderFillRect(renderer, &snake_segment); });
}

void Snake::handleDirectionChange(Direction newDir, Game &game)
{
    if (isOppositeDirection(newDir))
    {
        // keep continuing on same path if new direction is opposite
        newDir = mCurrDirection;
    }

    auto newHead = getNewHead(newDir, game);

    // check for self collision
    if (isCollision(newHead))
    {
        std::cout << "Collision - exiting.\n";
        game.over();
        return;
    }

    // check for food consumed
    if (newHead == game.getFood())
    {
        game.consumeFood();
        mSize += 10;
    }

    mCurrDirection = newDir;
    mBody.push_front(newHead);
    while (mBody.size() > mSize)
        mBody.pop_back();

    std::cout << "handleDirectionChange end()\n";
}

SDL_Rect Snake::getNewHead(Direction const &newDir, Game const &game)
{
    auto newHead = mBody.front();
    switch (newDir)
    {
    case Direction::DOWN:
        newHead.y += 10;
        break;
    case Direction::UP:
        newHead.y -= 10;
        break;
    case Direction::LEFT:
        newHead.x -= 10;
        break;
    case Direction::RIGHT:
        newHead.x += 10;
        break;
    }

    auto const &[windowHeight, windowWidth] = game.getDimensions();
    if (newHead.x < 0)
        newHead.x += windowWidth;
    if (newHead.y < 0)
        newHead.y += windowHeight;
    newHead.x %= windowWidth;
    newHead.y %= windowHeight;

    return newHead;
}

bool Snake::isCollision(SDL_Rect const &point)
{
    return std::any_of(mBody.begin(), mBody.end(), [&](auto &segment)
                       { return segment == point; });
}

bool Snake::isOppositeDirection(Direction const &dir)
{
    using enum Direction;
    return (mCurrDirection == DOWN && dir == UP || mCurrDirection == UP && dir == DOWN || mCurrDirection == RIGHT && dir == LEFT || mCurrDirection == LEFT && dir == RIGHT);
}
