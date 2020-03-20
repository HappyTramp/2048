#ifndef EXPECTIMAX_HPP
# define EXPECTIMAX_HPP

#include "2048.hpp"
#include "game.hpp"

class Expectimax
{
    public:
    Expectimax(Game *g);
    Direction move();

    private:
    Game *game;
};

#endif
