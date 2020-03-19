#ifndef AI_HPP
# define AI_HPP

#include "2048.hpp"
#include "game.hpp"

class AI
{
    public:
    // AI(Game *g);
    virtual Direction move() = 0;

    private:
    Game *game;
};

#endif
