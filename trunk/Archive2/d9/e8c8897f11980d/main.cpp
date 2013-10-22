#include <iostream>

using namespace std;


template <typename T>
int SendData( const T& tDataBuffer )
{
    cout << boolalpha << __has_trivial_copy(T);

    static_assert(
        __has_trivial_copy(T),
        "The object type must be trivially copyable" );

    return 0;
}

int main()
{
    const int iArray[2] = {1, 2};
    int iResult = SendData( iArray );

}