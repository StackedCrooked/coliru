#include <boost/thread.hpp>

struct StreamX
{
    StreamX() { puts(__FUNCTION__); }
   ~StreamX() { puts(__FUNCTION__); }
};

static boost::thread_specific_ptr<StreamX> StreamThreadSpecificPtr;

void thread_proc() {
    StreamX* stream = NULL;
    stream = StreamThreadSpecificPtr.get();
    if (NULL == stream) {
        stream = new StreamX();
        StreamThreadSpecificPtr.reset(stream);
    }
    printf("%p\n", stream);
}

int main() {
    boost::thread_group threads;
    for(int i = 0; i < 5; i ++)
        threads.create_thread(&thread_proc);

    threads.join_all();
}
