#include <boost/asio.hpp>

class server
{
    public:
        server();

        void run();

    private:
        bool start_listen();
        void start_accept();
        void handle_accept(boost::system::error_code e);

        boost::asio::io_service ios;
        boost::asio::ip::tcp::acceptor acceptor_;
        std::vector<boost::asio::ip::tcp::socket*> sockets;
};

#include <boost/bind.hpp>

server::server(): acceptor_(ios)
{
    start_listen();
    start_accept();
}

void server::run()
{
    ios.run();
}

bool server::start_listen()
{
    boost::system::error_code e;
    boost::asio::ip::tcp::endpoint endpoint { {}, 5050 };
    acceptor_.open(endpoint.protocol());
    acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
    acceptor_.bind(endpoint, e);
    if (e)
        return false;
    acceptor_.listen();
    return true;
}

void server::start_accept()
{
    boost::asio::ip::tcp::socket *s=new  boost::asio::ip::tcp::socket(ios);
    sockets.push_back(s);
    acceptor_.async_accept(*s, boost::bind(&server::handle_accept, this, boost::asio::placeholders::error));
}

#include <iostream>

void server::handle_accept(boost::system::error_code e)
{
    if(e)
    {
        std::cerr<<"e.message() = "<<e.message()<<std::endl;
        boost::asio::ip::tcp::socket *s=sockets.back();
        s->close();
        delete s;
        sockets.pop_back();

        acceptor_.close();
        if (!start_listen())
            return;
    }
    static int i=1;
    std::cerr<<"i = "<<i++<<std::endl;
    start_accept();
}

int main()
{
    server s;
    s.run();
}
