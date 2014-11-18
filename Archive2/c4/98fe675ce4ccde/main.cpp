#include <boost/chrono.hpp>
#include <boost/asio.hpp>
#include <boost/asio/spawn.hpp>
#include <boost/asio/steady_timer.hpp>

#include <iostream>

namespace asio = ::boost::asio;

template <typename Handler>
class handler_wrapper
{
public:
    explicit handler_wrapper (Handler handler) 
      : handler_ (std::move (handler))
    {}
 
    void operator() (boost::system::error_code ec)
    {
        handler_(ec);
    }
 
private:
    Handler handler_;
};
 

template <typename Timer, typename Token> auto my_timer(Timer &timer, Token &&token) {
    typename asio::handler_type<Token, void(::boost::system::error_code const)>::type handler(
        std::forward<Token>(token));

    asio::async_result<decltype(handler)> result(handler);

    // both options works fine.
    timer.async_wait( [handler] (::boost::system::error_code ec) mutable { handler (ec); } );
    // timer.async_wait(handler_wrapper<decltype(handler)> (handler));    
    
    return result.get();
}

int main() {
    asio::io_service io;
    asio::steady_timer timer(io, ::boost::chrono::seconds(1));

    asio::spawn(io, [&](asio::yield_context yield) {
        asio::io_service::work work (io);
        try {
            std::cout << "my_timer enter\n";
            my_timer(timer, yield);
            std::cout << "my_timer returns\n";
        }
        catch (boost::coroutines::detail::forced_unwind const &e) {
            throw;
        }
        catch (std::exception const &e) {
            std::cout << "exception: '" << e.what() << "'\n";
        }
    });

    io.run();
    std::cout << "Done\n";
}
