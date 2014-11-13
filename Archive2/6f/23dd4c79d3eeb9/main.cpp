#include <cstdlib>
#include <iostream>
#include <sstream>

#include <syslog.h>

static const int OUR_LOG_LEVEL 
    = LOG_DEBUG;
    // = LOG_NOTICE;

// log up to LOG_DEBUG output:
//std::err log opened with logName: test_log
//std::err log line flushed: "s:1:test server:Creating connection "
//std::err log line flushed: "c:23:test_conn 1:a:connection created "
//std::err log line flushed: "c:23:test_conn 1:b:connection is doing something "
//std::err log line flushed: "c:23:test_conn 1:c:connection destroyed "
//std::err log closed

// log up to LOG_NOTICE output:
//std::err log opened with logName: test_log
//std::err log line flushed: "c:23:test_conn 1:a:connection created "
//std::err log line flushed: "c:23:test_conn 1:c:connection destroyed "
//std::err log closed

// ---------------------------- for_each.h start ----------------------------//
#include <tuple>
#include <utility>

namespace helpers
{

////////////////////////////////////////////////////////////////
// param accessor

struct TParamAccessorDefaultTraits
{
};

template <typename _object_t, typename _value_type, _value_type _object_t::*member_t, typename _traits_t = TParamAccessorDefaultTraits>
struct TParamAccessor : public _traits_t
{
    using traits_t = _traits_t;
    using object_t = _object_t;
    using value_type = _value_type;
		
	static value_type& GetRef(object_t& data) { return data.*member_t; }
};

////////////////////////////////////////////////////////////////
// append to tuple

template<typename new_t, typename... other_t>
struct append_to_tuple
{
	using type = std::tuple<other_t..., new_t>;
};

template<typename new_t, typename... other_t>
struct append_to_tuple<new_t, std::tuple<other_t...>>
{
	using type = std::tuple<other_t..., new_t>;
};

////////////////////////////////////////////////////////////////
// for_each_impl

template<size_t i, typename... args_t>
struct for_each_impl
{
	using this_type = typename std::tuple_element<i, std::tuple<args_t...>>::type;
	using prev_type = for_each_impl<i - 1, args_t...>;

	template<template<size_t, typename> class func_t>
	using instantiate = 
		typename append_to_tuple<
			typename func_t<i, this_type>::type, 
			typename prev_type::template instantiate<func_t>
		>::type;
	
	template<typename object_t, typename... call_args_t>
	static void call(object_t&& obj, call_args_t&&... args)
	{
		prev_type::call(std::forward<object_t>(obj), std::forward<call_args_t>(args)...);
		this_type::call(std::forward<object_t>(obj), std::forward<call_args_t>(args)...);
	}
};

template<typename... args_t>
struct for_each_impl<0, args_t...>
{
	using this_type = typename std::tuple_element<0, std::tuple<args_t...>>::type;
	
	template<template<size_t, typename> class func_t>
	using instantiate = std::tuple<typename func_t<0, this_type>::type>;
	
	template<typename object_t, typename... call_args_t>
	static void call(object_t&& obj, call_args_t&&... args)
	{
		this_type::call(std::forward<object_t>(obj), std::forward<call_args_t>(args)...);
	}
	
	template<typename object_t>
	static void call(object_t&& obj)
	{
		this_type::call(std::forward<object_t>(obj));
	}
};

///////////////////////////////////////////////////////////////
// for_each

template<typename... args_t>
struct for_each
{
	using prev_type = for_each_impl<sizeof...(args_t) - 1, args_t...>;
	
	template<template<size_t, typename> class func_t>
	using instantiate = typename prev_type::template instantiate<func_t>;

	template<typename object_t, typename... call_args_t>
	static object_t call(object_t&& obj, call_args_t&&... args)
	{
		prev_type::call(std::forward<object_t>(obj), std::forward<call_args_t>(args)...);
		return obj;
	}
	
	template<typename object_t>
	static object_t call(object_t&& obj)
	{
		prev_type::call(std::forward<object_t>(obj));
		return obj;
	}
};

template<typename... args_t>
struct for_each<std::tuple<args_t...>> : public for_each<args_t...>
{
};

template<>
struct for_each<std::tuple<>>
{
	template<template<size_t, typename> class func_t>
	using instantiate = std::tuple<>;

