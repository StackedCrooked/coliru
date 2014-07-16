#ifndef TESTCLASS_HPP_
#define TESTCLASS_HPP_
#include "boost/asio.hpp"
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <iostream>

class TestClass : public boost::asio::ip::tcp::socket{
public:
    TestClass(boost::asio::io_service& ios) : boost::asio::ip::tcp::socket(ios) {
    }
    virtual ~TestClass() {};

    template <typename ConnectHandler>
    void async_connect(const endpoint_type& peer_endpoint, ConnectHandler handler) {

            boost::asio::ip::tcp::socket::async_connect(peer_endpoint,
                    boost::bind(&TestClass::handle_connect, this, boost::asio::placeholders::error, boost::bind(&TestClass::foo, this)));
    }
private:
    void handle_connect(const boost::system::error_code& err, boost::function<void (void)> func) {
        std::cout<<"handle_connect started"<<std::endl;
        func();
    }

    void foo(){
        std::cout<<"foo started" << std::endl;
    }

};

#endif /* TESTCLASS_HPP_ */

int main()
{
    boost::asio::io_service ios;
    TestClass t(ios);
}
