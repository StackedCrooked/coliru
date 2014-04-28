#include <boost/thread.hpp>

void plot(std::string msg)
{
    static boost::mutex mx;
    boost::lock_guard<boost::mutex> lk(mx);

    std::cout << msg << "\n";
}

class our_thread
{
    public:
        our_thread() : thread_object(0), thread_is_running(false) {}
        ~our_thread(){delete_thread();}

        void run(boost::thread*);
        void join(const char* = 0);
        inline bool is_running() const;

    private:
        void delete_thread();

        bool thread_is_running;
        boost::thread* thread_object;
};

void our_thread::run(boost::thread* t)
{
    this->delete_thread();
    this->thread_object = t; 
    this->thread_is_running = true;
    plot("in run");
}

void our_thread::join(const char* text)
{
    plot("in join");
    if(this->thread_object == 0) { return; }
    this->thread_is_running = false;
    if(text)
    {
        plot(text);
    }
    plot("progress.show(false);");
    this->thread_object->join();
    this->delete_thread();
}

void our_thread::delete_thread()
{
    this->thread_is_running = false;
    delete this->thread_object;
    this->thread_object = 0;
}

void function_name(std::string param1)
{
    plot("Enter function_name");
    plot(param1);
    boost::this_thread::sleep_for(boost::chrono::seconds(3));
    plot("Leave function_name");
}

int main()
{
    our_thread do_something_thread;
    do_something_thread.run(new boost::thread(&function_name, "param1"));
    // ...
    do_something_thread.join("Part creation finished");
}
