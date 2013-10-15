struct X{
    template<class T>
    auto operator[](T){ return 42; }
};

int main(){
    X x;
    x[0] + 42;
}