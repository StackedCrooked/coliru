#include <boost/asio.hpp>
#include <boost/bind.hpp>



template <typename T>
struct bind_struct{

   typedef boost::system::error_code                         error_code;
   typedef boost::asio::ip::tcp::acceptor                    tcp_acceptor_type;
   typedef std::shared_ptr<boost::asio::ip::tcp::socket>     socket_type;


   static void tcp_on_async_accept(error_code& er,
                                  tcp_acceptor_type* acc,
                                  socket_type socket){
       std::cout << "ok" << std::endl;
   }
   static void good_function(int m){
       std::cout << m << std::endl;
   }
};

int main(){
      /*Error*/
  bind_struct<void>::socket_type sock;
  bind_struct<void>::tcp_acceptor_type* acc;
  auto fn = boost::bind(bind_struct<void>::tcp_on_async_accept,
                                                boost::asio::placeholders::error,
                                                acc, sock);
  fn();


  /*Ok*/
  auto fn1 = boost::bind(bind_struct<void>::good_function,_1);
  fn1(10);
}