#include <boost/asio.hpp>
#include <boost/make_shared.hpp>
#include <boost/bind/bind.hpp>
#include <boost/array.hpp>
#include <boost/asio/placeholders.hpp>
#include <iostream>

class TestIOService {

public:
    void makeConnection();
    void onDataRead(const boost::system::error_code &error, std::size_t bytes_transferred, char *data);
    void operation1();
    void operation2();
    TestIOService(std::string address);
    

private:
    std::string address;

    boost::shared_ptr<boost::asio::ip::udp::socket> socket;
    boost::shared_ptr<boost::asio::io_service> service;
};

void TestIOService::makeConnection() {
    using namespace boost::asio;
    service = boost::make_shared<io_service>();
    socket  = boost::make_shared<ip::udp::socket>(*service);
    socket->connect({ip::address::from_string("192.168.1.2"), 1234 });
}


void TestIOService::onDataRead(const boost::system::error_code &error, std::size_t bytes_transferred, char *data) {
    std::cout << "onDataRead";          
}


void TestIOService::operation1() {
    using namespace boost::asio;
    //make some send request
    boost::array<uint8_t, 2> sendBuffer = {{ 0x01, 0x02}};

    socket->send(boost::asio::buffer(sendBuffer));
    char receiveBuffer[100];
    socket->async_receive(boost::asio::buffer(receiveBuffer), boost::bind(&TestIOService::onDataRead,
                                                                          this, boost::asio::placeholders::error,
                                                                          boost::asio::placeholders::bytes_transferred,
                                                                          receiveBuffer));
    service->run();

}

void TestIOService::operation2() {
    using namespace boost::asio;
    //make some send request
    boost::array<uint8_t, 2> sendBuffer = {{ 0x00, 0x01}};

    socket->send(boost::asio::buffer(sendBuffer));
    char receiveBuffer[100];
    socket->async_receive(boost::asio::buffer(receiveBuffer), boost::bind(&TestIOService::onDataRead,
                                                                          this, boost::asio::placeholders::error,
                                                                          boost::asio::placeholders::bytes_transferred,
                                                                          receiveBuffer));
    service->run();

}

TestIOService::TestIOService(std::string address) 
    : address(address) { }


int main() {
    auto test1 = TestIOService("192.168.1.2");
    test1.makeConnection();
    test1.operation1();
    test1.operation2();
}
