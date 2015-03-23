#include <iostream>
#include <boost/asio.hpp>
#include <boost/asio/spawn.hpp>
#include <boost/asio/system_timer.hpp>
#include <chrono>

using namespace std;

int main()
{
    boost::asio::io_service io_service;
    boost::asio::spawn(io_service,
                       [&io_service](boost::asio::yield_context yield){
        boost::asio::spawn(yield, [&io_service](boost::asio::yield_context yield){
            boost::asio::system_timer timer(io_service);
            timer.expires_from_now(std::chrono::seconds(1));
            timer.async_wait(yield);
            cout << "Sleep 1 second" << endl;
        });

        boost::asio::system_timer timer(io_service);
        timer.expires_from_now(std::chrono::seconds(2));
        timer.async_wait(yield);
        cout << "Sleep 2 second" << endl;
    });
    io_service.run();
    cout << "Done" << endl;
    return 0;
}