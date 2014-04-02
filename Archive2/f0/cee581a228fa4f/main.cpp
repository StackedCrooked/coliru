#include <boost/thread.hpp>

static const int ITERATIONS = 3;
static const int NUM_WORKERS = 12;

boost::barrier rendez_vous(NUM_WORKERS + 1); // logical join point, expecting 3 threads to meet-up

void coordinator()
{
    for (int i = 0; i < ITERATIONS; ++i)
    {
        rendez_vous.wait();
        std::cout << "Rendez-vous " << i << "\n";
    }
}

void worker()
{
    for (int i = 0; i < ITERATIONS; ++i)
    {
        boost::this_thread::sleep_for(boost::chrono::milliseconds(rand() % 1000));
        rendez_vous.wait();
    }
}

int main()
{
    boost::thread_group g;
    g.create_thread(coordinator);
    for (int i = 0; i < NUM_WORKERS; ++i)
        g.create_thread(worker);

    g.join_all();
}
