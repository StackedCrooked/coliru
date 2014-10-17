#include <iosfwd>
#include <string>
#include <tuple>
#include <type_traits>
#include <locale>
#include <cstddef>

template<typename Char, typename Trait>
struct stream_state {
    using ostream_type = std::basic_ostream<Char, Trait>;
    using istream_type = std::basic_istream<Char, Trait>;
    std::streamsize width;
    std::streamsize precision;
    std::ios_base::fmtflags flags;
    Char fill;

    stream_state() = default;
    stream_state(const stream_state&) = default;

    template<typename Stream>
    stream_state(const Stream& s): width(s.width()), precision(s.precision()), flags(s.flags()), fill(s.fill()) {}

    template<typename Stream>
    void apply(Stream& s) {
        s.width(width);
        s.precision(precision);
        s.flags(flags);
        s.fill(fill);
    }
};

namespace detail {
template<size_t... Indices>
struct indices {};

template<size_t N, size_t... Indices>
struct build_indices : build_indices<N-1, N-1, Indices...> {};

template<size_t... Indices>
struct build_indices<0, Indices...> : indices<Indices...> {};

template<typename Char, typename Trait>
struct printer {
private:
    std::basic_ostream<Char, Trait>& out;
public:
    printer(std::basic_ostream<Char, Trait>& out): out(out) {}

    template<typename T>
    void operator()(T&& t) const {
        out << std::forward<T>(t);
    }
};

template<typename Tuple, typename Function>
inline void apply_impl(const Tuple&, size_t, const Function&, indices<>) {
    throw std::out_of_range("tuple index is out of bounds");
}

template<size_t N, size_t... Tail, typename Tuple, typename Function>
inline void apply_impl(const Tuple& tuple, size_t index, const Function& f, indices<N, Tail...>) {
    if(index == N) {
        f(std::get<N>(tuple));
    }
    else {
        apply_impl(tuple, index, f, indices<Tail...>{});
    }
}

template<typename Tuple, typename Function>
inline void apply(const Tuple& tuple, size_t index, const Function& f) {
    apply_impl(tuple, index, f, build_indices<std::tuple_size<Tuple>::value>{});
}

template<typename Char, typename Locale>
inline size_t parse_integer(const Char*& str, const Char zero, const Locale& loc) {
    size_t result = 0;
    while(*str && std::isdigit(*str, loc)) {
        result = (result * 10) + (*str++ - zero);
    }
    return result;
}

template<typename Char, typename Trait, typename... Args>
inline void fprint(std::basic_ostream<Char, Trait>& out, const Char* str, Args&&... arguments) {
    // %[parameter][flags][width][.precision]verb
    // if it's *n$ instead of %n$ then it'll use the specific parameter number
    // n starts at 1 to sizeof...(Args)
    // at the moment I'm too lazy to do * at all.
    auto&& args = std::make_tuple(std::forward<Args>(arguments)...);
    stream_state<Char, Trait> original{out};
    stream_state<Char, Trait> changed;
    printer<Char, Trait> func(out);
    const Char percent = out.widen('%');
    const Char zero    = out.widen('0');
    auto&& loc = out.getloc();
    size_t index = 0;
    size_t position = 0;
    bool has_positional = false;

    while(*str != 0) {
        // not a %
        if(!Trait::eq(*str, percent)) {
            out << *str++;
            continue;
        }

        // at this point -- *str == '%'
        // so just increment it to get to the format-spec
        ++str;

        // escaped %
        if(*str && Trait::eq(*str, percent)) {
            out << percent;
            ++str;
            continue;
        }

        // beginning of format-spec
        changed = original;

        // check for [parameter], i.e. n$
        // or a numeric value for [width]
        position = parse_integer(str, zero, loc);

        // check if it's [parameter] rather than [width]
        if(Trait::eq(*str, out.widen('$'))) {
            has_positional = true;
            ++str;
        }

        // check for [flags]
        // they are as follows:
        // +       - equivalent to std::showpos
        // -       - left aligns instead of right align, i.e. std::left
        // 0       - pad with 0s instead of spaces
        // '[char] - pad with [char] instead of spaces
        while(*str) {
            if(Trait::eq(*str, out.widen('+'))) {
                changed.flags |= out.showpos;
            }
            else if(Trait::eq(*str, out.widen('-'))) {
                changed.flags |= out.left;
            }
            else if(Trait::eq(*str, out.widen('0'))) {
                changed.fill = out.widen('0');
            }
            else if(Trait::eq(*str, out.widen('\''))) {
                // the next character is unconditionally the fill character
                changed.fill = *(++str);
            }
            else {
                // unknown flag, so just exit
                break;
            }
            ++str;
        }

        // check for [width]
        changed.width = parse_integer(str, zero, loc);

        // check for [precision]
        if(Trait::eq(*str, out.widen('.'))) {
            changed.precision = parse_integer(++str, zero, loc);
        }


        size_t final_index = has_positional ? position - 1 : index++;

        // check for verb
        if(Trait::eq(*str, out.widen('s')) || Trait::eq(*str, out.widen('c'))) {
            // do nothing since these don't add any extra format specifiers.
            // many of these are provided as a thin compatibility layer for
            // the original printf -- albeit strict compatibility is not a requirement here.
        }
        else if(Trait::eq(*str, out.widen('f')) || Trait::eq(*str, out.widen('F'))) {
            changed.flags |= out.fixed;
        }
        else if(Trait::eq(*str, out.widen('e'))) {
            changed.flags |= out.scientific;
        }
        else if(Trait::eq(*str, out.widen('E'))) {
            changed.flags |= out.scientific;
            changed.flags |= out.uppercase;
        }
        else if(Trait::eq(*str, out.widen('g'))) {
            changed.flags &= ~out.floatfield;
        }
        else if(Trait::eq(*str, out.widen('G'))) {
            changed.flags &= ~out.floatfield;
            changed.flags |= out.uppercase;
        }
        else if(Trait::eq(*str, out.widen('x')) || Trait::eq(*str, out.widen('p'))) {
            changed.flags |= out.hex;
        }
        else if(Trait::eq(*str, out.widen('X'))) {
            changed.flags |= out.hex;
            changed.flags |= out.uppercase;
        }
        else if(Trait::eq(*str, out.widen('d')) || Trait::eq(*str, out.widen('i')) || Trait::eq(*str, out.widen('u'))) {
            changed.flags |= out.dec;
        }
        else if(Trait::eq(*str, out.widen('o'))) {
            changed.flags |= out.oct;
        }
        else {
            std::string error = "invalid verb given ";
            auto narrowed = out.narrow(*str, 0x00);
            if(narrowed == 0x00) {
                error.push_back('\'');
                error.push_back(narrowed);
                error.push_back('\'');
            }
            else {
                error.append(" (unable to convert to char)");
            }
            throw std::runtime_error(error);
        }

        changed.apply(out);
        apply(args, final_index, func);
        original.apply(out);

        ++str;
    }
}
} // detail


template<typename Char, typename Trait, typename... Args>
inline void fprint(std::basic_ostream<Char, Trait>& out, const std::basic_string<Char, Trait>& str, Args&&... arguments) {
    detail::fprint(out, str.c_str(), std::forward<Args>(arguments)...);
}

template<typename Char, typename Trait, typename... Args>
inline void fprint(std::basic_ostream<Char, Trait>& out, const Char* str, Args&&... arguments) {
    detail::fprint(out, str, std::forward<Args>(arguments)...);
}

#include <iostream>

int main() {
    int x = 10;
    fprint(std::cout, "%.2f%%", static_cast<float>(x));
}
