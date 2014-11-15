#define BOOST_LOG_DYN_LINK 1

#include <boost/filesystem.hpp>
#include <boost/log/attributes/scoped_attribute.hpp>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/expressions/formatters/date_time.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/sources/severity_channel_logger.hpp>
#include <boost/log/sources/channel_logger.hpp>
#include <boost/log/sources/global_logger_storage.hpp>
#include <boost/log/keywords/channel.hpp>
#include <boost/log/keywords/severity.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/manipulators/add_value.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <fstream>

#include <boost/log/sources/logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sources/global_logger_storage.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

namespace fs       = boost::filesystem;
namespace logging  = boost::log;
namespace src      = boost::log::sources;
namespace expr     = boost::log::expressions;
namespace sinks    = boost::log::sinks;
namespace attrs    = boost::log::attributes;
namespace keywords = boost::log::keywords;
namespace trivial  = boost::log::trivial;

struct Logger {
    void init(const fs::path &rErrEvtPath, const fs::path &rStatusPath) {
        // register common attributes - ThreadID, LineID, TimeStamp etc.
        logging::add_common_attributes();

        // Construct the sink for the "event_log" channel
        typedef sinks::synchronous_sink<sinks::text_ostream_backend> text_sink;
        auto sink = boost::make_shared<text_sink>();
        sink->locked_backend()->auto_flush(true);
        sink->locked_backend()->add_stream(boost::make_shared<std::ofstream>(rErrEvtPath.c_str()));
        sink->set_formatter(expr::format("%1% [%2%] tid[%3%] %4%") %
                            expr::format_date_time<boost::posix_time::ptime>("TimeStamp", "%H:%M:%S.%f") %
                            logging::trivial::severity % expr::attr<attrs::current_thread_id::value_type>("ThreadID") %
                            expr::smessage);
        sink->set_filter(expr::attr<std::string>("Channel") == "event");
        logging::core::get()->add_sink(sink);

        // Construct the sink for the "status_log" channel
        sink = boost::make_shared<text_sink>();
        sink->locked_backend()->auto_flush(true);
        sink->locked_backend()->add_stream(boost::make_shared<std::ofstream>(rStatusPath.c_str()));
        sink->set_formatter(expr::format("%1% [%2%] tid[%3%] %4%") %
                            expr::format_date_time<boost::posix_time::ptime>("TimeStamp", "%H:%M:%S.%f") %
                            logging::trivial::severity % expr::attr<attrs::current_thread_id::value_type>("ThreadID") %
                            expr::smessage);
        sink->set_filter(expr::attr<std::string>("Channel") == "status");
        logging::core::get()->add_sink(sink);
    }
};

BOOST_LOG_INLINE_GLOBAL_LOGGER_CTOR_ARGS(statuc_lg,
        src::severity_channel_logger_mt< >, (keywords::severity = trivial::error)(keywords::channel = "status"))
BOOST_LOG_INLINE_GLOBAL_LOGGER_CTOR_ARGS(event_lg,
        src::severity_channel_logger_mt< >, (keywords::severity = trivial::error)(keywords::channel = "event"))

#include <boost/thread.hpp>

int main()
{
    Logger l;
    l.init("/tmp/test.1", "/tmp/test.2");

    boost::thread_group tg;
    tg.create_thread([]{
            BOOST_LOG(statuc_lg::get()) << "this is a status update";
            BOOST_LOG(event_lg::get()) << "this is an event"; });
    tg.create_thread([]{
            BOOST_LOG(statuc_lg::get()) << "this is a status update";
            BOOST_LOG(event_lg::get()) << "this is an event"; });

    tg.join_all();
}
