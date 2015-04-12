#include <stdexcept>

//SqrtofZeroException objects are thrown by functions that detect attempts to square root negative numbers
class SqrtofZeroException : public std::runtime_error
{
public:
    SqrtofZeroException() //constructor specifies default error message
        : runtime_error("square root on a negative number is not allowed"){}
}; //end class SqrtofZeroException

#include <iostream>
#include <cmath>
using namespace std;

template <typename T>
T sqrtNumber(T&);

int main()
{
    int a, result;
    cout << "Enter number to square root: ";
    while (cin >> a){
        try{
            result = sqrtNumber(a);
            cout << "The square root of " << a << " is " << result << endl;
        } //end try
        catch (SqrtofZeroException &sqrtEx){
            cerr << "An exception occurred: " << sqrtEx.what() << endl;
        } //end catch
    }
    return 0;
}

template <typename T>
T sqrtNumber(T& num)
{
    if (num < 0)
        throw SqrtofZeroException();

    return sqrt(num);
}