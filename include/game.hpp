#ifndef GAME_HPP
# define GAME_HPP

#include <cstdlib>
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
};

#endif
