#include <boost/asio.hpp>
#include <boost/chrono.hpp>
#include <boost/bind.hpp>
#include <boost/asio/high_resolution_timer.hpp>

typedef boost::chrono::high_resolution_clock hrc;
using boost::chrono::duration_cast;
using boost::chrono::milliseconds;

boost::asio::io_service                              io_service_;
boost::asio::high_resolution_timer                   timer_(io_service_);
hrc::time_point lastTime_(0ul);

void case1(boost::system::error_code ec)
{
    hrc::time_point currentTime = hrc::now();
	
	if (lastTime_.time_since_epoch().count()) {
		hrc::duration diff = currentTime - lastTime_;
		std::cout << "run time: " << duration_cast<milliseconds>(diff).count() << std::endl;
	}

	lastTime_ = hrc::now();
	timer_.expires_from_now(milliseconds(20));
	timer_.async_wait(boost::bind(case1, boost::asio::placeholders::error));
}

void test()
{
	timer_.expires_from_now(milliseconds(0));
	timer_.async_wait(boost::bind(case1, boost::asio::placeholders::error));
	io_service_.run();
}

int main()
{
	test();
}
