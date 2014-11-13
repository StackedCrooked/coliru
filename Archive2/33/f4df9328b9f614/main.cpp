#include <cstdlib>
#include <iostream>
#include <sstream>

#include <syslog.h>


static const int OUR_LOG_LEVEL 
    = LOG_DEBUG;
    // = LOG_NOTICE;

// log up to LOG_DEBUG output:
//std::err log opened with logName: test_log
//std::err log line flushed: "Creating connection "
//std::err log line flushed: "connection created "
//std::err log line flushed: "connection is doing something "
//std::err log line flushed: "connection destroyed "
//std::err log closed

// log up to LOG_NOTICE output:
//std::err log opened with logName: test_log
//std::err log line flushed: "connection created "
//std::err log line flushed: "connection destroyed "
//std::err log closed

//////////////////////////////////////////////////////////////////////////////////////////

template<int logUpTo>
struct TLogTraitsStdErr
{
    void Open(const char* logName, int facility)
	{
    	std::cerr << "std::err log opened with logName: " << logName << std::endl;
	}
	
    ~TLogTraitsStdErr()
	{
        std::cerr << "std::err log closed" << std::endl;
	}
	
    template<int logLevel, bool isNull>
    struct TSink
    {
        ~TSink()
        {
            std::cerr << "std::err log line flushed: \"" << stream.str() << " \"" << std::endl;
        }
    
        std::stringstream stream;
        
        template<typename T>
        TSink<logLevel, isNull>& operator << (T&& val)
        {
            stream << val;
            return *this;
        }
    };

    template<int logLevel>
    struct TSink<logLevel, true>
    {
        template<typename T>
        TSink<logLevel, true>& operator << (T&& val)
        {
            return *this;
        }
    };
	
	template<int logLevel, bool isNull>
	using sink_type = TSink<logLevel, isNull>;
};

//////////////////////////////////////////////////////////////////////////////////////////
	
template<int logUpTo, template<int> class log_traits>
struct TLog : public log_traits<logUpTo>
{
	using trats_t = log_traits<logUpTo>;
	
	template<int logLevel, bool isNull>
	using sink_type = typename trats_t::template sink_type<logLevel, isNull>;
	
	template<int neededLogLevel, int logLevel>
	struct TGetLogOfLevel
	{
		using type = typename std::conditional<
			neededLogLevel == logLevel,
			sink_type<neededLogLevel, (neededLogLevel > logUpTo)>,
			typename TGetLogOfLevel<neededLogLevel, logLevel + 1>::type
		>::type;
    };
	
	template<int neededLogLevel>
	struct TGetLogOfLevel<neededLogLevel, LOG_DEBUG + 1>
	{
        using type = void;
    };
	
	template<int neededLogLevel>
	using Log = typename TGetLogOfLevel<neededLogLevel, 0>::type;
};

///////////////////////////////
//testcase

using TestLog = TLog<OUR_LOG_LEVEL, TLogTraitsStdErr>;

struct CConnection
{
	CConnection()
    {
        TestLog::Log<LOG_NOTICE>() << "connection created";
    }
 
    ~CConnection()
    {
        TestLog::Log<LOG_NOTICE>() << "connection destroyed";
    }
    
    void DoSomething()
    {
        TestLog::Log<LOG_DEBUG>() << "connection is doing something";
    }
};

class CServer : public TestLog
{
public:

    CServer()
	{
		TestLog::Open("test_log", 1);
	};

    int Run()
    {
        TestLog::Log<LOG_DEBUG>() << "Creating connection";
        
        CConnection test_conn1;
        test_conn1.DoSomething();
        
        return 0;
    }
};
    
int main(int argc, char** argv)
{
    CServer server;
    
    return server.Run();
}