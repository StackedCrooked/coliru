#include <string>
#include <functional>
#include <cstdio>

struct Option
{
    enum Flags : unsigned {
        none        = 0,
        exitSuccess = 1,
        exitFailure = (1 << 1),
        onlyOnce    = (1 << 2),
    };

    enum class Arg {
        none,
        optional,
        required,
        optionalList,
        list,
    };

    Arg argType;
    unsigned flags;
    char shortOpt;
    std::string longOpt;
    std::string argText;
    std::string longHelp;
    std::function<void(const char *)> action;
};

namespace std {
 template<> struct hash<Option> {
    typedef Option argument_type;
    typedef std::size_t value_type;

    static const std::hash<std::string> strHash;
    static const std::hash<char> charHash;

    value_type operator () (const argument_type & arg) const;
 };
}

namespace std {
 hash<Option>::value_type hash<Option>::operator () (const argument_type & arg) const
    { return (arg.longOpt.length() ? strHash(arg.longOpt)
                                   : charHash(arg.shortOpt)); }
  
   const hash<std::string> hash<Option>::strHash;
   const hash<char> hash<Option>::charHash;
}

main(int, char **)
{
    Option x;
    x.shortOpt = 'h';
    x.longOpt = "help";
    std::hash<Option> f;
    printf("%zx\n", f(x));
    return 0;
}