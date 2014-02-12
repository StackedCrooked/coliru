//#define SEHE_USE_SSL
#define BOOST_ASIO_ENABLE_HANDLER_TRACKING
//
// client.cpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2013 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

class client
{
public:
  client(boost::asio::io_service& io_service,
      boost::asio::ssl::context& context,
      boost::asio::ip::tcp::resolver::iterator endpoint_iterator)
    : socket_(io_service
#ifdef SEHE_USE_SSL
            , context)
  {
    socket_.set_verify_mode(boost::asio::ssl::verify_peer);
    socket_.set_verify_callback(
        boost::bind(&client::verify_certificate, this, _1, _2));
#else
            )
  {
      (void) context;
#endif

    boost::asio::async_connect(socket_.lowest_layer(), endpoint_iterator,
        boost::bind(&client::handle_connect, this,
          boost::asio::placeholders::error));
  }

  bool verify_certificate(bool preverified,
      boost::asio::ssl::verify_context& ctx)
  {
      // The verify callback can be used to check whether the certificate that is
      // being presented is valid for the peer. For example, RFC 2818 describes
      // the steps involved in doing this for HTTPS. Consult the OpenSSL
      // documentation for more details. Note that the callback is called once
      // for each certificate in the certificate chain, starting from the root
      // certificate authority.

      // In this example we will simply print the certificate's subject name.
      char subject_name[256];
      X509* cert = X509_STORE_CTX_get_current_cert(ctx.native_handle());
      X509_NAME_oneline(X509_get_subject_name(cert), subject_name, 256);
      std::cout << "Verifying " << subject_name << "\n";

      return preverified;
  }

  void handle_connect(const boost::system::error_code& error)
  {
#ifdef SEHE_USE_SSL
      if (!error)
      {
          socket_.async_handshake(boost::asio::ssl::stream_base::client,
                  boost::bind(&client::handle_handshake, this,
                      boost::asio::placeholders::error));
      }
      else
      {
          std::cout << "Connect failed: " << error.message() << "\n";
      }
#else
      handle_handshake(error);
#endif
  }

  void handle_handshake(const boost::system::error_code& error)
  {
      if (!error)
      {
          std::cout << "Enter message: ";
          static char const raw[] = "GET / HTTP/1.1\r\nHost: www.google.de\r\nConnection: close\r\n\r\n\r\n";

          static_assert(sizeof(raw)<=sizeof(request_), "too large");

          size_t request_length = strlen(raw);
          std::copy(raw, raw+request_length, request_);
          
          {
              std::ostream hexos(std::cout.rdbuf());
              for(auto it = raw; it != raw+request_length; ++it)
              {
                  hexos << std::hex << std::setw(2) << std::setfill('0') << std::showbase << ((short unsigned) *it) << " ";
              }
              std::cout << "\n";
          }
          
          boost::asio::async_write(socket_,
                  boost::asio::buffer(request_, request_length),
                  boost::bind(&client::handle_write, this,
                      boost::asio::placeholders::error,
                      boost::asio::placeholders::bytes_transferred));
      }
      else
      {
          std::cout << "Handshake failed: " << error.message() << "\n";
      }
  }

  void handle_write(const boost::system::error_code& error,
      size_t /*bytes_transferred*/)
  {
      if (!error)
      {
          std::cout << "starting read loop\n";
          boost::asio::async_read_until(socket_,
                  //boost::asio::buffer(reply_, sizeof(reply_)),
                  reply_, '\n',
                  boost::bind(&client::handle_read, this,
                      boost::asio::placeholders::error,
                      boost::asio::placeholders::bytes_transferred));
      }
      else
      {
          std::cout << "Write failed: " << error.message() << "\n";
      }
  }

  void handle_read(const boost::system::error_code& error, size_t /*bytes_transferred*/)
  {
      if (!error)
      {
          std::cout << "Reply: " << &reply_ << "\n";
      }
      else
      {
          std::cout << "Read failed: " << error.message() << "\n";
      }
  }

private:
#ifdef SEHE_USE_SSL
  boost::asio::ssl::stream<boost::asio::ip::tcp::socket> socket_;
#else
  boost::asio::ip::tcp::socket socket_;
#endif
  char request_[1024];
  //char reply_  [1024];
  boost::asio::streambuf reply_;
};

int main(int argc, char* argv[])
{
    try
    {
        if (argc != 3)
        {
            std::cerr << "Usage: client <host> <port>\n";
            return 1;
        }

        boost::asio::io_service io_service;

        boost::asio::ip::tcp::resolver resolver(io_service);
        boost::asio::ip::tcp::resolver::query query(argv[1], argv[2]);
        boost::asio::ip::tcp::resolver::iterator iterator = resolver.resolve(query);

        boost::asio::ssl::context ctx(boost::asio::ssl::context::sslv23);
        ctx.set_default_verify_paths();

        client c(io_service, ctx, iterator);

        io_service.run();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}

