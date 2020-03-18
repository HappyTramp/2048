#ifndef GRAPHICS_HPP
# define GRAPHICS_HPP

#include <string>
#include <SDL2/SDL.h>

class Graphics
{
    public:
    Graphics(std::string t, int w, int h);
    ~Graphics();

    void update();
    bool isRunning();

    private:
    bool running;
    std::string title;
    int width;
    int height;
    SDL_Renderer *renderer;
    SDL_Window *window;

    void handleEvent();
};

#endif
