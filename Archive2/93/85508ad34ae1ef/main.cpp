#include <iostream>
using namespace std;

template <typename T>
class sparseArray2D
{
private:
    //...
public:
    //...
    friend ostream& operator << (ostream&, const sparseArray2D<T>&);
    //...
};

template<typename T>
ostream& operator << (ostream& os, const sparseArray2D<T> &_matrix)
{
//...
    os<<"Overloaded operator works";
    return os;
};

int main()
{
    //...
    sparseArray2D<int> matrX;
    cout << matrX;
    //...
}