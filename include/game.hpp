#ifndef GAME_HPP
# define GAME_HPP

class Game
{
    public:
    Game(int s);
    ~Game();
    int getSize();
    int at(int x, int y);

    private:
    int size;
    int **grid;
};

#endif
