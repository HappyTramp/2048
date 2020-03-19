#ifndef GAME_HPP
# define GAME_HPP

#include <cstdlib>
#include <vector>
#include <utility>
#include "2048.hpp"

class Game
{
    public:
    Game(int s);
    ~Game();
    int getSize();
    int at(int x, int y);
    void move(Direction direction);
    void spawn();
    bool lost();

    private:
    int size;
    int **grid;
    void mergeRow(std::vector<int> &row);
    int **gridCopy();
    bool gridEqual(int **other);
    void gridDestroy(int **g);
};

#endif
