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
    
    const T& get(unsigned row, unsigned column) const
    {
        return data_[row * columns() + column];
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
            for (unsigned c = 0; c != grid.columns(); ++c)
            {
                os << '\t' << grid.get(r, c) << ' ';
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
    Grid<int> grid(2, 2);
    grid.set(0, 0, 1);
    grid.set(0, 1, 2);
    grid.set(1, 0, 3);
    grid.set(1, 1, 4);    
    std::cout << grid << std::endl;
}
