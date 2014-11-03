#include <ctime>
#include <iostream>
#include <string>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/make_shared.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>

using namespace boost;
using asio::ip::udp;
using system::error_code;

std::string make_daytime_string()
{
    using namespace std; // For time_t, time and ctime;
    time_t now = time(0);
    return ctime(&now);
}

class udp_server; // forward declaration

struct udp_session : enable_shared_from_this<udp_session> {

    udp_session(udp_server* server) : server_(server) {}

    void handle_request(const error_code& error);

    void handle_sent(const error_code& ec, std::size_t) {
        // here response has been sent
        if (ec) {
            std::cout << "Error sending response to " << remote_endpoint_ << ": " << ec.message() << "\n";
        }
    }

    udp::endpoint remote_endpoint_;
    array<char, 100> recv_buffer_;
    std::string message;
    udp_server* server_;
};

class udp_server
{
    typedef shared_ptr<udp_session> shared_session;
  public:
    udp_server(asio::io_service& io_service)
        : socket_(io_service, udp::endpoint(udp::v4(), 1313)), 
          strand_(io_service)
    {
        receive_session();
    }

  private:
    void receive_session()
    {
        // our session to hold the buffer + endpoint
        auto session = make_shared<udp_session>(this);

        socket_.async_receive_from(
                asio::buffer(session->recv_buffer_), 
                session->remote_endpoint_,
                strand_.wrap(
                    bind(&udp_server::handle_receive, this,
                        session, // keep-alive of buffer/endpoint
                        asio::placeholders::error,
                        asio::placeholders::bytes_transferred)));
    }

    void handle_receive(shared_session session, const error_code& ec, std::size_t /*bytes_transferred*/) {
        // now, handle the current session on any available pool thread
        socket_.get_io_service().post(bind(&udp_session::handle_request, session, ec));

        // immediately accept new datagrams
        receive_session();
    }

    void enqueue_response(shared_ptr<udp_session> const& session) {
        socket_.async_send_to(asio::buffer(session->message), session->remote_endpoint_,
                strand_.wrap(bind(&udp_session::handle_sent, 
                        session, // keep-alive of buffer/endpoint
                        asio::placeholders::error,
                        asio::placeholders::bytes_transferred)));
    }

    udp::socket  socket_;
    asio::strand strand_;

    friend struct udp_session;
};

void udp_session::handle_request(const error_code& error)
{
    if (!error || error == asio::error::message_size)
    {
        message = make_daytime_string(); // let's assume this might be slow

        // let the server coordinate actual IO
        server_->enqueue_response(shared_from_this());
    }
}

int main()
{
    try {
        asio::io_service io_service;
        udp_server server(io_service);

        thread_group group;
        for (unsigned i = 0; i < thread::hardware_concurrency(); ++i)
            group.create_thread(bind(&asio::io_service::run, ref(io_service)));

        group.join_all();
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}
