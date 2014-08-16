#include <stdexcept>

#include <boost/exception/exception.hpp>
#include <boost/throw_exception.hpp>

struct my_exception: virtual boost::exception, virtual std::out_of_range {
    my_exception(): std::out_of_range { "dear god why" } {}
};

int main()
{
    BOOST_THROW_EXCEPTION(( my_exception {} ));
}