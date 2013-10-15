template<class> struct X{};

namespace N{
    struct Y{};
    template<class T> void fun(T){}
};

int main(){
    X<X<X<X<X<N::Y>>>>> x5;
    fun(x5);
}