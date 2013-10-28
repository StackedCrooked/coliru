#include <cxxabi.h>
#include <cstdio>
#include <cstdlib>
#include <cerrno>
#include <cctype>
#include <cstring>
#include <iostream>
#include <sstream>
#include <memory>
#include <limits>
#include <chrono>
#include <string>
#include <vector>
#include <random>
#include <stdexcept>

std::locale userLocale("");
const size_t numNumbers = 1e5;

//////////////////////////////////////////////////////////////////////
template <class U, class T>
bool inRange(T value)
{
    if (std::is_signed<U>::value)
		return (  static_cast<intmax_t>(value)
		            >= static_cast<intmax_t>(std::numeric_limits<U>::min())
		       && static_cast<intmax_t>(value)
		            <= static_cast<intmax_t>(std::numeric_limits<U>::max()));
	else
		return (  static_cast<uintmax_t>(value)
		            <= static_cast<uintmax_t>(std::numeric_limits<U>::max()));
}

//////////////////////////////////////////////////////////////////////
template<class T>
T stringstream_convert(const std::string & s)
{
	std::istringstream str(s);
	T retval;
	str >> retval;
	return retval;
}

//////////////////////////////////////////////////////////////////////
template <class T>
T sscanf_convert(const std::string & s)
{
	T retval;
	int numRead = 0;
	const char * format;

	if (sizeof(T) == sizeof(int8_t))
		format = "%hhi%n";
	else if (sizeof(T) == sizeof(short))
		format = "%hi%n";
	else if (sizeof(T) == sizeof(int))
		format = "%i%n";
	else if (sizeof(T) == sizeof(long))
		format = "%li%n";
	else if (sizeof(T) == sizeof(long long))
		format = "%Li%n";
	else
		throw std::invalid_argument(s);

	int rc = sscanf(s.c_str(), format, &retval, &numRead);

	if (rc != 1)
	{
		std::cout << rc << ", " << retval << ", " << numRead << std::endl;
		throw std::invalid_argument(s + " bad convert " + strerror(errno));
	} else if (static_cast<std::string::size_type>(numRead) != s.length())
		throw std::invalid_argument(s + " incomplete convert");

	return retval;
}
//////////////////////////////////////////////////////////////////////
template<class T>
T strtol_convert(const std::string & s)
{
	std::string::value_type * endptr = nullptr;
	errno = 0;
	auto value  = strtol(s.c_str(), &endptr, 0);

	if (errno != 0)
		throw std::invalid_argument(s);
	else if (endptr - s.data() !=  static_cast<ptrdiff_t>(s.length()))
		throw std::invalid_argument(s);
	else if ( ! inRange<decltype(value), T>(value))
		throw std::range_error(s + " is out of range for type");
	
	return static_cast<T>(value);
}

//////////////////////////////////////////////////////////////////////
template<class T>
T strtoll_convert(const std::string & s)
{
	errno = 0;
	auto value  = strtoll(s.c_str(), nullptr, 0);
	if (errno != 0)
		throw std::invalid_argument(s);

	if ( ! inRange<decltype(value), T>(value))
		throw std::range_error(s + " is out of range for type");
	
	return static_cast<T>(value);
}

//////////////////////////////////////////////////////////////////////
template<class T>
T stoi_convert(const std::string & s)
{
	auto value  = std::stoi(s, nullptr, 0);
	return static_cast<T>(value);
}

//////////////////////////////////////////////////////////////////////
template<class T>
T stol_convert(const std::string & s)
{
	auto value  = std::stol(s, nullptr, 0);
	return static_cast<T>(value);
}

//////////////////////////////////////////////////////////////////////
template<class T>
T stoll_convert(const std::string & s)
{
	auto value  = std::stoll(s, nullptr, 0);
	return static_cast<T>(value);
}

