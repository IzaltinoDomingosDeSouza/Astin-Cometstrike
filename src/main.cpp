#include <SDL2/SDL.h>
#include <fmt/core.h>

int main(int argc, char * argv[])
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fmt::print("SDL could not initialize! SDL_Error : {}\n", SDL_GetError());
        return 1;
    }
    SDL_Window * window = SDL_CreateWindow("SDL2 Rectangle Example",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          800, 600,
                                          SDL_WINDOW_SHOWN);
    if(!window)
    {
        fmt::print("Window could not be created! SDL_Error: {}\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(!renderer)
    {
        fmt::print("Renderer could not be created! SDL_Error : {}\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    SDL_Rect fillRect = {0, 0, 256, 256};
    SDL_RenderFillRect(renderer, &fillRect);

    SDL_RenderPresent(renderer);

    SDL_Delay(5000);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

