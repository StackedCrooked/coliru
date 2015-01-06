#include <iostream>
#include <string>
#include <vector>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

//Constructor chaining;
class dirtyBigObject
{
    public:
        //
        dirtyBigObject(int data, bool validity, double score) : mData(data), mValid(validity), mScore(score) { printData();};
        dirtyBigObject(int data, bool validity) : dirtyBigObject(data, validity, 3.14) {};
        dirtyBigObject(int data) : dirtyBigObject(data, true) {}
        dirtyBigObject() : dirtyBigObject(0) {};
        
        void printData() { std::cout << mData << " " << mValid << " " << mScore << std::endl;}
    private:
        int    mData;
        bool   mValid;
        double mScore;
};

int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
    
    dirtyBigObject x1(9, false, 7.3);
    dirtyBigObject x2(9, false);
    dirtyBigObject x3(9);
    dirtyBigObject x4();
    
    //This works with the initializer list aka uniform initialization: type name{variables}, here constructor variables;
    dirtyBigObject x5{11, false};
}
