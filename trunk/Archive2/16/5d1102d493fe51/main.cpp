#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/thread.hpp>
#include <iostream>

namespace ba = boost::asio;

struct TestIOService {

    void operation1();
    void operation2();
    TestIOService(std::string address) : address_(address) {
        socket_.connect(socket_.local_endpoint());
    }
    ~TestIOService() {
        work_.reset();
        if (th_.joinable())
            th_.join(); // perhaps timeout TODO
        service_.stop();
    }

  private:
    std::string address_;

    ba::io_service service_;
    boost::optional<ba::io_service::work> work_ { service_ };
    ba::strand strand_                          { service_ };
    ba::ip::udp::socket socket_                 { service_, { ba::ip::address::from_string(address_), 1234 } };
    boost::thread th_                           { boost::bind(&ba::io_service::run, &service_) };
    char receiveBuffer[100];

    void do_operation(char const* request, int len);
    void onDataRead(const boost::system::error_code &error, std::size_t bytes_transferred);
};

void TestIOService::onDataRead(const boost::system::error_code &error, std::size_t bytes_transferred) {
    if (!error) {
        std::cout << "onDataRead: " << bytes_transferred << " bytes '";
        std::cout.write(receiveBuffer, bytes_transferred) << "'\n";
    } else
    {
        std::cout << "onDataRead: " << error.message() << "\n";
    }
}

void TestIOService::do_operation(char const* request, int len) {
    using namespace ba;
    socket_.send(ba::buffer(request, len));

    socket_.async_receive(
            ba::buffer(receiveBuffer),
                strand_.wrap(
                    boost::bind(&TestIOService::onDataRead, this, ba::placeholders::error, ba::placeholders::bytes_transferred)
                ));
}

void TestIOService::operation1() {
    strand_.post([this] { do_operation("\x41\x5a", 2); });
    // c++03:
    // strand_.post(boost::bind(&TestIOService::do_operation, this, "\x42\x43", 2));
}

void TestIOService::operation2() {
    strand_.post([this] { do_operation("\x5a\x41", 2); });
    //strand_.post([this] { do_operation("\x40\x41", 2); });
}


int main() {
    TestIOService test1 {"127.0.0.1"};
    test1.operation1();
    boost::this_thread::sleep_for(boost::chrono::milliseconds(10));
    test1.operation2();
}
