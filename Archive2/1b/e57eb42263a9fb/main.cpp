
#define BOOST_LOG_DYN_LINK
#define BOOST_SYSTEM_NO_DEPRECATED
    
#include <boost/log/sinks.hpp>
#include <boost/log/trivial.hpp>
    
int main() {
    
    using namespace boost::log;
    
    typedef sinks::synchronous_sink<sinks::text_file_backend> sink_t;
    
    boost::shared_ptr<sink_t> sink(
        new sink_t(boost::make_shared<sinks::text_file_backend>(keywords::file_name="my.log")));
    core::get()->add_sink(sink);
    
    BOOST_LOG_TRIVIAL(debug) << "hello";
}
