#include <iostream>

template <class, int>
class Tuple {

};

template <int T>
class Tuple <int, T> {
    public:
        Tuple(int x, int y) {
            std::cout << "arguments are: " << x << " and " << y;     
        }
};

int main()
{
    Tuple<int, 2> t1(8, 2);
}
