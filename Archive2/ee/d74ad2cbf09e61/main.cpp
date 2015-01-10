class VeryPrivateClass {
    int protectedVar;
public:
    VeryPrivateClass() {};

    template<typename T>
    int someFeature()
    {
        // Do useful work and return value
        return 1;
    }

};

class A;

template<>
int VeryPrivateClass::someFeature<A>()
{
    // Change the private variable outside the class
    protectedVar = -1;
}

int main()
{
    VeryPrivateClass c1;
    c1.someFeature<A>();
}