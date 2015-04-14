#include <boost/asio.hpp>
#include <boost/make_shared.hpp>
#include <iostream>

class TestIOService {

public:
    void makeConnection();
    static TestIOService getInst();

private:
    TestIOService(std::string address);
    std::string address;

    boost::shared_ptr<boost::asio::ip::udp::socket> socket;
    boost::shared_ptr<boost::asio::io_service> service;
};

void TestIOService::makeConnection() {
    using namespace boost::asio;
    service = boost::make_shared<io_service>();
    socket  = boost::make_shared<ip::udp::socket>(*service);
    socket->connect({ip::address::from_string("192.168.1.2"), 1234 });
    //socket->close();
}

TestIOService::TestIOService(std::string address) 
    : address(address) { }

TestIOService TestIOService::getInst() {
    return TestIOService("192.168.1.2");
}

int main() {
    auto test1 = TestIOService::getInst();
    auto test2 = TestIOService::getInst();
}
