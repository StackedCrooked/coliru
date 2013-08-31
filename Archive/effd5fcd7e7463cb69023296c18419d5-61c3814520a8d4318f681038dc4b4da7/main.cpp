void TradeEmpires::GameServer::join_and_auth_accept_handler(const boost::system::error_code& error,
                                                            std::shared_ptr<boost::asio::ip::tcp::socket> sock) {
    std::cout << "Incoming socket from " << sock->local_endpoint().address().to_string() << ":" << sock->local_endpoint().port() << "\n";

    auto username_length_buf = std::make_shared<std::array<unsigned char, sizeof(int32_t)>>();
    boost::asio::async_read(*sock,
                            boost::asio::buffer(*username_length_buf),
                            std::bind(&GameServer::join_and_auth_read_user_handler,
                                      this,
                                      std::placeholders::_1,
                                      std::placeholders::_2,
                                      sock,
                                      username_length_buf));
}
