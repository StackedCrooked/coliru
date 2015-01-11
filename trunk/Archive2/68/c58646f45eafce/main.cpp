#include <functional>
#include <string>
#include <memory>

#include <boost/asio.hpp>

class asio_service_client
{
public:
    asio_service_client (
                          const std::string & /*header*/,
                          const std::string & /*post*/,
                          std::function<void( boost::asio::streambuf & )> /*callback*/
                        )
    {}
};

struct faceDetector
{
    void parse__ ( boost::asio::streambuf & /*buffer*/ )
    {}
    
    faceDetector()
    {
        std::string header, post;
        auto client__1 = std::make_shared<asio_service_client>( header, post, 
                                                                std::bind( &faceDetector::parse__, this, std::placeholders::_1) );
        auto client__2 = std::make_shared<asio_service_client>( header, post, 
                                                                [&](boost::asio::streambuf & buffer ) {} );
    }
};

int main()
{
    faceDetector f;
}
