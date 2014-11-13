#include <vector>

template <typename T, typename... MyBases> class SmartAlias :  public MyBases... {
public:
    typedef std::vector<T> Shared;
};

class Base : public SmartAlias<Base>
{
};

class Derived : public SmartAlias<Derived, Base>
{
};

class MiniBase : public SmartAlias<MiniBase> {};

class MiniDerived : public SmartAlias<MiniDerived, MiniBase, Derived> { 
public: 
    MiniDerived(); 
};
 
int main() {
    Base::Shared base;
    Derived::Shared derived; 
    MiniDerived::Shared md;
}
