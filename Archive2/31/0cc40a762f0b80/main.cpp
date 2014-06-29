void f(int) = delete;
template<class T> void f(T){}

template<class T>
auto g(T v) -> decltype(f(v)){}

int main(){
    g(3.14);
    g(42);
}