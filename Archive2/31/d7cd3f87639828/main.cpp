#include <boost/thread.hpp>
#include <boost/asio.hpp>

struct Wrapcontainer {
    int id = id_gen();
  private:
    static int id_gen() {
        static int seed = 0;
        return ++seed;
    }
};

class ThreadAsioPool {
  public:
    ThreadAsioPool(const std::size_t nb_threads);
    virtual ~ThreadAsioPool() { CancelAll(); }

    void CancelAll();
    void AddJob(Wrapcontainer &wrap);

  protected:
    static void job(Wrapcontainer wrap);
    void AddThread() { m_threadgroup.create_thread(boost::bind(&boost::asio::io_service::run, &io)); }

  private:
    std::size_t nbThreads;
    boost::asio::io_service io;
    boost::thread_group m_threadgroup;
    boost::optional<boost::asio::io_service::work> work;
};

ThreadAsioPool::ThreadAsioPool(const std::size_t nb_threads) 
    : nbThreads(nb_threads), io(), 
      work(boost::asio::io_service::work(io))
{
    for (std::size_t i = 0; i < nbThreads; ++i)
        AddThread();
}

void ThreadAsioPool::AddJob(Wrapcontainer &wrap) {
    // after a CancelAll, the m_threadgroup would be empty, so add more thread if needed
    if (m_threadgroup.size() < nbThreads)
        AddThread();

    io.post(boost::bind(&ThreadAsioPool::job, wrap));
}

void ThreadAsioPool::CancelAll() {
    try {
        work.reset();
        io.stop(); // not sure that's necessary to stop the queue from processing
        m_threadgroup.interrupt_all(); // this to empty the queue
        m_threadgroup.join_all(); // I assume after this line that the m_threadgroup is empty
    } catch (boost::thread_interrupted const &e) {
        std::cout << "CAUGHT " + std::to_string(__LINE__) << "\n";
    } catch (std::exception const &e) {
        std::cout << "CAUGHT" + std::to_string(__LINE__) << "\n";
    } catch (...) {
        std::cout << "CAUGHT " + std::to_string(__LINE__) << "\n";
    }
}
void ThreadAsioPool::job(Wrapcontainer wrap) {
    try {
        boost::this_thread::interruption_point();
        boost::this_thread::interruption_point(); // inserting few interruption point between heavy task
        boost::this_thread::sleep(boost::posix_time::milliseconds(50)); // different type of breakpoint see if it makes a difference
        boost::this_thread::interruption_point();
        std::cout << "Job " << wrap.id << " done " + std::to_string(__LINE__) << "\n";
    } // try
    catch (boost::thread_interrupted &e) {
        std::cout << "CAUGHT " + std::to_string(__LINE__) << "\n";
    } catch (std::exception const &e) {
        std::cout << "CAUGHT " + std::to_string(__LINE__) << "\n";
    } catch (...) {
        std::cout << "CAUGHT " + std::to_string(__LINE__) << "\n";
    }
}

int main() {
    ThreadAsioPool threadpool(3);

    // add 50 jobs in the queue
    for (int i = 0; i < 50; i++) {
        Wrapcontainer itemdata; // just a class to contain data for the job
        //... fill up 'itemdata' with required data for the job
        threadpool.AddJob(itemdata);//feed a job
    }
    std::cout << "Canceling\n";

    threadpool.CancelAll();
}
