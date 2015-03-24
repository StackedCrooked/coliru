# include <cstdarg>
# include <cstdio>
# include <limits>
# include <type_traits>
# include <string>
# include <stdexcept>
# include <iostream>


namespace
{
template <typename To, typename From>
To numericCast(From from)
{   if (std::numeric_limits<To>::lowest() > from ||
            std::numeric_limits<To>::max() < from)
    {   throw std::runtime_error("Invalid numeric cast.");
    }
    return static_cast<To>(from);
}

template <typename T>
void printLine(T value)
{   std::cout << value << std::endl;
}

# define NON_copyable 2
# define NON_movable 1

class Noisy
{
public:
    Noisy() = default; //: value(-13)
    //{ //  printLine("Default constructor");
    //}
    Noisy(int value) : value(value)
    {   printLine("Value constructor (" + std::to_string(value) + ')');
    }
# if NON_copyable == 1
    Noisy(const Noisy &) = delete;
    Noisy & operator=(const Noisy &) & = delete;
# elif NON_copyable == 0
    Noisy(const Noisy &)
    {   printLine("Copy constructor");
    }
    Noisy & operator=(const Noisy &) &
    {   printLine("Copy assignment operator");
        return *this;
    }
# endif
# if NON_movable == 1
    Noisy(Noisy &&) = delete;
    Noisy & operator=(Noisy &&) & = delete;
# elif NON_movable == 0
    Noisy(Noisy &&)
    {   printLine("Move constructor");
    }
    Noisy & operator=(Noisy &&) &
    {   printLine("Move assignment operator");
        return *this;
    }
# endif
# if NON_copyable != 2
    ~Noisy()
    {   printLine("Destructor");
    }
# endif
    int value;
};

void printLine(const Noisy & noisy)
{   std::cout << "Printing Noisy(" << noisy.value << ')' << std::endl;
}

void simplePrintf(const char * format, ...)
{   std::va_list args;
    va_start(args, format);
    while (*format != 0)
    {   switch (*format)
        {   case 'd':
                printLine(va_arg(args, int));
                break;
            case 'c':
                printLine(va_arg(args, char));
                break;
            case 'y':
                // note automatic conversion to integral type
                printLine(numericCast<char>(va_arg(args, int)));
                break;
            case 'f':
                printLine(va_arg(args, double));
                break;
            case 's':
                printLine(va_arg(args, const char *));
                break;
            case 'n':
                printLine(va_arg(args, Noisy));
                break;
            default:
                throw std::runtime_error(
                        std::string("Unknown format: ") + *format + '.');
        }
        ++format;
    }
    va_end(args);
}

} // }END namespace

int main()
{   simplePrintf("dyfffsyyndnn",
            3, 'a',
            1.999, 42.5, 24E-5,
            "my str", 'g', 126,
            Noisy{1}, Noisy{5}, Noisy(), Noisy(-8));

    std::printf("int:%d, double:%lf, float:%f, short:%hd, long:%ld\n",
                5, 4.2L, 4.2f,
                Noisy(-2), Noisy{-2},
                "extra", "arguments");
    std::printf("int?:%d\n");

    std::cout << "----!!----\n" << std::boolalpha;
    printLine(std::is_function<int()>           ::value);
    printLine(std::is_function<int(...)>        ::value);
    printLine(std::is_function<int(int...)>     ::value);
    printLine(std::is_function<int(int, ...)>   ::value);
    printLine(std::is_function<int>             ::value);
}
