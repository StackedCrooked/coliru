template <typename F>
class MyTemplate {
public:
    void SomeMethod(F f) {
        //...
    }

    template <typename C, typename O>
    void SomeMethod(F C::* f, O& o) {    // this does not work, it want a member function pointer here
        //...
    }
};

void StaticFunction(int) {}

struct SomeClass {
public:
    void MemberMethod(int) {}
};

int main()
{
MyTemplate<void(int)> mt;
mt.SomeMethod(StaticFunction);
SomeClass SomeClassInstance;
mt.SomeMethod(&SomeClass::MemberMethod, SomeClassInstance); // I want to call it like this
}