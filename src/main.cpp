#include <iostream>
#include <cstdlib>
#include "graphics.hpp"
#include "game.hpp"
#include "ai.hpp"
#include "rand_ai.hpp"

#define WINDOW_TITLE "2048"
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define GAME_GRID_SIZE 4

int main(int argc, char **argv)
{
    Graphics *graphics;

    srand(time(NULL));
    Game game = Game(GAME_GRID_SIZE);
    if (argc == 2 && strcmp(argv[1], "--ai") == 0)
    {
        RandAI ai = RandAI(&game);
        graphics = new Graphics(game, WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT, &ai);
    }
    else
        graphics = new Graphics(game, WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT);
    while (graphics->isRunning())
        graphics->update();
    delete graphics;
    return 0;
}
