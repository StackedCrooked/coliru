#include <cstring>
#include <iostream>
#include <vector>
#include <memory>


template<class T>
class Grid
{
public:
    Grid(unsigned rows, unsigned columns, const T& t = T()) :
        data_(rows * columns, t),
        rows_(rows)
    {
    }
    
    unsigned rows() const
    {
        return rows_;
    }
    
    unsigned columns() const
    {
        return data_.size() / rows();
    }
    
    const T* operator[](unsigned row) const
    {
        return &data_[row * columns()];
    }
    
    T* operator[](unsigned row)
    {
        return &data_[row * columns()];
    }
    
    void set(unsigned row, unsigned column, const T & val)
    {
        data_[row * columns() + column] = val;
    }

private:
    friend std::ostream& operator<<(std::ostream& os, const Grid<T>& grid)
    {
        os << "Grid(" << grid.rows() << ", " << grid.columns() << "):\n";
        for (unsigned r = 0; r != grid.rows(); ++r)
        {
            os << "  ";
            for (unsigned c = 0; c != grid.columns(); ++c)
            {
                if (c != 0) os << ' ';
                const T& t = grid[r][c];
                os << t;
            }   
            os << '\n';
        }
        return os;
    }
    
    std::vector<T> data_;
    unsigned rows_;
};


int main()
{
    Grid<int> grid(2, 3);
    grid[0][0] = 1;
    grid[0][1] = 2;
    grid[0][2] = 3;
    grid[1][0] = 4;
    grid[1][1] = 5;
    grid[1][2] = 6;
    std::cout << grid << std::endl;
    
    std::cout << grid[0][0] << std::endl;
    std::cout << grid[0][1] << std::endl;
    std::cout << grid[0][2] << std::endl;
    
    
}
