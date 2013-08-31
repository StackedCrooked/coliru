struct X{
    template<class T, class U>
    X(T, U){}
};

int main()
{
    X x{1,2};
}
