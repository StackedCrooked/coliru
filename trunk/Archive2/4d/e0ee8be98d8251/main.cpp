
template<int N> struct X{};

int main()
{
    X<0>      x1; //ok
    X<int{}>  x2; //ok (same as X<0>)
    X<int()>  x3; //error  
}