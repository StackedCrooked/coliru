#include <iostream>

    

    #include <type_traits>
     
    class Root { };
     
    class Fixture
    {
    public:
        template <typename T,
                  typename = typename std::enable_if<std::is_same<T, Root>::value>::type>
        Fixture (T & root)
        : mRoot (root)
        { std::cout << "templated ctor" << std::endl; }
        Fixture(Fixture const& p)
        : mRoot(p.mRoot)
        { std::cout << "copy-ctor" << std::endl; }
    private:
        Root & mRoot;
    };
     
    class Branch : public Root, public Fixture
    {
    public:
        Branch() :  Fixture (*this) { }
    };
     
    int main()
    {
        Branch b;
    }

