#include <iostream>
#include <future>

using namespace std;

template<typename Cont, typename Accum, typename F>
    Accum accumulate(Cont const& cont, Accum&& init, F func)
{
    auto f(begin(cont)), l(end(cont));
    for(;f!=l;++f)
        init = func(std::forward<Accum>(init), *f);
    return std::move(init);
}

int main()
{
    accumulate("hello world", async([]{}), [](future<void>&& before, char ch) { 
            return async([](future<void>&& before, char ch) { before.get(); cout << ch; }, move(before), ch); }
        ).get();
}
