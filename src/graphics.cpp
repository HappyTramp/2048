#include "graphics.hpp"

Graphics::Graphics(Game *g, std::string t, int w, int h)
{
    running = true;
    game = g;
    title = t;
    width = w;
    height = h;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        error();
    if ((window = SDL_CreateWindow(title.c_str(), 0, 0, width, height, 0)) == NULL)
        error();
    if ((renderer = SDL_CreateRenderer(window, -1, 0)) == NULL)
        error();
    if (TTF_Init() < 0)
        error();
    if ((font = TTF_OpenFont("./font/noto_mono_regular.ttf", 16)) == NULL)
        error();
    std::cout << font << std::endl;
}

Graphics::~Graphics()
{
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Graphics::update()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    handleEvent();
    drawGame();
    SDL_RenderPresent(renderer);
    SDL_Delay(3);
}

void Graphics::drawGame()
{
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, SDL_ALPHA_OPAQUE);
    for (int i = 0; i < game->getSize(); i++)
        for (int j = 0; j < game->getSize(); j++)
            drawCell(i, j);
}

void Graphics::drawCell(int x, int y)
{
    SDL_Rect r;
    SDL_Color c;
    SDL_Surface *text;
    SDL_Texture *tex;

    c.r = 255;
    c.g = 255;
    c.b = 255;
    c.a = 255;
    if ((text = TTF_RenderText_Solid(font, std::to_string(game->at(x, y)).c_str(), c)) == NULL)
        error();
    if ((tex = SDL_CreateTextureFromSurface(renderer, text)) == NULL)
        error();
    SDL_FreeSurface(text);
    r.x = 2 + x * (width / game->getSize());
    r.y = 2 + y * (height / game->getSize());
    r.w = (width / game->getSize() - 5);
    r.h = (height / game->getSize() - 5);
    SDL_RenderFillRect(renderer, &r);
    r.x += 20;
    r.y += 20;
    SDL_QueryTexture(tex, NULL, NULL, &r.w, &r.h);
    SDL_RenderCopy(renderer, tex, NULL, &r);
    SDL_DestroyTexture(tex);
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

void Graphics::error()
{
    std::cout << SDL_GetError() << std::endl;
    exit(1);
}
