class Base {};

template <int x> class Grandpa: public Base {};

template <int x> 
class Father: public Grandpa<x> {};

int main()
{
    Father<3> f;
}