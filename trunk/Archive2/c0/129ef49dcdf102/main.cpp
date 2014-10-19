#include <array>
#include <ostream>
#include <iostream>
#include <utility>

namespace ns {

// ersatzes for array_view/string_view
template<typename Type>
using view = std::pair<Type*, Type*>;
using string_view = view<char const>;

struct format_flags {
};

using emitter = std::streambuf;

using erased_formatter = void(*)(emitter&, void const* erased, format_flags const&);

void format1(emitter& emit, int, format_flags const&)
{
    auto const& message = "formatting an int!\n";
    emit.sputn(message, sizeof message - 1);
}

void format1(emitter& emit, double, format_flags const&)
{
    auto const& message = "formatting a double!\n";
    emit.sputn(message, sizeof message - 1);
}

struct erase_format1 {
    template<typename Arg>
    static constexpr void erased_format1(emitter& emit, void const* erased, format_flags const& flags)
    { return format1(emit, *static_cast<Arg const*>(erased), flags); }

    template<typename Arg>
    static constexpr erased_formatter value()
    { return static_cast<erased_formatter>(&erased_format1<Arg>); }
};

template<typename... Args>
constexpr std::array<erased_formatter, sizeof...(Args)> formatters_for()
{ return {{ erase_format1::value<Args>()... }}; }

// **************************
// Can be compiled separately
// **************************
void format(emitter& emit, string_view /*format_spec*/, view<erased_formatter const> formatters, view<void const* const> args)
{
    format_flags flags;
    formatters.first[0](emit, args.first[0], flags);
    formatters.first[1](emit, args.first[1], flags);
    emit.pubsync();
}

template<std::size_t N, typename... Args>
void format(const char(&format_spec)[N], Args const&... args)
{
    constexpr auto formatters = formatters_for<Args...>();
    std::array<void const*, sizeof...(Args)> const addresses = { &args... };
    format(*std::cout.rdbuf()
            , { format_spec, format_spec + (N - 1) }
            , { formatters.data(), formatters.data() + formatters.size() }
            , { addresses.data(), addresses.data() + addresses.size() } );
}

} // ns

int main()
{
    ns::format("irrelevant", 42, 84., 18);
}