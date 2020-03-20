#include "graphics.hpp"

#define CELL_GAP 5
#define GRID_BORDER 10
#define UPDATE_DELAY 3
#define AI_TIME_STEP 100

Graphics::Graphics(Game &game, std::string title, int width, int height, AI *ai):
    m_running(true), m_game(game), m_title(title), m_width(width), m_height(height), m_ai(ai), m_aiTimeStep(AI_TIME_STEP)
{
    m_gridSize = std::min(m_width, m_height);
    m_aiNextTime = SDL_GetTicks();

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        error();
    if ((m_window = SDL_CreateWindow(m_title.c_str(), 0, 0, m_width, m_height, 0)) == NULL)
        error();
    if ((m_renderer = SDL_CreateRenderer(m_window, -1, 0)) == NULL)
        error();
    if (TTF_Init() < 0)
        error();
    if ((m_font = TTF_OpenFont("./font/noto_mono_regular.ttf", 16)) == NULL)
        error();
    m_scoreText = newTextTex("score", {255, 255, 255, 255});
    m_palette[0] = {10, 10, 10, 255};
    m_palette[2] = {100, 100, 100, 255};
    m_palette[4] = {65, 65, 65, 255};
    m_palette[8] = {40, 40, 40, 255};
    m_palette[16] = {150, 50, 20, 255};
    m_palette[32] = {160, 70, 20, 255};
    m_palette[64] = {190, 80, 30, 255};
    m_palette[128] = {200, 100, 40, 255};
    m_palette[256] = {220, 120, 40, 255};
    m_palette[512] = {230, 180, 30, 255};
    m_palette[1024] = {230, 190, 20, 255};
    m_palette[2048] = {230, 200, 10, 255};
}

Graphics::~Graphics()
{
    for (size_t i = 0; i < m_numberTexBuf.size(); i++)
        SDL_DestroyTexture(m_numberTexBuf[i].second);
    TTF_CloseFont(m_font);
    TTF_Quit();
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void Graphics::update()
{
    if (m_game.lost())
        m_running = false;
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(m_renderer);
    handleEvent();
    drawGame();
    drawScore();
    SDL_RenderPresent(m_renderer);
    if (m_ai != NULL)
    {
        if (SDL_TICKS_PASSED(SDL_GetTicks(), m_aiNextTime))
        {
            m_aiNextTime = SDL_GetTicks() + m_aiTimeStep;
            m_game.move(m_ai->move());
        }
    }
    SDL_Delay(UPDATE_DELAY);
}

void Graphics::drawGame()
{
    for (int i = 0; i < m_game.getSize(); i++)
        for (int j = 0; j < m_game.getSize(); j++)
            drawCell(i, j);
}

void Graphics::drawCell(int x, int y)
{
    SDL_Rect r;
    SDL_Texture *tex;
    SDL_Color c;

    if ((tex = getNumberTex(m_game.get(y, x))) == NULL)
        tex = addNumberTex(m_game.get(y, x));
    if (m_palette.find(m_game.get(y, x)) == m_palette.end())
        c = {30, 30, 30, 255};
    else
        c = m_palette[m_game.get(y, x)];
    r.x = 2 + x * (m_gridSize / m_game.getSize());
    r.y = 2 + y * (m_gridSize / m_game.getSize());
    r.w = m_gridSize / m_game.getSize() - 5;
    r.h = m_gridSize / m_game.getSize() - 5;
    SDL_SetRenderDrawColor(m_renderer, c.r, c.g, c.b, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(m_renderer, &r);
    if (m_game.get(y, x) != 0)
    {
        SDL_QueryTexture(tex, NULL, NULL, &r.w, &r.h);
        r.x += m_gridSize / m_game.getSize() / 2 - r.w / 2;
        r.y += m_gridSize / m_game.getSize() / 2 - r.h / 2;
        SDL_RenderCopy(m_renderer, tex, NULL, &r);
    }
}

void Graphics::drawScore()
{
    SDL_Rect r;
    int dist = std::abs(m_width - m_height);

    if (dist < 50)
        return;
    SDL_QueryTexture(m_scoreText, NULL, NULL, &r.w, &r.h);
    if (m_width > m_height)
    {
        r.x = m_width - dist / 2 - r.w / 2;
        r.y = m_height / 2;
    }
    else
    {
        r.x = m_width / 2;
        r.y = m_height - dist / 2 - r.h / 2;
    }
    SDL_RenderCopy(m_renderer, m_scoreText, NULL, &r);

    SDL_Texture *scoreNumTex = newTextTex(std::to_string(m_game.getScore()), {255, 255, 255, 255});
    SDL_QueryTexture(scoreNumTex, NULL, NULL, &r.w, &r.h);
    if (m_width > m_height)
        r.y += 20;
    else
        r.x += 20;
    SDL_RenderCopy(m_renderer, scoreNumTex, NULL, &r);
    SDL_DestroyTexture(scoreNumTex);
}

bool Graphics::isRunning() const
{
    return m_running;
}

void Graphics::handleEvent()
{
    SDL_Event e;

    while (SDL_PollEvent(&e))
    {
        switch (e.type)
        {
            case SDL_QUIT:
                m_running = false;
                break;
            case SDL_KEYDOWN:
                switch (e.key.keysym.sym)
                {
                    case SDLK_LEFT:
                        m_game.move(DIRECTION_LEFT);
                        break;
                    case SDLK_RIGHT:
                        m_game.move(DIRECTION_RIGHT);
                        break;
                    case SDLK_DOWN:
                        m_game.move(DIRECTION_DOWN);
                        break;
                    case SDLK_UP:
                        m_game.move(DIRECTION_UP);
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
    m_numberTexBuf.push_back(std::make_pair(n, tex));
    return tex;
}

SDL_Texture *Graphics::getNumberTex(int n) const
{
    for (size_t i = 0; i < m_numberTexBuf.size(); i++)
        if (m_numberTexBuf[i].first == n)
            return m_numberTexBuf[i].second;
    return NULL;
}

SDL_Texture *Graphics::newTextTex(std::string s, SDL_Color c)
{
    SDL_Surface *surface;
    SDL_Texture *tex;

    if ((surface = TTF_RenderText_Solid(m_font, s.c_str(), c)) == NULL)
        error();
    if ((tex = SDL_CreateTextureFromSurface(m_renderer, surface)) == NULL)
        error();
    SDL_FreeSurface(surface);
    return (tex);
}

void Graphics::error() const
{
    std::cout << SDL_GetError() << std::endl;
    exit(1);
}