//////////////////////////////////////////////////////////////////////
template<class T>
T hybrid_convert(const std::string & s)
{
	if(std::is_integral<T>::value)
	{
		if(std::is_unsigned<T>::value)
		{
			auto res = std::strtoull(s.c_str(), 0, 0);
			if ( ! inRange<decltype(res), T>(res) )
				throw std::range_error(s + " is out of range for type");
			return static_cast<T>(res);
		} else
		{
			auto res = std::strtoll(s.c_str(), 0, 0);
			if ( ! inRange<decltype(res), T>(res) )
				throw std::range_error(s + " is out of range for type");
			return static_cast<T>(res);
		}
	} else
	{
		std::istringstream is(s);
		T res;
		if(is >> res)
			return res;
		throw std::runtime_error("hurrrrg");
	}
}

//////////////////////////////////////////////////////////////////////
template<class T>
T handcoded_convert(const std::string & s)
{
	T retVal = 0;
	unsigned int base = 10;
	std::string::size_type i = 0;
	std::string::size_type length = s.length();
	bool negate = false;

	while (i < s.length() && std::isspace(s[i]))
	{
		++i;
	}

	if (length >= 1)
	{
		if (s[i] == '-')
		{
			negate = true;
			++i;
		} else if (s[i] == '+')
		{
			++i;
		}
	}
	
	if ((length - i) >= 1 && s[i] == '0')
	{
		base = 8;
		++i;
		if ((length - i) >= 2 && s[i] == 'x')
		{
			++i;
			base = 16;
		}
	}

	for (; i < length; ++i)
	{
		if (  retVal == std::numeric_limits<T>::max()
		   || retVal == std::numeric_limits<T>::min())
			throw std::range_error(s + " - is out of range for type");

		retVal *= base;
		retVal += s[i] - '0';
	}

	return (negate ? -retVal : retVal);
}

//////////////////////////////////////////////////////////////////////
template<class T>
std::vector<std::string> generateRandStrings(size_t number)
{
	std::vector<std::string> retVal;
	std::default_random_engine engine;
	std::uniform_int_distribution<T> dist(std::numeric_limits<T>::min(),
	                                      std::numeric_limits<T>::max());
	using clock = std::chrono::system_clock;
	std::chrono::time_point<clock> begin, end;

	begin = clock::now();
	for (size_t i = 0; i < number; ++i)
	{
		T value = dist(engine);
		retVal.push_back(std::to_string(value));
	}
	end = clock::now();

	std::chrono::duration<double> length = end - begin;

	std::cout << "Generation took " << length.count()
	          << " seconds" << std::endl;

	return retVal;
}

//////////////////////////////////////////////////////////////////////
template<class T>
T time_run(const std::vector<std::string> & v,
           T (*convert)(const std::string &),
           int samples = 1)
{
	T val = 0;
	using clock = std::chrono::system_clock;
	std::chrono::time_point<clock> begin, end;
	double average = 0.0;

	for (int x = 0; x < samples; ++x)
	{
		begin = clock::now();
		for (auto i = v.cbegin(); i != v.cend(); ++i)
		{
			val = convert(*i);
		}
		end = clock::now();

		std::chrono::duration<double> length = end - begin;
		average += length.count();
	}
	average /= samples;
	std::cout << average << " seconds" << std::endl;
	return val;
}

//////////////////////////////////////////////////////////////////////
struct MallocDeleter {
	void operator () (void * p) { free(p); }
};

//////////////////////////////////////////////////////////////////////
template <class T>
const std::string getTypeName()
{
	// This is tricky stuff - DO NOT use array specialization here
	std::unique_ptr<char, MallocDeleter> buffer;
	int status = 0;

	buffer.reset(abi::__cxa_demangle(typeid(T).name(), NULL, NULL, &status));

	switch (status)
	{
	 case 0:
		 return std::string(buffer.get());
		 break;

	 case -1:
		 throw std::bad_alloc();
		 break;

	 case -2:
		throw std::runtime_error(std::string("Mangled name ") +
		                         typeid(T).name() + " is invalid");
		break;

	 case -3:
		throw std::invalid_argument("Bad argument passed to __cxa_demangle");
		break;

	 default:
		throw std::out_of_range("__cxa_demangle returned bad status");
	}

	return std::string();
}

