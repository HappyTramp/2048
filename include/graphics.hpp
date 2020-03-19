#ifndef GRAPHICS_HPP
# define GRAPHICS_HPP

#include <string>
#include <iostream>
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
    Graphics(Game *g, std::string t, int w, int h, AI *ai = NULL);
    ~Graphics();

    void update();
    bool isRunning();

    private:
    bool running;
    std::string title;
    int width;
    int height;
    int gridSize;
    Game *game;
    SDL_Renderer *renderer;
    SDL_Window *window;
    TTF_Font *font;
    SDL_Texture *scoreText;
    std::vector< std::pair<int, SDL_Texture*> > numberTexBuf;
    std::map< int, SDL_Color > palette;
    AI *ai;
    Uint32 aiTimeStep;
    Uint32 aiNextTime;


    void drawGame();
    void drawCell(int x, int y);
    void drawScore();
    void handleEvent();
    SDL_Texture *addNumberTex(int n);
    SDL_Texture *getNumberTex(int n);
    SDL_Texture *newTextTex(std::string s, SDL_Color c);
    void error();
};

#endif
