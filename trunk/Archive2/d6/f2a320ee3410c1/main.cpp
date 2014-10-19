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
    Char fill;

    stream_state() = default;
    stream_state(const stream_state&) = default;

    template<typename Stream>
    stream_state(const Stream& s): width(s.width()), precision(s.precision()), fill(s.fill()) {}

    template<typename Stream>
    void apply(Stream& s) {
        s.width(width);
        s.precision(precision);
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

template<typename Char>
inline std::tuple<size_t, bool> parse_integer(const Char*& str, const Char zero, const std::locale& loc) {
    size_t result = 0;
    bool b = false;
    while(*str && std::isdigit(*str, loc)) {
        b = true;
        result = (result * 10) + (*str++ - zero);
    }
    return std::make_tuple(result, b);
}


template<typename Char, typename Trait, typename... Args>
inline void fprint(std::basic_ostream<Char, Trait>& out, const Char* str, Args&&... arguments) {
    // format-string ::= "|" <`parameter`> [":" `format-spec`] "|"
    // parameter     ::= <integer>
    // format-spec   ::= [`align`][`fill`][`width`]["." `precision`][`verb`]*
    // align         ::= "<" | ">" | "^"
    // fill          ::= "'" <any character>
    // width         ::= <integer> | "*" <integer>
    // precision     ::= <integer> | "*" <integer>
    // verb          ::= "f" | "e" | "g" | "x" | "b" | "o" | "d" | "u" | "p" | "t"
    auto&& args = std::make_tuple(std::forward<Args>(arguments)...);
    stream_state<Char, Trait> original{out};
    stream_state<Char, Trait> changed;
    auto&& original_flags = out.flags();
    printer<Char, Trait> func(out);
    const Char pipe = out.widen('|');
    const Char zero    = out.widen('0');
    auto&& loc = out.getloc();
    size_t position = 0;
    size_t temp_pos = 0;
    bool has_integer = false;

    while(*str != 0) {
        // not a |
        if(!Trait::eq(*str, pipe)) {
            out << *str++;
            continue;
        }

        // at this point -- *str == '|'
        // so just increment it to get to the format-spec
        ++str;

        // escaped | so format-spec is over
        if(*str && Trait::eq(*str, pipe)) {
            out << pipe;
            ++str;
            continue;
        }

        // actual beginning of format-spec
        changed = original;
        has_integer = false;

        // retrieve parameter
        std::tie(position, has_integer) = parse_integer(str, zero, loc);

        if(!has_integer) {
            throw std::runtime_error("numeric parameter expected");
        }

        // check if format spec exists
        if(*str && Trait::eq(*str, out.widen(':'))) {
            ++str;
            // check for [align]
            if(Trait::eq(*str, out.widen('<'))) {
                out.setf(out.left, out.adjustfield);
                ++str;
            }
            else if(Trait::eq(*str, out.widen('>'))) {
                out.setf(out.right, out.adjustfield);
                ++str;
            }
            else if(Trait::eq(*str, out.widen('^'))) {
                out.setf(out.internal, out.adjustfield);
                ++str;
            }

            // check for [fill]
            if(Trait::eq(*str, out.widen('\'')) && *(str + 1)) {
                ++str;
                changed.fill = *str;
                ++str;
            }

            // check for [width]
            if(Trait::eq(*str, out.widen('*'))) {
                ++str;
                std::tie(temp_pos, has_integer) = parse_integer(str, zero, loc);
                if(!has_integer) {
                    throw std::runtime_error("expected positional index after *");
                }
                apply(args, temp_pos, make_extractor(changed.width));
            }
            else {
                std::tie(changed.width, std::ignore) = parse_integer(str, zero, loc);
            }

            // check for [.precision]
            if(Trait::eq(*str, out.widen('.'))) {
                ++str;
                if(Trait::eq(*str, out.widen('*'))) {
                    ++str;
                    std::tie(temp_pos, has_integer) = parse_integer(str, zero, loc);
                    if(!has_integer) {
                        throw std::runtime_error("expected positional index after *");
                    }
                    apply(args, temp_pos, make_extractor(changed.precision));
                }
                else {
                    std::tie(changed.precision, std::ignore) = parse_integer(str, zero, loc);
                }
            }

            // check for [verbs]
            // they are as follows:
            // f  - Set std::fixed
            // e  - Set std::scientific
            // u  - Set std::uppercase
            // x  - Set std::hex
            // b  - Set std::showbase
            // o  - Set std::oct
            // d  - Set std::dec
            // t  - Set std::boolalpha
            // p  - Set std::showpoint
            // g  - Set std::defaultfloat

            while(*str) {
                if(Trait::eq(*str, out.widen('f'))) {
                    out.setf(out.fixed, out.floatfield);
                }
                else if(Trait::eq(*str, out.widen('e'))) {
                    out.setf(out.scientific, out.floatfield);
                }
                else if(Trait::eq(*str, out.widen('g'))) {
                    out.unsetf(out.floatfield);
                }
                else if(Trait::eq(*str, out.widen('u'))) {
                    out.setf(out.uppercase);
                }
                else if(Trait::eq(*str, out.widen('x'))) {
                    out.setf(out.hex, out.basefield);
                }
                else if(Trait::eq(*str, out.widen('o'))) {
                    out.setf(out.oct, out.basefield);
                }
                else if(Trait::eq(*str, out.widen('d'))) {
                    out.setf(out.dec, out.basefield);
                }
                else if(Trait::eq(*str, out.widen('b'))) {
                    out.setf(out.showbase);
                }
                else if(Trait::eq(*str, out.widen('t'))) {
                    out.setf(out.boolalpha);
                }
                else if(Trait::eq(*str, out.widen('p'))) {
                    out.setf(out.showpoint);
                }
                else {
                    // unknown flag
                    break;
                }
                ++str;
            }
        }

        if(*str && Trait::eq(*str, pipe)) {
            // apply the changes
            changed.apply(out);
            // print it out
            apply(args, position, func);
            // revert changed
            original.apply(out);
            ++str;
        }
        else {
            throw std::runtime_error("expected end of format string");
        }
    }

    out.flags(original_flags);
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
#include <iomanip>
#include <cmath>

int main() {
    unsigned x = 0xDEADBEEF;
    fprint(std::cout, "|0| and |0:x| and |0:xu|\n", x);
    fprint(std::cout, "|0:<'#*1| has a width of |1|", "Hello World", 15);
}
