#include "rand_ai.hpp"

RandAI::RandAI(Game *g)
{
    game = g;
}

Direction RandAI::move()
{
    Direction directions[4] = {DIRECTION_LEFT, DIRECTION_RIGHT,
                               DIRECTION_DOWN, DIRECTION_UP};
    return directions[rand() % 4];
}
