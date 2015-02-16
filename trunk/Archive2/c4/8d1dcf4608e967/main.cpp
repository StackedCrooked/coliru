#include <iostream>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/asio/spawn.hpp>
#include <memory>

template <typename Handler>
void bar(boost::asio::io_service &io, Handler cb){
    auto ptr = std::make_shared<boost::asio::deadline_timer>(io, boost::posix_time::seconds(1));
    ptr->async_wait([ptr, cb](const boost::system::error_code&){
        using boost::asio::asio_handler_invoke;
        asio_handler_invoke(cb, &cb);
    });
}

template<typename Handler>
void foo(boost::asio::io_service &io, Handler && handler){
    typename boost::asio::handler_type<Handler, void()>::type handler_(std::forward<Handler>(handler));
    boost::asio::async_result<decltype(handler_)> result(handler_);
    bar(io, handler_);
    result.get();
    return;
}

int main()
{
  boost::asio::io_service io;
  boost::asio::spawn(io, [&io](boost::asio::yield_context yield){
      foo(io, yield);
      std::cout << "hello, world!\n";
  });

  io.run();

  return 0;
}