#include <boost/asio.hpp>
#include <iostream>
#include <thread>

int main() {
    boost::asio::io_service svc;
    boost::asio::deadline_timer timer(svc, boost::posix_time::seconds(2));
    timer.async_wait([](boost::system::error_code ec) { std::cout << ec.message() << '\n'; });

    std::thread th([&] { svc.run(); });

    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "first\n";
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "bye\n";
    
    th.join();
}

