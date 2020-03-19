#include "game.hpp"


Game::Game(int s)
{
    size = s;
    grid = new int*[size];
    for (int i = 0; i < size; i++)
    {
        grid[i] = new int[size];
        for (int j = 0; j < size; j++)
            grid[i][j] = 0;
    }
    spawn();
    spawn();
    score = 0;
}

Game::~Game()
{
    gridDestroy(grid);
}

int Game::getSize()
{
    return size;
}

int Game::getScore()
{
    return score;
}

int Game::at(int x, int y)
{
    return grid[y][x];
}

void Game::move(Direction direction)
{
    std::vector<int> row;
    int **saved = gridCopy();

    switch (direction)
    {
        case DIRECTION_LEFT:
            for (int i = 0; i < size; i++)
            {
                row.clear();
                for (int j = 0; j < size; j++)
                    row.push_back(grid[i][j]);
                mergeRow(row);
                for (int j = 0; j < size; j++)
                    grid[i][j] = row[j];
            }
            break;
        case DIRECTION_RIGHT:
            for (int i = 0; i < size; i++)
            {
                row.clear();
                for (int j = size - 1; j >= 0; j--)
                    row.push_back(grid[i][j]);
                mergeRow(row);
                for (int j = size - 1; j >= 0; j--)
                    grid[i][j] = row[size - j - 1];
            }
            break;
        case DIRECTION_DOWN:
            for (int j = 0; j < size; j++)
            {
                row.clear();
                for (int i = size - 1; i >= 0; i--)
                    row.push_back(grid[i][j]);
                mergeRow(row);
                for (int i = size - 1; i >= 0; i--)
                    grid[i][j] = row[size - i - 1];
            }
            break;
        case DIRECTION_UP:
            for (int j = 0; j < size; j++)
            {
                row.clear();
                for (int i = 0; i < size; i++)
                    row.push_back(grid[i][j]);
                mergeRow(row);
                for (int i = 0; i < size; i++)
                    grid[i][j] = row[i];
            }
            break;
    }
    if (!gridEqual(saved))
        spawn();
    gridDestroy(saved);
}

void Game::spawn()
{
    std::vector< std::pair<int, int> > possible;

    if (lost())
        return;
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
        {
            if (grid[i][j] == 0)
                possible.push_back(std::make_pair(i, j));
        }
    if (possible.size() < 1)
        return;
    std::pair<int, int> pos = possible[rand() % possible.size()];
    grid[pos.first][pos.second] = rand() % 2 == 0 ? 2 : 4;
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

void Game::mergeRow(std::vector<int> &row)
{
    if (row.size() < 2)
        return;
    int pivot = 0;
    for (size_t curr = 0; curr < row.size() - 1; curr++)
    {
        if (row[pivot] != 0)
        {
            pivot++;
            continue;
        }
        for (size_t i = pivot; i < row.size() - 1; i++)
        {
            row[i] = row[i + 1];
            row[i + 1] = 0;
        }
    }
    for (size_t curr = 0; curr < row.size() - 1; curr++)
    {
        if (row[curr] == 0)
            break;
        if (row[curr + 1] == row[curr])
        {
            row[curr] *= 2;
            score += row[curr];
            row[curr + 1] = 0;
            for (size_t i = curr + 1; i < row.size() - 1; i++)
                row[i] = row[i + 1];
        }
    }
}

int **Game::gridCopy()
{
    int **copy = new int*[size];
    for (int i = 0; i < size; i++)
    {
        copy[i] = new int[size];
        for (int j = 0; j < size; j++)
            copy[i][j] = grid[i][j];
    }
    return copy;
}

bool Game::gridEqual(int **other)
{
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            if (grid[i][j] != other[i][j])
                return false;
    return true;
}

void Game::gridDestroy(int **g)
{
    for (int i = 0; i < size; i++)
        delete []g[i];
    delete []g;
}
