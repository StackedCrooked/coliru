#include <iostream>

using namespace std;

template <class T>
T max(T& t1, T& t2)
{
  return t1 < t2 ? t2 : t1;
}

int main(int argc, char* argv[])
{
    cout << "max of 33 and 44 is: " << max(33,44) << endl;
    return 0;
}