#include <type_traits>

template<typename Func, typename = typename std::result_of<Func()>::type>
void asdf(Func doThing)
{
    auto val = doThing();
}


int main()
{
    asdf([] {
        return 0;
    });
    
    // rejected
    asdf([](int) {});
}