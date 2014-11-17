#define BOOST_LOG_DYN_LINK 1

#include <string>
#include <fstream>
#include <thread>
#include <mutex>

#include <boost/filesystem.hpp>
#include <boost/log/core.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/attributes/scoped_attribute.hpp>
#include <boost/log/expressions/formatters/date_time.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/manipulators/add_value.hpp>
#include <boost/log/sources/severity_channel_logger.hpp>
#include <boost/log/sources/global_logger_storage.hpp>

namespace fs       = boost::filesystem;
namespace logging  = boost::log;
namespace src      = boost::log::sources;
namespace expr     = boost::log::expressions;
namespace sinks    = boost::log::sinks;
namespace attrs    = boost::log::attributes;
namespace keywords = boost::log::keywords;
namespace trivial  = boost::log::trivial;

#define LOG(logger, lvl) BOOST_LOG_CHANNEL_SEV(logger, "event", lvl)
#define LOG_TRACE(logger) BOOST_LOG_CHANNEL_SEV(logger, "event", trivial::trace)
#define LOG_DEBUG(logger) BOOST_LOG_CHANNEL_SEV(logger, "event", trivial::debug)
#define LOG_INFO(logger) BOOST_LOG_CHANNEL_SEV(logger, "event", trivial::info)
#define LOG_WARNING(logger) BOOST_LOG_CHANNEL_SEV(logger, "event", trivial::warning)
#define LOG_ERROR(logger) BOOST_LOG_CHANNEL_SEV(logger, "event", trivial::error)
#define LOG_FATAL(logger) BOOST_LOG_CHANNEL_SEV(logger, "event", trivial::fatal)

class Logger {
public:    
    using SEVChannelLoggerMT = src::severity_channel_logger_mt<trivial::severity_level>;
    
    /**
     * singleton pattern implementation
     *
     * @return singleton instance
     */
    static Logger* getInstance() {
        // Critical Section here
        std::lock_guard<std::mutex> lock(gMutexGuard);
        if (!gpInstance) {
            // Create the singleton class for clients to use
            gpInstance = new Logger();
        }
        return gpInstance;
    }

    // destructor
    virtual ~Logger() = default;

    /** define a log filter associated with a channel attribute */
    enum class LogDest { EventLog, StatusLog };
    
    /**
     * log the message to a specified log<p>
     *
     * @param logDest  [in] filter used to route the log message to
     *                 the correct logging sink.
     * @param rMessage [in] message to log
     */
    void logMessage(
        const LogDest logDest,
        const trivial::severity_level& severity,
        const std::string& rMessage) {
        switch (logDest) {
        case LogDest::EventLog:
            BOOST_LOG_CHANNEL_SEV(m_event_logger, "event", severity) << rMessage;
            break;
        case LogDest::StatusLog:
        default:
            BOOST_LOG_CHANNEL_SEV(m_status_logger, "status", severity) << rMessage;
            break;
        }
    }    

    /**
     * Returns logger associated with the specified log destination.<p>
     *
     * @param logDest  [in] filter used to route the log message to
     *                 the correct logging sink.
     * @return logger of the appropriate type
     */
    SEVChannelLoggerMT& getLoggerRef(const LogDest logDest) {
        switch (logDest) {
        case LogDest::EventLog:
            return m_event_logger;
            break;
        case LogDest::StatusLog:
        default:
            return m_status_logger;
            break;
        }
    }

    /**
     * Initialize the logging framework.<p>
     * Initializes the Boost logging framework by setting up the
     * following log files<p>.
     * Under the covers the Boost Logging framework initializes two
     * distinct log files.
     * <ul>
     *     <li>Error/Event log - this contains everything</li>
     *     <li>rStatusPath - high level log file which is also
     *     displayed on the iPad</li>
     * </ul>
     *
     * @param rErrEvtPath
     *               [in] fully qualified path to
     *               DlfLogBuffer[num].txt log file.  This log
     *               file will be created as necessary or
     *               reinitialized to empty (truncated) if it
     *               already exists.
     * @param rStatusPath
     *               [in] fully qualified path to
     *               DlfStatusBuffer[num].txt log file.  This log
     *               file will be created as necessary or
     *               reinitialized to empty (truncated) if it
     *               already exists.
     */
    static void init(
        const fs::path& rErrEvtPath,
        const fs::path& rStatusPath) {
        // Construct the sink for the "event" channel
        using text_sink = sinks::synchronous_sink<sinks::text_ostream_backend>;
        auto sink = boost::make_shared<text_sink>();
        sink->locked_backend()->auto_flush(true);
        sink->locked_backend()->add_stream(
            boost::make_shared<std::ofstream>(rErrEvtPath.c_str()));
        sink->set_formatter(expr::format("%1% [%2%] tid[%3%] %4%") 
            % expr::format_date_time<boost::posix_time::ptime>("TimeStamp", "%H:%M:%S.%f") 
            % logging::trivial::severity 
            % expr::attr<attrs::current_thread_id::value_type>("ThreadID") 
            % expr::smessage);
        sink->set_filter(expr::attr<std::string>("Channel") == "event");
        logging::core::get()->add_sink(sink);

        // Construct the sink for the "status" channel
        sink = boost::make_shared<text_sink>();
        sink->locked_backend()->auto_flush(true);
        sink->locked_backend()->add_stream(
            boost::make_shared<std::ofstream>(rStatusPath.c_str()));
        sink->set_formatter(expr::format("%1% [%2%] tid[%3%] %4%")
            % expr::format_date_time<boost::posix_time::ptime>("TimeStamp", "%H:%M:%S.%f")
            % logging::trivial::severity 
            % expr::attr<attrs::current_thread_id::value_type>("ThreadID") 
            % expr::smessage);
        sink->set_filter(expr::attr<std::string>("Channel") == "status");
        logging::core::get()->add_sink(sink);
        
        // register common attributes - ThreadID, LineID, TimeStamp etc.
        logging::add_common_attributes();
    }
private:
    // severity channel loggers - one for the error event log
    SEVChannelLoggerMT m_event_logger, m_status_logger;

    /**
     * Constructor - initialize each channel logger with a named
     * channel attribute which will be used by filtering to route
     * logging records to the appropriate sink.
     */
    Logger()
        : m_event_logger(keywords::channel = "event")
        , m_status_logger(keywords::channel = "status")
    {}
    // singleton and locking support
    static std::mutex gMutexGuard;
    static Logger* gpInstance;
};

// static and global initialization here
Logger* Logger::gpInstance = nullptr;
std::mutex Logger::gMutexGuard;

int main()
{
    static Logger* gpLogger = Logger::getInstance();
    
    gpLogger->init("test.1", "test.2");
    
    static auto& gEvtLog = gpLogger->getLoggerRef(Logger::LogDest::EventLog);
    static auto& gStsLog = gpLogger->getLoggerRef(Logger::LogDest::StatusLog);

    // vector container stores threads
    std::vector<std::thread> workers;
    for (int i = 0; i < 10; i++) {
        workers.push_back(std::thread([]() {
            LOG_INFO(gEvtLog) << "event log";
            LOG_INFO(gStsLog) << "status log";
        }));
    }
    std::cout << "main thread\n";

    std::for_each(workers.begin(), workers.end(),
        [](std::thread &t) {
            t.join();
        });
}
