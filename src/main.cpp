#include <iostream>
#include <SDL2/SDL.h>
#include "graphics.hpp"

#define WINDOW_TITLE "2048"
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

int main()
{
    Graphics g = Graphics(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT);

    while (g.isRunning())
        g.update();

    return 0;
}
