#include "graphics.hpp"

#define CELL_GAP 5
#define GRID_BORDER 10
#define AI_TIME_STEP 100

Graphics::Graphics(Game *g, std::string t, int w, int h, AI *a)
{
    running = true;
    game = g;
    title = t;
    width = w;
    height = h;
    gridSize = std::min(width, height);
    ai = a;
    aiTimeStep = AI_TIME_STEP;
    aiNextTime = SDL_GetTicks();

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
    scoreText = newTextTex("score", {255, 255, 255, 255});
    palette[0] = {10, 10, 10, 255};
    palette[2] = {100, 100, 100, 255};
    palette[4] = {65, 65, 65, 255};
    palette[8] = {40, 40, 40, 255};
    palette[16] = {150, 50, 20, 255};
    palette[32] = {160, 70, 20, 255};
    palette[64] = {190, 80, 30, 255};
    palette[128] = {200, 100, 40, 255};
    palette[256] = {220, 120, 40, 255};
    palette[512] = {230, 180, 30, 255};
    palette[1024] = {230, 190, 20, 255};
    palette[2048] = {230, 200, 10, 255};
}

Graphics::~Graphics()
{
    for (size_t i = 0; i < numberTexBuf.size(); i++)
        SDL_DestroyTexture(numberTexBuf[i].second);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Graphics::update()
{
    if (game->lost())
        running = false;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    handleEvent();
    drawGame();
    drawScore();
    SDL_RenderPresent(renderer);
    if (ai != NULL)
    {
        if (SDL_TICKS_PASSED(SDL_GetTicks(), aiNextTime))
        {
            aiNextTime = SDL_GetTicks() + aiTimeStep;
            game->move(ai->move());
        }
    }
    SDL_Delay(3);
}

void Graphics::drawGame()
{
    for (int i = 0; i < game->getSize(); i++)
        for (int j = 0; j < game->getSize(); j++)
            drawCell(i, j);
}

void Graphics::drawCell(int x, int y)
{
    SDL_Rect r;
    SDL_Texture *tex;
    SDL_Color c;

    if ((tex = getNumberTex(game->at(x, y))) == NULL)
        tex = addNumberTex(game->at(x, y));
    if (palette.find(game->at(x, y)) == palette.end())
        c = {30, 30, 30, 255};
    else
        c = palette[game->at(x, y)];
    r.x = 2 + x * (gridSize / game->getSize());
    r.y = 2 + y * (gridSize / game->getSize());
    r.w = gridSize / game->getSize() - 5;
    r.h = gridSize / game->getSize() - 5;
    SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &r);
    if (game->at(x, y) != 0)
    {
        SDL_QueryTexture(tex, NULL, NULL, &r.w, &r.h);
        r.x += gridSize / game->getSize() / 2 - r.w / 2;
        r.y += gridSize / game->getSize() / 2 - r.h / 2;
        SDL_RenderCopy(renderer, tex, NULL, &r);
    }
}

void Graphics::drawScore()
{
    SDL_Rect r;
    int dist = std::abs(width - height);

    if (dist < 50)
        return;
    SDL_QueryTexture(scoreText, NULL, NULL, &r.w, &r.h);
    if (width > height)
    {
        r.x = width - dist / 2 - r.w / 2;
        r.y = height / 2;
    }
    else
    {
        r.x = width / 2;
        r.y = height - dist / 2 - r.h / 2;
    }
    SDL_RenderCopy(renderer, scoreText, NULL, &r);

    SDL_Texture *scoreNumTex = newTextTex(std::to_string(game->getScore()), {255, 255, 255, 255});
    SDL_QueryTexture(scoreNumTex, NULL, NULL, &r.w, &r.h);
    if (width > height)
        r.y += 20;
    else
        r.x += 20;
    SDL_RenderCopy(renderer, scoreNumTex, NULL, &r);
    SDL_DestroyTexture(scoreNumTex);
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
                break;
            case SDL_KEYDOWN:
                switch (e.key.keysym.sym)
                {
                    case SDLK_LEFT:
                        game->move(DIRECTION_LEFT);
                        break;
                    case SDLK_RIGHT:
                        game->move(DIRECTION_RIGHT);
                        break;
                    case SDLK_DOWN:
                        game->move(DIRECTION_DOWN);
                        break;
                    case SDLK_UP:
                        game->move(DIRECTION_UP);
                        break;
                }
        }
    }
}

SDL_Texture *Graphics::addNumberTex(int n)
{
    SDL_Texture *tex;
    SDL_Color c = {255, 255, 255, 255};
    tex = newTextTex(std::to_string(n), c);
    numberTexBuf.push_back(std::make_pair(n, tex));
    return tex;
}

SDL_Texture *Graphics::getNumberTex(int n)
{
    for (size_t i = 0; i < numberTexBuf.size(); i++)
        if (numberTexBuf[i].first == n)
            return numberTexBuf[i].second;
    return NULL;
}

SDL_Texture *Graphics::newTextTex(std::string s, SDL_Color c)
{
    SDL_Surface *surface;
    SDL_Texture *tex;

    if ((surface = TTF_RenderText_Solid(font, s.c_str(), c)) == NULL)
        error();
    if ((tex = SDL_CreateTextureFromSurface(renderer, surface)) == NULL)
        error();
    SDL_FreeSurface(surface);
    return (tex);
}

void Graphics::error()
{
    std::cout << SDL_GetError() << std::endl;
    exit(1);
}