//////////////////////////////////////////////////////////////////////
template <class T>
bool checkResults(const std::vector<std::string> & v,
                  T (*convert)(const std::string &))
{
	for (auto i = v.cbegin(); i != v.cend(); ++i)
	{
		auto result = convert(*i);
		long long trueValue = strtoll(i->c_str(), 0, 0);

		if (trueValue != result)
			return false;
	}

	return true;
}

//////////////////////////////////////////////////////////////////////
template<class T>
void benchmark(int samples = 1)
{
	std::cout << std::string(70, '-') << std::endl
	          << getTypeName<T>()
	          << " conversion (size = " << sizeof(T)*8 << " bits) - ";

	std::vector<std::string> strings = generateRandStrings<T>(numNumbers);

	std::cout << std::string(70, '-') << std::endl;

	////
	std::cout << "  stringstream: ";
	if (checkResults(strings, stringstream_convert<T>))
		time_run<T>(strings, stringstream_convert<T>, samples);
	else
		std::cout << "FAILURE" << std::endl;

	////
	std::cout << "        sscanf: ";
	if (checkResults(strings, sscanf_convert<T>))
		time_run<T>(strings, sscanf_convert<T>, samples);
	else
		std::cout << "FAILURE" << std::endl;

	////
	std::cout << "          stoi: ";
	if (sizeof(T) > sizeof(int))
		std::cout << "SKIPPED" << std::endl;
	else if (checkResults(strings, stoi_convert<T>))
		time_run<T>(strings, stoi_convert<T>, samples);
	else
		std::cout << "FAILURE" << std::endl;

	////
	std::cout << "        strtol: ";
	if (sizeof(T) > sizeof(long))
		std::cout << "SKIPPED" << std::endl;
	else if (checkResults(strings, strtol_convert<T>))
		time_run<T>(strings, strtol_convert<T>, samples);
	else
		std::cout << "FAILURE" << std::endl;

	std::cout << "          stol: ";
	if (sizeof(T) > sizeof(long))
		std::cout << "SKIPPED" << std::endl;
	else if (checkResults(strings, stol_convert<T>))
		time_run<T>(strings, stol_convert<T>, samples);
	else
		std::cout << "FAILURE" << std::endl;

	std::cout << "       strtoll: ";
	if (sizeof(T) > sizeof(long long))
		std::cout << "SKIPPED" << std::endl;
	else if (checkResults(strings, strtoll_convert<T>))
		time_run<T>(strings, strtoll_convert<T>, samples);
	else
		std::cout << "FAILURE" << std::endl;

	std::cout << "         stoll: ";
	if (sizeof(T) > sizeof(long long))
		std::cout << "SKIPPED" << std::endl;
	else if (checkResults(strings, stoll_convert<T>))
		time_run<T>(strings, stoll_convert<T>, samples);
	else
		std::cout << "FAILURE" << std::endl;

	std::cout << "     handcoded: ";
	if (checkResults(strings, handcoded_convert<T>))
		time_run<T>(strings, handcoded_convert<T>, samples);
	else
		std::cout << "FAILURE" << std::endl;


	std::cout << "        hybrid: ";
	if (checkResults(strings, hybrid_convert<T>))
		time_run<T>(strings, hybrid_convert<T>, samples);
	else
		std::cout << "FAILURE" << std::endl;

}

//////////////////////////////////////////////////////////////////////
int main(int, char **)
{
	benchmark<int8_t>();
	benchmark<short>();
	benchmark<int>();
	benchmark<long>();
	benchmark<long long>();

	return 0;
}