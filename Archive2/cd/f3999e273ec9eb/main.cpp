#include <iostream>
#include <cstdio>

using namespace std;

template <bool b1, bool b2>
struct HeavyLoopImpl
{
    static int func(int arg)
    {
        cout << "b1=" << b1 << " b2=" << b2 << endl;
        for (int i = 0; i < 10000000; i++) {
            arg += b1 ? 1 : 2;
            arg += b2 ? 10 : 20;
        }
        return arg;
    }
};

template <template<bool...> class Impl, bool...Bs>
struct GenericJump
{
    template<typename... Args>
    static int impl(Args&&... args)
    {
        return Impl<Bs...>::func(std::forward<Args>(args)...);
    }

    template<typename... Args>
    static int impl(bool b, Args&&... args)
    {
        //  Pull b off the front, and stick it on the end
        return b
            ? GenericJump<Impl,Bs...,true >::impl(std::forward<Args>(args)...)
            : GenericJump<Impl,Bs...,false>::impl(std::forward<Args>(args)...);
    }
};

int HeavyLoop(bool b1, bool b2, int arg)
{
    return GenericJump<HeavyLoopImpl>::impl(b1,b2,arg);
}

int main()
{
    bool b1 = true;
    bool b2 = false;
    int arg = 0;
    int res = HeavyLoop(b1, b2, arg);
    cout << "res: "<<res<<endl;
    return 0;
}