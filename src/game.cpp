#include "game.hpp"


Game::Game(int m_size): m_size(m_size), m_score(0)
{
    m_grid = new int*[m_size];
    for (int i = 0; i < m_size; i++)
    {
        m_grid[i] = new int[m_size];
        for (int j = 0; j < m_size; j++)
            m_grid[i][j] = 0;
    }
    spawn();
    spawn();
}

Game::Game(Game const &other): m_size(other.m_size), m_score(other.m_score)
{
    m_grid = new int*[m_size];
    for (int i = 0; i < m_size; i++)
    {
        m_grid[i] = new int[m_size];
        for (int j = 0; j < m_size; j++)
            m_grid[i][j] = other.get(i, j);
    }
}

Game::~Game()
{
    for (int i = 0; i < m_size; i++)
        delete []m_grid[i];
    delete []m_grid;
}

int Game::getSize() const
{
    return m_size;
}

int Game::getScore() const
{
    return m_score;
}

int Game::get(int y, int x) const
{
    return m_grid[y][x];
}

bool Game::move(Direction direction)
{
    std::vector<int> row;
    Game saved(*this);

    switch (direction)
    {
        case DIRECTION_LEFT:
            for (int i = 0; i < m_size; i++)
            {
                row.clear();
                for (int j = 0; j < m_size; j++)
                    row.push_back(m_grid[i][j]);
                mergeRow(row);
                for (int j = 0; j < m_size; j++)
                    m_grid[i][j] = row[j];
            }
            break;
        case DIRECTION_RIGHT:
            for (int i = 0; i < m_size; i++)
            {
                row.clear();
                for (int j = m_size - 1; j >= 0; j--)
                    row.push_back(m_grid[i][j]);
                mergeRow(row);
                for (int j = m_size - 1; j >= 0; j--)
                    m_grid[i][j] = row[m_size - j - 1];
            }
            break;
        case DIRECTION_DOWN:
            for (int j = 0; j < m_size; j++)
            {
                row.clear();
                for (int i = m_size - 1; i >= 0; i--)
                    row.push_back(m_grid[i][j]);
                mergeRow(row);
                for (int i = m_size - 1; i >= 0; i--)
                    m_grid[i][j] = row[m_size - i - 1];
            }
            break;
        case DIRECTION_UP:
            for (int j = 0; j < m_size; j++)
            {
                row.clear();
                for (int i = 0; i < m_size; i++)
                    row.push_back(m_grid[i][j]);
                mergeRow(row);
                for (int i = 0; i < m_size; i++)
                    m_grid[i][j] = row[i];
            }
            break;
    }
    if (*this != saved)
        spawn();
    else
        return false;
    return true;
}

void Game::spawn()
{
    std::vector< std::pair<int, int> > possible;

    if (lost())
        return;
    for (int i = 0; i < m_size; i++)
        for (int j = 0; j < m_size; j++)
        {
            if (m_grid[i][j] == 0)
                possible.push_back(std::make_pair(i, j));
        }
    if (possible.size() < 1)
        return;
    std::pair<int, int> pos = possible[rand() % possible.size()];
    m_grid[pos.first][pos.second] = rand() % 10 == 0 ? 4 : 2;
}

bool Game::lost() const
{
    for (int i = 0; i < m_size; i++)
        for (int j = 0; j < m_size; j++)
        {
            if (m_grid[i][j] == 0)
                return false;
            if (i - 1 >= 0 && m_grid[i - 1][j] == m_grid[i][j])
                return false;
            if (i + 1 < m_size && m_grid[i + 1][j] == m_grid[i][j])
                return false;
            if (j - 1 >= 0 && m_grid[i][j - 1] == m_grid[i][j])
                return false;
            if (j + 1 < m_size && m_grid[i][j + 1] == m_grid[i][j])
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
            m_score += row[curr];
            row[curr + 1] = 0;
            for (size_t i = curr + 1; i < row.size() - 1; i++)
                row[i] = row[i + 1];
        }
    }
}

Game &Game::operator=(Game const &other)
{
    if (this == &other)
        return *this;
    for (int i = 0; i < m_size; i++)
        delete []m_grid[i];
    delete []m_grid;
    m_size = other.m_size;
    m_score = other.m_score;
    m_grid = new int*[m_size];
    for (int i = 0; i < m_size; i++)
    {
        m_grid[i] = new int[m_size];
        for (int j = 0; j < m_size; j++)
            m_grid[i][j] = other.m_grid[i][j];
    }
    return *this;
}

bool operator==(Game const &a, Game const &b)
{
    if (a.getSize() != b.getSize())
        return false;
    for (int i = 0; i < a.getSize(); i++)
        for (int j = 0; j < a.getSize(); j++)
            if (a.get(i, j) != b.get(i, j))
                return false;
    return true;
}

bool operator!=(Game const &a, Game const &b)
{
    return !(a == b);
}

std::ostream &operator<<(std::ostream &out, Game const &game)
{
    out << "score: " << game.getScore() << std::endl;
    for (int i = 0; i < game.getSize(); i++)
    {
        for (int j = 0; j < game.getSize(); j++)
            out << std::setw(5) << game.get(i, j) << " ";
        out << std::endl;
    }
    return out;
}
