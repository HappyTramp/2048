#ifndef GRAPHICS_HPP
# define GRAPHICS_HPP

#include <string>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "game.hpp"

class Graphics
{
    public:
    Graphics(Game *g, std::string t, int w, int h);
    ~Graphics();

    void update();
    void drawGame();
    void drawCell(int x, int y);
    bool isRunning();

    private:
    bool running;
    std::string title;
    int width;
    int height;
    Game *game;
    SDL_Renderer *renderer;
    SDL_Window *window;
    TTF_Font *font;

    void handleEvent();
    void error();
};

#endif
