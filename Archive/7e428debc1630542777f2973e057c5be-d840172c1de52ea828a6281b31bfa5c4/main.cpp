#include <iostream>
#include <algorithm>
using namespace std;
 
template<typename T, size_t N>
class Data
{
private:
    template<typename U, size_t M> friend class Data;
    T data[N];
   
public:
    // default constructor
    Data() : data() {}
    
    // template constructor from source
    template<size_t M>
    Data(const Data<T,M>& arg) : data()
    {
        // ERROR: can't access Data<T,M>::data
        std::copy_n(std::begin(arg.data), std::min(N,M), std::begin(data));
    }
 
    template<size_t M>
    Data& operator =(const Data<T,M>& arg)
    {
        // same issue
        std::copy_n(arg.data, std::min(N,M), data);
        return *this;
    }
};
 
int main()
{
    Data<char,10> x1;
    Data<char,12> x2 = x1;
    return 0;
}