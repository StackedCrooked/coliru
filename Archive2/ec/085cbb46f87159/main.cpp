#include <boost/chrono.hpp>
#include <boost/asio.hpp>
#include <boost/asio/spawn.hpp>
#include <boost/asio/steady_timer.hpp>

#include <iostream>

namespace asio = ::boost::asio;

template <typename Timer, typename Token> auto my_timer(Timer &timer, Token &&token) {
    typename asio::handler_type<Token, void(::boost::system::error_code const)>::type handler(
        std::forward<Token>(token));

    asio::async_result<decltype(handler)> result(handler);

    timer.async_wait(handler);
    return result.get();
}

int main() {
    asio::io_service io;
    asio::steady_timer timer(io, ::boost::chrono::seconds(1));

    asio::spawn(io, [&](asio::yield_context yield) {
        try {
            std::cout << "my_timer enter\n";
            my_timer(timer, yield);
            std::cout << "my_timer returns\n";
        }
        catch (boost::coroutines::detail::forced_unwind const &e) {
            throw;
        }
        catch (const boost::coroutines::detail::forced_unwind &e) {
            std::cout << "boost::coroutines::detail::forced_unwind\n";
        }
    });

    io.run();
    std::cout << "Done\n";
}
