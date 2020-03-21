#ifndef GRAPHICS_HPP
# define GRAPHICS_HPP

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <utility>
#include <utility>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "game.hpp"
#include "2048.hpp"
#include "ai.hpp"

class Graphics
{
    public:
    Graphics(Game &game, std::string title, int width, int height, AI *ai = NULL);
    ~Graphics();

    void update();
    bool isRunning() const;

    private:
    bool         m_running;
    Game         &m_game;
    std::string  m_title;
    int          m_width;
    int          m_height;
    AI           *m_ai;
    Uint32       m_aiTimeStep;
    int          m_gridSize;
    Uint32       m_aiNextTime;
    SDL_Renderer *m_renderer;
    SDL_Window   *m_window;
    TTF_Font     *m_font;
    SDL_Texture  *m_scoreText;

    std::vector< std::pair<int, SDL_Texture*> >
        m_numberTexBuf;
    std::map< int, SDL_Color >
        m_palette;

    void        drawGame();
    void        drawCell(int x, int y);
    void        drawScore();
    void        handleEvent();
    SDL_Texture *addNumberTex(int n);
    SDL_Texture *getNumberTex(int n) const;
    SDL_Texture *newTextTex(std::string s, SDL_Color c, SDL_Color bg);
    void        error() const;

    static SDL_Color   makeColor(int r, int g, int b);
    static std::string intToString(int n);
};

#endif