	template<typename object_t, typename... call_args_t>
	static object_t call(object_t&& obj, call_args_t&&... args)
	{
		return obj;
	}
	
	template<typename object_t>
	static object_t call(object_t&& obj)
	{
		return obj;
	}
};

} //namespace helpers

// ---------------------------- for_each.h end ----------------------------//


using namespace helpers;

//////////////////////////////////////////////////////////////////////////////////////////


template<int logUpTo>
struct TLogTraitsStdErr
{
    static void Open(const char* logName, int facility)
	{
    	std::cerr << "std::err log opened with logName: " << logName << std::endl;
	}
	
	static void CloseLog()
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<int logUpTo>
struct TLogTraitsSyslog
{
	static void Open(const char* logName, int facility)
	{
		openlog(logName, LOG_PID | LOG_NDELAY, facility);
		setlogmask(LOG_UPTO(logUpTo));
	}
	
	static void CloseLog()
	{
		closelog();
	}
	
	template<int logLevel, bool isNull>
	struct TSink
	{
		~TSink()
		{
			syslog(logLevel, stream.str().c_str(), "junk");
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

template<char moduleName, typename object_t>
struct TLogHeader
{
	template<size_t idx, typename accessor_t>
	struct TLogHeaderWriter
	{
		using type = TLogHeaderWriter<idx, accessor_t>;

		static void call(typename accessor_t::object_t& obj, std::stringstream& out)
		{
			typename accessor_t::value_type& val = accessor_t::GetRef(obj);
			out << val << ":";
		}
	};
	
	template<typename sink_type>
	friend sink_type& operator << (sink_type& sink, object_t& val)
	{
		std::stringstream header;
		
		using writers = typename for_each<typename object_t::log_header_param_list_t>::template instantiate<TLogHeaderWriter>;
		for_each<writers>::call(*static_cast<object_t*>(&val), header);

		sink << moduleName << ":" << header.str();
		return sink;
	}
};

//////////////////////////////////////////////////////////////////////////////////////////
	
template<int logUpTo, template<int> class log_traits = TLogTraitsSyslog>
struct TLog : public log_traits<logUpTo>
{
	using trats_t = log_traits<logUpTo>;
	
	template<int logLevel, bool isNull>
	using sink_type = typename trats_t::template sink_type<logLevel, isNull>;
	
	TLog()
	{
	}

	~TLog()
	{
		trats_t::CloseLog();
	}
	
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

struct CConnection : public TLogHeader<'c', CConnection>
{
	CConnection(int _id, const std::string& _name) : m_id(_id), m_name(_name), m_state('a')
    {
        TestLog::Log<LOG_NOTICE>() << *this << "connection created";
        m_state = 'b';
    }
 
    ~CConnection()
    {
        TestLog::Log<LOG_NOTICE>() << *this << "connection destroyed";
    }
    
    void DoSomething()
    {
        TestLog::Log<LOG_DEBUG>() << *this << "connection is doing something";
        m_state = 'c';
    }
    
	using this_t = CConnection;

	int m_id;           using m_id_t = TParamAccessor<this_t, decltype(this_t::m_id), &this_t::m_id>;
	std::string m_name; using m_name_t = TParamAccessor<this_t, decltype(this_t::m_name), &this_t::m_name>;
    char m_state;       using m_state_t = TParamAccessor<this_t, decltype(this_t::m_state), &this_t::m_state>;
	
	using log_header_param_list_t = std::tuple<m_id_t, m_name_t, m_state_t>;
};

class CServer :  public TLogHeader<'s', CServer>, public TestLog
{
public:

    CServer() : m_id(1), m_name("test server")
	{
		TestLog::Open("test_log", 1);
	};

    int Run()
    {
        TestLog::Log<LOG_DEBUG>() << *this << "Creating connection";
        
        CConnection test_conn1(23, "test_conn 1");
        test_conn1.DoSomething();
        
        return 0;
    }
    
    using this_t = CServer;

	int m_id; using m_id_t = TParamAccessor<this_t, decltype(this_t::m_id), &this_t::m_id>;
	std::string m_name; using m_name_t = TParamAccessor<this_t, decltype(this_t::m_name), &this_t::m_name>;
	
	using log_header_param_list_t = std::tuple<m_id_t, m_name_t> ;
};
    
int main(int argc, char** argv)
{
    CServer server;
    
    return server.Run();
}
