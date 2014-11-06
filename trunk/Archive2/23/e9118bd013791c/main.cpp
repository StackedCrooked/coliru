#include <tuple>
#include <future>
#include <vector>
#include <stdio.h>

using namespace std;

template<typename Sequence>
struct when_any_result {
  size_t index;
  Sequence futures;
};

template <class... Futures>
future<when_any_result<future<tuple<decay_t<Futures>...>>>> when_any(Futures&&...)
{
    when_any_result<future<tuple<future<int>,future<char>>>> x;
    return async([&]{return move(x);});
    
}


int main(int argc, char const *argv[])
{
    future<int> f1;
    future<char> f2;
    auto any = when_any(f1,f2).get();

    if(any.index == 0) {
        future<int> ready = get<0>(any.futures.get());
    }
    else{
        //const future<char>& ready = get<1>(any.futures.get());
    }

    return 0;
}