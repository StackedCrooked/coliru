#include <initializer_list>

template<class T, int N, int M>
struct X{
    X(std::initializer_list<std::initializer_list<T>>){}
private:
    T arr[N][M];
};

int main(){
    X<int, 3, 4> x = {{1, 2}, {3, 4}, {5, 6}};
}