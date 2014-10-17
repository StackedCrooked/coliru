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


template<typename T>
struct extractor {
private:
    T& val;
public:
    extractor(T& val): val(val) {}

    template<typename U, typename std::enable_if<std::is_constructible<T, U>::value, int>::type = 0>
    void operator()(U&& t) const noexcept {
        val = std::forward<U>(t);
    }

    template<typename U, typename std::enable_if<!std::is_constructible<T, U>::value, int>::type = 0>
    void operator()(U&&) const noexcept {}
};

template<typename T>
inline extractor<T> make_extractor(T& t) {
    return { t };
}

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
    size_t temp_pos = 0;
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
        has_positional = false;

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
        // #       - enables std::showbase
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
            else if(Trait::eq(*str, out.widen('#'))) {
                changed.flags |= out.showbase;
            }
            else {
                // unknown 'flag', so just exit
                break;
            }
            ++str;
        }

        // check for [width]
        // see if it's a variable width specifier
        if(Trait::eq(*str, out.widen('*'))) {
            ++str;
            // check if it's a positional argument i.e. *n$
            temp_pos = parse_integer(str, zero, loc);
            // verify that it is in fact a positional argument
            if(temp_pos != 0 && *str && Trait::eq(*str, out.widen('$'))) {
                apply(args, temp_pos - 1, make_extractor(changed.width));
                ++str;
            }
            else {
                apply(args, index++, make_extractor(changed.width));
            }
        }
        else {
            changed.width = parse_integer(str, zero, loc);
        }

        // check for [precision]
        if(Trait::eq(*str, out.widen('.'))) {
            ++str;
            // variable precision?
            if(Trait::eq(*str, out.widen('*'))) {
                ++str;
                // check for *n$
                temp_pos = parse_integer(str, zero, loc);
                if(temp_pos != 0 && *str && Trait::eq(*str, out.widen('$'))) {
                    apply(args, temp_pos - 1, make_extractor(changed.precision));
                    ++str;
                }
                else {
                    apply(args, index++, make_extractor(changed.precision));
                }
            }
            else {
                changed.precision = parse_integer(++str, zero, loc);
            }
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
#include <cmath>

int main() {
    fprint(std::cout, "Strings:\n");

    const char* s = "Hello";
    fprint(std::cout, "\t.%10s.\n\t.%-10s.\n\t.%*s.\n", s, s, 10, s);

    fprint(std::cout, "Characters:\t%c %%\n", 'A');

    fprint(std::cout, "Integers\n");
    fprint(std::cout, "Decimal:\t%i %d %.6i %i %.0i %+i %u\n", 1, 2, 3, 0, 0, 4, -1);
    fprint(std::cout, "Hexadecimal:\t%x %x %X %#x\n", 5, 10, 10, 6);
    fprint(std::cout, "Octal:\t%o %#o %#o\n", 10, 10, 4);

    fprint(std::cout, "Floating point\n");
    fprint(std::cout, "Rounding:\t%f %.0f %.32f\n", 1.5, 1.5, 1.3);
    fprint(std::cout, "Padding:\t%05.2f %.2f %5.2f\n", 1.5, 1.5, 1.5);
    fprint(std::cout, "Scientific:\t%E %e\n", 1.5, 1.5);
    fprint(std::cout, "Special values:\t0/0=%g 1/0=%g\n", NAN, INFINITY);

    fprint(std::cout, "Variable width control:\n");
    fprint(std::cout, "right-justified variable width: '%*c'\n", 5, 'x');
    fprint(std::cout, "left-justified variable width : '%*c'\n", -5, 'x');
}
