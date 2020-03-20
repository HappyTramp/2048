#include "expectimax.hpp"

Expectimax::Expectimax(Game *g)
{
    game = g;
}

Direction Expectimax::move()
{
    // algo(game->clone());
    return DIRECTION_UP;
}
