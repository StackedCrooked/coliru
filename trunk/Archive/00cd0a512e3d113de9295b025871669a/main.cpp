boost::system::error_code error;

boost::asio::streambuf response;
boost::asio::read_until(*sock, response, "\r\nfacepalm\r\n", error);
//boost::asio::read(*sock, response, error);

if(error > 0)
{
	std::cout << "error > 0" << std::endl;

	boost::mutex::scoped_lock lock_inner(closeflag_mutex);
	closeflag = true;
	return;
}

std::istream buffer( &response );

buffer >> ss.rdbuf();