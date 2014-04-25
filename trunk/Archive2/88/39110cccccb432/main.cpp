#include <boost/thread.hpp>
#include <boost/make_shared.hpp>
#include <cassert>
using namespace boost;

using shared_thread = shared_ptr<thread>;

struct request {
    int i;
    std::string message;
};

static mutex mx;

void process_request(request req, shared_thread th)
{
    assert(th->get_id() == this_thread::get_id());
    th->detach();

    lock_guard<mutex> lk(mx);
    std::cout << "processing request " << req.i << ": '" << req.message << "'\n";
}

int main()
{
    for(int i=0; i<10; ++i)
    {
        shared_thread th = make_shared<thread>();

        *th = thread(&process_request, request { i, "some message" }, th);
    }

    this_thread::sleep_for(chrono::seconds(1));
}
