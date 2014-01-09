#include <functional>

template<class T>
struct identity{ using type = T; };

template<class T>
void f1(T, std::function<void(T)>){}
template<class T>
void f2(T, typename identity<std::function<void(T)>>::type){}

void g(long){}

int main(){
    //f1(42, g); // error
    f2(42, g);
}