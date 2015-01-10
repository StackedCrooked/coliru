class VeryPrivateClass {
    int protectedVar;
public:
    VeryPrivateClass() {};

    template<typename T>
    int someFeature()
    {
        return 1;
    }

};

class A;

template<>
int VeryPrivateClass::someFeature<A>()
{
    protectedVar = 10;
    return 0;
}

int main()
{
    VeryPrivateClass c1;
    c1.someFeature<A>();
}