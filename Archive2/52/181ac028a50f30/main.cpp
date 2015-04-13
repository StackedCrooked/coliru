#include <boost/thread.hpp>

static const int numThreads = 10;

struct W {
    W(...) {}

    void work() {
    }
};

int main()
{
    boost::thread_group tg;
    for (int i = 0; i < numThreads; i++) {
        W w = W("some", 42, "args");
        tg.create_thread(boost::bind(&W::work, &w));
    }

    tg.join_all();
}
