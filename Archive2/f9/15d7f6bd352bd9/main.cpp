# include <cstddef>
# include <ctime>
# include <string>
# include <sstream>
# include <chrono>
# include <thread>
# include <iomanip>
# include <iostream>


namespace
{
std::size_t tPrintf(const char * format)           // base function
{   std::cout << format;
    return 0;
}

template <typename T, typename ... Args>    // recursive variadic function
std::size_t tPrintf(const char * format, const T & value, const Args & ... args)
{   for ( ; *format != 0; ++format)
    {   if (*format == '%')
        {   std::cout << value;
            return tPrintf(format + 1, args...) + 1; // recursive call
        }
        std::cout << *format;
    }
    std::cerr << "** WARNING ** tPrintf(): skipping "
            << 1 + sizeof...(args)
            << " extra argument(s)." << std::endl;
    return 0;
}

template <typename ... Args>
void tPrintfNoisy(const char * format, const Args & ... args)
{   std::cout << "$\tNoisy: accepted " << sizeof...(args) << " argument(s).\n";
    const auto nPrinted = tPrintf(format, args...);
    std::cout << "$\tNoisy: printed  " << nPrinted
            << " argument(s)." << std::endl;
}

void printDelimiter()
{   std::cout << "\n-------------------------------------------\n" << std::endl;
}

# define STD_put_time_available (! defined __GLIBCXX__)
std::string getCurrentTime()
{   const std::time_t timeT = std::time(0);
    const std::tm * const timeStruct = std::localtime(& timeT);
    const char * const timeFormat = "%c %Z";
# if STD_put_time_available
    std::ostringstream os;
    os << "[C++] " << std::put_time(timeStruct, timeFormat);
    return os.str();
# else
    char buffer[1000];
    std::strftime(buffer, sizeof(buffer), timeFormat, timeStruct);
    return std::string("[C] ") + buffer;
# endif
}

} // }END namespace

int main()
{   using Clock = std::chrono::steady_clock;
    const auto startTime = Clock::now();

    tPrintfNoisy("% world% %\n%\t- %\n",
            "Hello", '!', 123,
            2e-7L, 244, "u");
    printDelimiter();

    tPrintfNoisy("");
    printDelimiter();

    tPrintfNoisy("", 1, 2, 3);
    printDelimiter();

    tPrintfNoisy("%%%%%%%%%");
    printDelimiter();

    std::string currentTimeString = getCurrentTime();
    const auto endTime = Clock::now();
    using namespace std::literals::string_literals;
    tPrintfNoisy("thread id: %; current time: (%); % microseconds elapsed.\n"
                    "%\n",
            std::this_thread::get_id(),
            getCurrentTime(),
            std::chrono::duration_cast<
                    std::chrono::microseconds>(endTime - startTime).count(),
            "sample std_string - "s + std::to_string(1E+22),
            "dummy", 5);
}
