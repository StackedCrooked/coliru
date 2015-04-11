//#define BOOST_SPIRIT_DEBUG
#include <boost/fusion/adapted/struct.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/date_time/posix_time/posix_time_io.hpp>
#include <boost/optional/optional_io.hpp>

namespace qi = boost::spirit::qi;

#include <boost/date_time.hpp>
#include <boost/date_time/local_time/local_time.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/filesystem/operations.hpp>

namespace http {
    class datetime {
        using clock = boost::local_time::local_sec_clock;
        boost::local_time::local_date_time m_dt;
      public:
        datetime() : m_dt(clock::local_time(boost::local_time::time_zone_ptr())) {
        }

        friend std::ostream& operator<<(std::ostream& os, datetime const& o) {
            std::ostream imbued(os.rdbuf());
            imbued.imbue(std::locale(imbued.getloc(), new boost::local_time::local_time_facet("%a, %d %b %Y %H:%M:%S GMT")));
            imbued << o.m_dt;
            return os;
        }

        friend std::istream& operator>>(std::istream& is, datetime& o) {
            std::istream imbued(is.rdbuf());
            imbued.imbue(std::locale(std::locale::classic(), new boost::local_time::local_time_input_facet("%a, %d %b %Y %H:%M:%S GMT")));
            imbued >> o.m_dt;
            return is;
        }
    };
}

namespace ast {
    using boost::optional;
    using rfc1123date = http::datetime; // rfc1123 formatting

    struct expires_av {
        rfc1123date date;
        expires_av(rfc1123date date = {}) : date(date) {}
        friend std::ostream& operator<<(std::ostream& os, expires_av const& attr) {
            return os << "[ expires_av: " << attr.date << " ]";
        }
    };

    struct max_age_av {
        unsigned age;
        max_age_av(unsigned age = {}) : age(age) {}
        friend std::ostream& operator<<(std::ostream& os, max_age_av const& attr) {
            return os << "[ max_age_av: " << attr.age << " ]";
        }
    };
    struct string_attribute {
        std::string value;
        string_attribute(std::string value = "") : value(std::move(value)) {}
        friend std::ostream& operator<<(std::ostream& os, string_attribute const& attr) {
            return os << "[ string_attribute: " << attr.value << " ]";
        }
    };
    using domain_av = string_attribute;
    using path_av = string_attribute;
    using extension_av = string_attribute;

    struct cookie_av {
        optional<expires_av> expires;
        optional<max_age_av> max_age;
        optional<domain_av> domain;
        optional<path_av> path;
        bool secure   = false;
        bool httponly = false;
        optional<extension_av> extension;
    };

    struct cookie_pair {
        std::string name, value;
    };

    struct cookie {
        cookie_pair pair;
        cookie_av   attributes;
    };
}

BOOST_FUSION_ADAPT_STRUCT(ast::cookie_av,
        (optional<ast::expires_av>,expires)
        (optional<ast::max_age_av>,max_age)
        (optional<ast::domain_av>,domain)
        (optional<ast::path_av>,path)
        (bool,secure)
        (bool,httponly)
        (optional<ast::extension_av>,extension)
    )

BOOST_FUSION_ADAPT_STRUCT(ast::cookie_pair,
        (std::string, name)
        (std::string, value)
    )

BOOST_FUSION_ADAPT_STRUCT(ast::cookie,
        (ast::cookie_pair, pair)
        (ast::cookie_av, attributes)
    )

namespace ast {
    static inline std::ostream& operator<<(std::ostream& os, cookie_av   const&v) { return os << boost::fusion::as_vector(v); }
    static inline std::ostream& operator<<(std::ostream& os, cookie_pair const&v) { return os << boost::fusion::as_vector(v); }
    static inline std::ostream& operator<<(std::ostream& os, cookie      const&v) { return os << boost::fusion::as_vector(v); }
}

