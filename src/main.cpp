#include <fmt/core.h>

#include "sdl2_backend.h"

int main(int argc, char * argv[])
{
  
    SDL2Backend backend;
    backend.init("Atsin Comestrike",800,600,true);
    
    auto renderer = backend.get_renderer();

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    SDL_Rect fillRect = {0, 0, 256, 256};
    SDL_RenderFillRect(renderer, &fillRect);

    SDL_RenderPresent(renderer);

    SDL_Delay(5000);
}

