#include <boost/thread.hpp>

struct Hello
{
    void run();
    bool canRun() { return true; }
    boost::condition_variable cond;
    boost::mutex mut;
};

void Hello::run()
{
    boost::unique_lock<boost::mutex> lock(this->mut);
    cond.wait(lock, boost::bind(&Hello::canRun, this));
    
    std::cout << "Done";
}

int main()
{
    Hello obj;
    boost::thread th(&Hello::run, &obj);

    boost::this_thread::sleep_for(boost::chrono::milliseconds(100));

    {
        boost::lock_guard<boost::mutex> lk(obj.mut);
        obj.cond.notify_one();
    }

    th.join(); 
}
