// -- Noisy.hpp --
# include <string>
# include <iostream>

class Noisy
{
public:
    Noisy() : value_(-13)
    {   printThis("Default constructor");
    }
    Noisy(int value) : value_(value)
    {   printThis("Value constructor");
    }
    Noisy(const Noisy & other) : value_(other.value_)
    {   printThis("Copy constructor");
    }
    Noisy & operator=(const Noisy & other) &
    {   value_ = other.value_;
        printThis("Copy assignment operator");
        return *this;
    }
    Noisy(Noisy && other) : value_(other.value_)
    {   other.value_ = - value_;
        printThis("Move constructor");
    }
    Noisy & operator=(Noisy && other) &
    {   value_ = other.value_;
        other.value_ = - value_;
        printThis("Move assignment operator");
        return *this;
    }
    ~Noisy()
    {   printThis("Destructor");
    }

    int value() const noexcept
    {   return value_;
    }

private:
    void printThis(const std::string & message)
    {   std::cout << "$$ " << message + " (" + std::to_string(value_) + ')'
                << std::endl;
    }

    int value_;
};

struct AggressiveString
{   std::string value;
    AggressiveString() = default;
    AggressiveString(const char * value) : AggressiveString(std::string(value))
    {}
    AggressiveString(const std::string & value) : value(value)
    {}
    template <typename Number>
    AggressiveString(Number number) : value(std::to_string(number))
    {}
};
AggressiveString & operator+=(AggressiveString & a, const AggressiveString & b)
{   a.value += b.value;
    return a;
}
AggressiveString operator+(AggressiveString a, const AggressiveString & b)
{   return a += b;
}



// -- StreamOutput.hpp --
// # include "Noisy.hpp"
# include <ostream>

namespace FormattedOutput
{
inline void print(std::ostream & os, double number)
{   os << "double{" << number << '}';
}

inline void print(std::ostream & os, const Noisy & noisy)
{   os << "Noisy{" << noisy.value() << '}';
}

inline void print(std::ostream & os, const AggressiveString & s)
{   os << "AggressiveString{" << s.value << '}';
}
} // }END namespace FormattedOutput



# ifndef STD_OSTREAM_EXTENDABLE_FORMATTED_OUTPUT_HPP
# define STD_OSTREAM_EXTENDABLE_FORMATTED_OUTPUT_HPP

# include <ostream>

namespace FormattedOutput
{
template <typename Arg>
void print(std::ostream & os, const Arg & arg)
{   os << arg;
}

class Print
{
public:
    template <typename Arg1, typename ... Args>
    static void simple(std::ostream & os, const Arg1 & arg1,
                       const Args & ... args)
    {   print(os, arg1);
        simpleImpl(os, args...);
        os << std::endl;
    }

    template <typename Arg1, typename ... Args>
    static void sp(std::ostream & os, const Arg1 & arg1, const Args & ... args)
    {   print(os, arg1);
        spImpl(os, args...);
        os << std::endl;
    }

    Print() = delete;

private:
    static void simpleImpl(std::ostream &)
    {}

    template <typename Arg1, typename ... Args>
    static void simpleImpl(std::ostream & os, const Arg1 & arg1,
                           const Args & ... args)
    {   print(os, arg1);
        simpleImpl(os, args...);
    }

    static void spImpl(std::ostream &)
    {}

    template <typename Arg1, typename ... Args>
    static void spImpl(std::ostream & os, const Arg1 & arg1,
                       const Args & ... args)
    {   os << ' ';
        print(os, arg1);
        spImpl(os, args...);
    }
};

} // }END namespace FormattedOutput

# endif // STD_OSTREAM_EXTENDABLE_FORMATTED_OUTPUT_HPP



namespace FormattedOutput
{
inline void print(std::ostream & os, int number)
{   os << "int{" << number << '}';
}
} // }END namespace FormattedOutput



# ifndef ERROR_SS_HPP
# define ERROR_SS_HPP

// # include "StreamOutput/FormattedOutput.hpp"
# include <iostream>

namespace ErrorSs
{
inline constexpr const char * getPrefix() noexcept
{   return "** CRITICAL **";
}

template <typename ... Args>
void simple(const Args & ... args)
{   FormattedOutput::Print::simple(std::cerr, getPrefix(), ' ', args...);
}

template <typename ... Args>
void sp(const Args & ... args)
{   FormattedOutput::Print::sp(std::cerr, getPrefix(), args...);
}

template <typename ... Args>
struct Simple
{   void operator()(const Args & ... args) const
    {   simple(args...);
    }
};

template <typename ... Args>
struct Sp
{   void operator()(const Args & ... args) const
    {   sp(args...);
    }
};

} // }END namespace ErrorSs

