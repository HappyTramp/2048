#ifndef GAME_HPP
# define GAME_HPP

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <vector>
#include <utility>
#include "2048.hpp"

class Game
{
    public:
    Game(int size);
    Game(Game const &other);
    Game &operator=(Game const &other);
    ~Game();
    int  getSize() const;
    int  getScore() const;
    int  get(int y, int x) const;
    bool move(Direction direction);
    void spawn();
    bool lost() const;

    private:
    int m_size;
    int m_score;
    int **m_grid;

    void mergeRow(std::vector<int> &row);
};

bool operator==(Game const &a, Game const &b);
bool operator!=(Game const &a, Game const &b);
std::ostream &operator<<(std::ostream &out, Game const &game);

#endif
