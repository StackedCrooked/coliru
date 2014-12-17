#include<boost/asio.hpp>
#include<iostream>
#include<boost/asio.hpp>
#include<boost/signals2.hpp>
#include<boost/thread.hpp>
#include<boost/make_shared.hpp>

static boost::asio::io_service svc;
static boost::shared_ptr<boost::asio::io_service::work> work_lock;

static boost::signals2::signal<void(std::string)> textEntered;

static void
handleInputText(std::string text)
{
    std::cout<<"handleInputText()"<<" text provided: "<<text;
    return;
}

static void 
worker()
{
    sleep(2);
    svc.post([](){
            std::cout<<"\nRaising signal.";
            std::string hello("hello world");
            textEntered(hello);
       });
    return;
}

int main()
{
    try
    {
        work_lock = boost::make_shared<boost::asio::io_service::work>(svc);
        textEntered.connect(&handleInputText);

        boost::thread_group tg;
        tg.create_thread(boost::bind(&boost::asio::io_service::run, &svc));
        tg.create_thread(&worker);

        boost::this_thread::sleep_for(boost::chrono::seconds(3));
        work_lock.reset();

        tg.join_all();
    }
    catch(std::exception &ex)
    {
        std::cerr<<"main() exited with exception:"<<ex.what();
    }
    return 0;
}
