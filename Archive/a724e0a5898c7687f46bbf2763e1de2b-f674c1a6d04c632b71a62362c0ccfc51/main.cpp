#include <cstring>
#include <vector>
#include <memory>



/**
 * GenericGrid represents a grid or table structure.
 */
template<class T>
class GenericGrid
{
public:
    GenericGrid(std::size_t inRowCount, std::size_t inColumnCount) :
        mData(inRowCount * inColumnCount),
        mRowCount(inRowCount),
        mColumnCount(inColumnCount)
    {
    }
    
    GenericGrid(std::size_t inRowCount, std::size_t inColumnCount, const T & inInitialValue) :
        mData(inRowCount * inColumnCount, inInitialValue),
        mRowCount(inRowCount),
        mColumnCount(inColumnCount)
    {
    }
    
    std::size_t rowCount() const
    {
        return mRowCount;
    }
    
    std::size_t columnCount() const
    {
        return mColumnCount;
    }
    
    const T & get(std::size_t inRow, std::size_t inColumn) const
    {
        return mData[inRow * mColumnCount + inColumn];
    }
    
    void set(std::size_t inRow, std::size_t inColumn, const T & inValue)
    {
        mData[inRow * mColumnCount + inColumn] = inValue;
    }

private:
    typedef std::vector<T> Data;
    Data mData;
    std::size_t mRowCount;
    std::size_t mColumnCount;
};


int main()
{
    GenericGrid<std::string> grid(10, 10);
    grid.set(1, 2, "Hello");
    grid.get(1, 1);
}