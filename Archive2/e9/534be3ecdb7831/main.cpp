#define BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
#define BOOST_THREAD_PROVIDES_FUTURE
#include <boost/thread/future.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>

using boost::async;
using boost::future;

int main() {
    boost::function<int(int)> foo = [](int i) { return i*2; };

    auto consequence = async(boost::bind(foo, 42))
        .then([&](future<int> j) { return j.get()-4; })
        .then([&](future<int> k) { return k.get()/2; })
        .then([&](future<int> l) { return l.get()+2; });

    return consequence.get();
}
