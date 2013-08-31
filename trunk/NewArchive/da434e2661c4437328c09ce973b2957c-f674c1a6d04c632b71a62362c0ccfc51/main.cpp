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
    
    // returns a pointer to the beginning of the row
    const T* operator[](unsigned row) const
    {
        return data_.data() + row * columns();
    }
    
    // returns a pointer to the beginning of the row
    T* operator[](unsigned row)
    {
        return data_.data() + row * columns();
    }

private:
    std::vector<T> data_;
    unsigned rows_;
};


int main()
{
    Grid<int> grid(2, 2);
    grid[0][0] = 1;
    grid[0][1] = 2;
    grid[1][0] = 3;
    grid[1][1] = 4;
    std::cout << grid[1][0] << std::endl;
}
