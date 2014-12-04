#include <iostream>
#include <random>
#include <chrono>

using namespace std;

template<typename type>
    struct ugaw //uninitialized temporary generator and array wrapper
    {
        ugaw() {}

        ugaw(const ugaw&) = default;

        ugaw(const type & arg) { *this = *(const ugaw*)arg; } //data-only copy constructor (doesn't invoke any 'type' functions)

        & operator type() & {return d;} //cast operator for a reference to 'type' (used for arrays)

        & operator const type() const & {return d;} //cast operator for a const reference to 'type' (used for arrays)

        ugaw & operator =(const ugaw&) = default;

        ugaw & operator =(const type &arg) { *this = *(const ugaw*)arg; } //data-only assignment operator

        type *operator & () & { return &d; } //address operator to return the actual data stored

        const type *operator & () const & { return &d; } //and a constant version

        type d;
    };
    
using namespace std;

ugaw<size_t [10][10]> GenerateBoardRand();
    
int main()
{
    int var[4]{0, 1, 2, 3};

    int var1[4]{1, 1, 2, 3};

    auto &&refArray = FuncAdd(var, var1);

    for(size_t i(0); i < sizeof(var) / sizeof(var[0]); ++i)
        cout << var[i] << endl;

    cout << "Here" << endl;

    for(size_t i(0); i < sizeof(var1) / sizeof(var1[0]); ++i)
        cout << var1[i] << endl;

    cout << "Here" << endl;

    for(size_t i(0); i < sizeof(refArray) / sizeof(refArray[0]); ++i)
        cout << refArray[i] << endl;
    
    return 0;
}

inline bool bSetBoad(size_t x, size_t y, size_t (&refTable)[10][10], size_t nBoatSize);

ugaw<size_t [10][10]> GenerateBoardRand()
{
    size_t aTable[10][10] {};
    
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();

    default_random_engine generator (seed);

    uniform_int_distribution<size_t> distributionPos(0,9);

    while(!bSetBoad( distributionPos(generator), distributionPos(generator), aTable, 4));
    
    size_t i(0);
    
    while(i += bSetBoad( distributionPos(generator), distributionPos(generator), aTable, 3), i < 2);
    
    i = 0;
    
    while(i += bSetBoad( distributionPos(generator), distributionPos(generator), aTable, 2), i < 3);
    
    i = 0;
    
    while(i += bSetBoad( distributionPos(generator), distributionPos(generator), aTable, 1), i < 4);
}

bool bSetBoad(size_t x, size_t y, size_t (&refTable)[10][10], size_t nBoatSize)
{
    enum EN_DIRECTION {UP, DOWN, LEFT, RIGHT};
    
    const size_t yDimens(sizeof(refTable) / sizeof(refTable[0]));
    
    const size_t xDimens(sizeof(refTable[0]) / sizeof(refTable[0][0]));
    
    auto DoSomethingForRangInDir = [&] (EN_DIRECTION enWhere, auto enFunc, size_t nTimes, size_t X, size_t Y) 
{
        if(enWhere == LEFT)
    {
        if(!(X >= nTimes)) return false;

        for(size_t i(0); i < nTimes; ++i)
            if(enFunc(refTable[Y][i])) break;

        return true;
    }

    else if(enWhere == RIGHT)
    {
        if(!(X <= (xDimens - nTimes))) return false;

        for(size_t i(X); i < xDimens; ++i)
            if(enFunc(refTable[Y][i])) break;

        return true;
    }

    else if(enWhere == DOWN)
    {
        if(!(Y <= (yDimens - nTimes))) return false;

        for(size_t i(Y); i < yDimens; ++i)
            if(enFunc(refTable[i][X])) break;

        return true;
    }

    else if(enWhere == UP)
    {
        if(!(Y >= nTimes)) return false;

        for(size_t i(0); i < nTimes; ++i)
            if(enFunc(refTable[i][X])) break;

        return true;
    }
    
};

    bool bTmp = false;

    auto FuncHelper = [&] (size_t &arg){
                               if(arg == 2)
                               {
                                    bTmp = true;
                                    return true;
                               }
                               return false; };
                               
    size_t value;

    auto FuncHelper1 = [&] (size_t &arg){
                               arg = value;
                            };
                            
    if(DoSomethingForRangInDir(LEFT, FuncHelper, nBoadSize, x, y) && !bTmp)
    {
        value = 1;

        DoSomethingForRangInDir(LEFT, FuncHelper1, nBoadSize, x, y);

        value = 2;

        if(y) DoSomethingForRangInDir(LEFT, FuncHelper1, nBoadSize + 1 + (x < nBoadSize), x + 1, y - 1);

        DoSomethingForRangInDir(LEFT, FuncHelper1, nBoadSize + 1 + (x < nBoadSize), x + 1, y + 1);

        DoSomethingForRangInDir(LEFT, FuncHelper1, 1, x + 1, y);

        if(x >= nBoadSize) DoSomethingForRangInDir(LEFT, FuncHelper1, 1, x - nBoadSize, y);

        return true;
    }
    
    bTmp = false;

    if(DoSomethingForRangInDir(RIGHT, FuncHelper, nBoadSize, x, y) && !bTmp)
    {
        value = 1;

        DoSomethingForRangInDir(RIGHT, FuncHelper1, nBoadSize, x, y);

        value = 2;

        if(y) DoSomethingForRangInDir(RIGHT, FuncHelper1, nBoadSize + 1 + (bool)x, (x ? x - 1 : x), y - 1);

        DoSomethingForRangInDir(RIGHT, FuncHelper1, nBoadSize + 1 + (bool)x, (x ? x - 1 : x), y + 1);

        if(x) DoSomethingForRangInDir(RIGHT, FuncHelper1, 1, x - 1, y);

        DoSomethingForRangInDir(RIGHT, FuncHelper1, 1, x + nBoadSize, y);

        return true;
    }
    
    bTmp = false;

    if(DoSomethingForRangInDir(UP, FuncHelper, nBoadSize, x, y) && !bTmp)
    {
        value = 1;

        DoSomethingForRangInDir(UP, FuncHelper1, nBoadSize, x, y);

        value = 2;

        if(x) DoSomethingForRangInDir(UP, FuncHelper1, nBoadSize, x - 1, y + 1);

        DoSomethingForRangInDir(UP, FuncHelper1, nBoadSize, x + 1, y + 1);

        if(y >= nBoadSize) DoSomethingForRangInDir(UP, FuncHelper1, 1, x, y - nBoadSize);

        DoSomethingForRangInDir(UP, FuncHelper1, 1, x, y + 1);

        return true;
    }
    
    bTmp = false;
    
    if(DoSomethingForRangInDir(DOWN, FuncHelper, nBoadSize, x, y) && !bTmp)
    {
        value = 1;

        DoSomethingForRangInDir(DOWN, FuncHelper1, nBoadSize, x, y);

        value = 2;

        if(x) DoSomethingForRangInDir(DOWN, FuncHelper1, nBoadSize, x - 1, y);

        DoSomethingForRangInDir(DOWN, FuncHelper1, nBoadSize, x + 1, y);

        if(y) DoSomethingForRangInDir(DOWN, FuncHelper1, 1, x, y - 1);

        DoSomethingForRangInDir(DOWN, FuncHelper1, 1, x, y + nBoadSize);

        return true;
    }
    
    return false;
}