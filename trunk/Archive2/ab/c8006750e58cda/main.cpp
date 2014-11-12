
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <thread>

/*singleton function for thread queue*/
struct thread_source
{
    thread_source()
    :
    work_(new boost::asio::io_service::work(ios_) ),
    strand_(ios_)
    {
        
    }

    static void create(){
        instance_ = new thread_source;
        instance_->ios_thread = std::thread(boost::bind(&boost::asio::io_service::run, &instance_->ios_));
    }

    //static void run(){
    //    if (instance_ != nullptr)
    //        instance_->ios_thread = std::thread(boost::bind(&boost::asio::io_service::run, &instance_->ios_));
    //}

    static void stop()
    {
        if (instance_ != nullptr){
            if (instance_->work_ != nullptr){
                delete instance_->work_;
                instance_->work_ = nullptr;
            }
            instance_->ios_thread.join();
        }
    }

    static void clear(){
        /*stop service and clear*/
        stop();
        if (instance_ != nullptr){
            delete instance_;
            instance_ = nullptr;
        }
    }

    template<typename HandlerType>
    static void start_thread(HandlerType handler)
    {
        std::shared_ptr<std::thread> thr(new std::thread(handler));
        instance_->threads[thr->get_id()] = thr;
    }

    void kill_thread(std::thread::id id)
    {
        instance_->strand_.post(boost::bind(&thread_source::kill_thread_handling, instance_, id));
    }

    

private:

    void kill_thread_handling(std::thread::id id)
    {
        threads[id]->join();
        size_t num = threads.erase(id);
        assert(num == 1);
        std::cerr << "killing thread by id: " << id << std::endl;
    }

private:
    static thread_source* instance_;
    std::map<std::thread::id, std::shared_ptr<std::thread> > threads;


   
    /*for thread handling*/
    boost::asio::io_service       ios_;
    boost::asio::io_service::work* work_;
    boost::asio::strand           strand_;
    std::thread                   ios_thread;
};

thread_source* thread_source::instance_ = nullptr;


struct message_class : virtual thread_source
{
    void handler(std::string message)
    {
        std::cout << message << std::endl;
        kill_thread(std::this_thread::get_id());
    }
};

int main(int argc, char* argv[])
{
    thread_source::create();
    message_class message_;
    std::string mes[] = { "Hello,\n", "world" };
    thread_source::start_thread(std::bind(&message_class::handler, &message_, mes[0]));
    thread_source::start_thread(std::bind(&message_class::handler, &message_, mes[1]));
    /*let strand kill threads before deletion*/
    boost::this_thread::sleep(boost::posix_time::milliseconds(1));
    thread_source::clear();
    return 0;
}