template <typename It>
struct set_cookie : qi::grammar<It, ast::cookie()> {
    set_cookie() : set_cookie::base_type(start) {
        using namespace qi;
        using boost::proto::deep_copy;

        /////////////////////////////////////////////////////////////////
        // RFC2616 2.2 token
#define RFC_CTLs "\x01-\x1f\x7f"
        constexpr char DQUOTE = '"';
        token = +(~char_(RFC_CTLs /*separators:*/ "()<>@,;:\\\"/[]?={} \t") - '\0');

        /////////////////////////////////////////////////////////////////
        // RFC6265 4.1.1. Syntax (set-cookie)

        set_cookie_header = no_case["set-cookie: "] >> set_cookie_string;
        set_cookie_string = cookie_pair >> -attributes;
        cookie_pair       = cookie_name >> '=' >> cookie_value;
        cookie_name       = token;
        auto cookie_octet = deep_copy(char_("\x21" "\x23-\x2B" "\x2D-\x3A" "\x3C-\x5B" "\x5D-\x7E"));
        cookie_value      = *cookie_octet | (DQUOTE >> *cookie_octet >> DQUOTE);
        //                     ; US-ASCII characters excluding CTLs,
        //                     ; whitespace DQUOTE, comma, semicolon,
        //                     ; and backslash

        attributes        = ("; " >> expires_av)
                          ^ ("; " >> max_age_av)
                          ^ ("; " >> domain_av)
                          ^ ("; " >> path_av)
                          ^ ("; " >> secure_av)
                          ^ ("; " >> httponly_av)
                          ^ ("; " >> extension_av)
                          ;
        expires_av        = no_case["expires="] >> sane_cookie_date;
        sane_cookie_date  = stream; // TODO <rfc1123_date, defined in [RFC2616], Section 3.3.1>
        max_age_av        = no_case["max-age="] >> !char_('0') >> uint_;
        //                     ; In practice, both expires_av and max_age_av
        //                     ; are limited to dates representable by the
        //                     ; user agent.
        // non_zero_digit    = %x31-39
        //                     ; digits 1 through 9
        domain_av         = no_case["domain="] >> domain_value;
        domain_value      = raw [ (alpha >> *(alpha|digit|'-')) % '.'];
        //                     ; defined in [RFC1034], Section 3.5, as
        //                     ; enhanced by [RFC1123], Section 2.1
        path_av           = no_case["path="] >> path_value;
        path_value        = *(~char_(RFC_CTLs ";") - '\0'); //  <any CHAR except CTLs or ";">
        secure_av         = no_case["secure"]   >> attr(true);
        httponly_av       = no_case["httponly"] >> attr(true);
        extension_av      = as_string [*(~char_(RFC_CTLs ";") - '\0')]; // <any CHAR except CTLs or ";">

        start = set_cookie_header;

        BOOST_SPIRIT_DEBUG_NODES(
                (start)
                (set_cookie_header) (set_cookie_string)
                (cookie_pair) (cookie_name) (cookie_value) (token)

                (attributes)
                (expires_av) (sane_cookie_date)
                (max_age_av)
                (domain_av)  (domain_value)
                (path_av)    (path_value)
                (secure_av)
                (httponly_av)
                (extension_av)
            );
#undef RFC_CTLs
    }
  private:
    qi::rule<It, ast::cookie()>       start;
    qi::rule<It, std::string()>       token, cookie_name, cookie_value, domain_value, path_value;

    qi::rule<It, ast::cookie()>       set_cookie_header, set_cookie_string;
    qi::rule<It, ast::cookie_pair()>  cookie_pair;

    qi::rule<It, ast::cookie_av()>    attributes;

    qi::rule<It, ast::expires_av()>   expires_av;
    qi::rule<It, ast::rfc1123date()>  sane_cookie_date;

    qi::rule<It, ast::max_age_av()>   max_age_av; // non_zero_digit;
    qi::rule<It, ast::domain_av()>    domain_av;
    qi::rule<It, ast::path_av()>      path_av;

    qi::rule<It, bool()>              secure_av, httponly_av;
    qi::rule<It, ast::extension_av()> extension_av;
};

int main() {
    using It = std::string::const_iterator;
    for (std::string const s : {
            "Set-Cookie: name=value",
            "Set-Cookie: name=value; Path=/; Domain=domain.com",
            "set-cookie: name=value; path=/; domain=domain.com",
            //// not actually rfc 6265 conformant:
            //"Set-Cookie: name=value;path=/;domain=domain.com",

            // actually a wednesday:
            "Set-Cookie: name=value; path=/; domain=.mydomain.com; expires=Thu, 01-Jan-2070 00:00:10 GMT; comment=no_comment"
            })
    {
        It f = s.begin(), l = s.end();
        std::cout << "Parsing '" << s << "'\n";

        ast::cookie cookie;
        bool ok = qi::parse(f,l,set_cookie<It>(),cookie);

        if (ok) {
            std::cout << " -- Parse success: " << cookie << "\n";
        }
        else
            std::cout << " -- Parse failure\n";

        if (f!=l)
            std::cout << " -- Remaining unparsed: '" << std::string(f,l) << "'\n";
    }
}
