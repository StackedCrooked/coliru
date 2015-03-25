#include <valarray>
#include <cstdlib>

class Wine
{
private:
    struct Pair
    {
        std::valarray<int> valYear;
        std::valarray<int> valBottlesNum;
    };
    std::size_t m_yearNum;
    Pair m_numericData;
public:
    Wine();
    Wine(std::size_t, const int[], const int[]);
};

Wine::Wine(std::size_t yearNum, const int year[], const int bottlesNum[])
    : m_yearNum(yearNum)
    , m_numericData{{year, yearNum}, {bottlesNum, yearNum}}
{}

int main()
{}
