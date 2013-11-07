template<class T>
struct X{
    X(){}
    X(int){}
};

template<class T>
void foo(T, X<T>){}

int main(){
    foo(42, {});
}