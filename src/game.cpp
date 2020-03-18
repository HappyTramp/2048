#include "game.hpp"


Game::Game(int s)
{
    size = s;
    grid = new int*[size];
    for (int i = 0; i < size; i++)
        grid[i] = new int[size];
}

Game::~Game()
{
    for (int i = 0; i < size; i++)
        delete []grid[i];
    delete []grid;
}

int Game::getSize()
{
    return size;
}

int Game::at(int x, int y)
{
    return grid[y][x];
}
