#ifndef RAND_AI_HPP
# define RAND_AI_HPP

#include "ai.hpp"
#include "game.hpp"

class RandAI : public AI
{
    public:
    RandAI(Game *g);
    Direction move();

    private:
    Game *game;
};

#endif
