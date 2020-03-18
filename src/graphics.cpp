#include "graphics.hpp"

Graphics::Graphics(std::string t, int w, int h)
{
    running = true;
    title = t;
    width = w;
    height = h;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        return;
    if ((window = SDL_CreateWindow(title.c_str(), 0, 0, width, height, 0)) == NULL)
        return;
    if ((renderer = SDL_CreateRenderer(window, -1, 0)) == NULL)
        return;
}

Graphics::~Graphics()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Graphics::update()
{
    SDL_RenderClear(renderer);
    handleEvent();
    SDL_RenderPresent(renderer);
}

bool Graphics::isRunning()
{
    return running;
}

void Graphics::handleEvent()
{
    SDL_Event e;

    while (SDL_PollEvent(&e))
    {
        switch (e.type)
        {
            case SDL_QUIT:
                running = false;
        }
    }

}
