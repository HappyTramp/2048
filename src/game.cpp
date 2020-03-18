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

void Game::move(Direction direction)
{
    switch (direction)
    {
        case DIRECTION_LEFT:
            break;
        case DIRECTION_RIGHT:
            // for (int i = 0; i < size; i++)
            //     for (int j = size - 2; j >= 0; j--)
            //     {
            //         if (grid[i][j + 1] == grid[i][j])
            //         {
            //             grid[i][j + 1] *= 2;
            //             for (int k = j; k >= 0; k--)
            //                 grid[i][k] = grid[i][k - 1];
            //             grid[i][shifts] = 0;
            //             shifts++;
            //         }
            //     }
            break;
        case DIRECTION_DOWN:
            break;
        case DIRECTION_UP:
            // for (int i = size - 2; i >= 0; i--)
            //     for (int j = 0; j < size; j++)
            //     {
            //         if (grid[i + 1][j] == grid[i][j])
            //         {
            //             grid[i + 1][j 1] *= 2;
            //             for (int k = j; k >= 0; k--)
            //                 grid[i][k] = grid[i][k - 1];
            //             grid[i][shifts] = 0;
            //             shifts++;
            //         }
            //     }
            break;
    }
    spawn();
}

void Game::spawn()
{
    int i;
    int j;

    do
    {
        i = rand() % size;
        j = rand() % size;
    }
    while (grid[i][j] != 0);
    grid[i][j] = 2;
}

bool Game::lost()
{
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
        {
            if (grid[i][j] == 0)
                return false;
            if (i - 1 >= 0 && grid[i - 1][j] == grid[i][j])
                return false;
            if (i + 1 < size && grid[i + 1][j] == grid[i][j])
                return false;
            if (j - 1 >= 0 && grid[i][j - 1] == grid[i][j])
                return false;
            if (j + 1 < size && grid[i][j + 1] == grid[i][j])
                return false;
        }
    return true;
}
