#pragma once

class SDLObject
{
public:
    virtual void render(SDL_Renderer *renderer) const = 0;
};
