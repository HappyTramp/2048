#include <iostream>
#include <cstdlib>
#include "graphics.hpp"
#include "game.hpp"

#define WINDOW_TITLE "2048"
#define WINDOW_WIDTH 480
#define WINDOW_HEIGHT 480
#define GAME_GRID_SIZE 6

int main()
{
    srand(time(NULL));
    Game game = Game(GAME_GRID_SIZE);
    Graphics *graphics = new Graphics(&game, WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT);

    while (graphics->isRunning())
        graphics->update();

    delete graphics;

    return 0;
}