# endif // ERROR_SS_HPP



# ifndef DEBUG_SS_HPP
# define DEBUG_SS_HPP

# ifdef ENABLE_DEBUG_SS

// # include "StreamOutput/FormattedOutput.hpp"
# include <iostream>

# define DEBUG_SS(...) \
    PRIVATE_DEBUG_SS_DISPATCH(FormattedOutput::Print::simple,   \
                                "@DEBUG_SS: ", __VA_ARGS__)

# define DEBUG_SS_SP(...) \
PRIVATE_DEBUG_SS_DISPATCH(FormattedOutput::Print::sp,           \
                            "@DEBUG_SS:", __VA_ARGS__)

# define PRIVATE_DEBUG_SS_DISPATCH(print, ...)  \
    do                                          \
    {   print(std::cout, __VA_ARGS__);          \
    } while (false)

# else // ENABLE_DEBUG_SS

# define DEBUG_SS(...) \
    do { } while (false)

# define DEBUG_SS_SP(...) \
    DEBUG_SS(__VA_ARGS__)

# endif // ENABLE_DEBUG_SS

# endif // DEBUG_SS_HPP



namespace FormattedOutput
{
inline void print(std::ostream & os, char symbol)
{   os << "char{" << symbol << '}';
}
} // }END namespace FormattedOutput

namespace
{
void customPrintPlacementTest();
void noisyTest();
void debugSsTest();
void variadicTest();
void cubicVariadicTest();
} // }END namespace

int main()
{   FormattedOutput::Print::simple(std::cout, 5);
    customPrintPlacementTest();
    noisyTest();
    debugSsTest();
    variadicTest();
    cubicVariadicTest();
}

# include <utility>
# include <string>
# include <iostream>

# define BEGIN_FUNCTION std::cout   << std::endl \
                                    << "[[[[[ " << __func__ << std::endl;

# define END_FUNCTION   std::cout   << "]]]]] " << __func__ << std::endl;

namespace
{
void customPrintPlacementTest()
{   BEGIN_FUNCTION
    ErrorSs::sp("D:", -7.77, "; I:", 42, "; C:", 'Q');

    FormattedOutput::print(std::cout, 1.4);
    FormattedOutput::print(std::cout, " ");
    FormattedOutput::print(std::cout, 77);
    FormattedOutput::print(std::cout, " ");
    FormattedOutput::print(std::cout, 'T');
    std::cout << std::endl;
    END_FUNCTION
}

void noisyTest()
{   BEGIN_FUNCTION
    Noisy a(5), b, c(42);
    ErrorSs::sp(a, b, c);
    Noisy d = a, e = std::move(b), f, g(-3);
    const auto printAll = [&]
    {   ErrorSs::sp(a, b, c, d, e, f, g);
    };
    printAll();
    f = std::move(d);
    g = b;
    printAll();
    END_FUNCTION
}

void debugSsTest()
{   BEGIN_FUNCTION
    // DEBUG_SS();
    DEBUG_SS("I'm a debug message. You'll not see me in the final release!");
    const std::string helloString("Hello there!");
    DEBUG_SS_SP(helloString, -5, 1E7 + 75.5, 'q', '$',
                " ! \t", "\\\n", Noisy());
    END_FUNCTION
}


template <typename ... Args>
void printPlus2(const Args & ... args)
{   FormattedOutput::Print::sp(std::cout, args + 2 ...);
}

void variadicTest()
{   BEGIN_FUNCTION
    printPlus2(24, 0.3, 'a', "POSIX", AggressiveString("added number: "));
    END_FUNCTION
}


inline AggressiveString combine()
{   return AggressiveString();
}
template <typename Arg1, typename ... Args>
AggressiveString combine(const Arg1 & arg, const Args & ... args)
{   return arg + combine(args...);
}

template <typename ... Args>
void cubicPrintPlus(Args && ... args)
{   FormattedOutput::Print::sp(std::cout,
        combine(combine(1 + args...) + 2 + args...) + 3 + args...);
}

void cubicVariadicTest()
{   BEGIN_FUNCTION
    cubicPrintPlus(AggressiveString{"A"}, AggressiveString{"B"});
    END_FUNCTION
}

} // }END namespace
