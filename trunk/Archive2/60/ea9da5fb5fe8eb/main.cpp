template <typename T, int... dims>
void f(T (&...arr)[dims]);

template<class T> class TD;
TD<decltype(f<int, 2, 3, 4>)> t;

int main(){
}