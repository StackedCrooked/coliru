#include <boost/spirit/include/karma.hpp>
#include <complex>

namespace boost { namespace spirit { namespace traits {

    template <typename T>
        struct extract_from_attribute<typename std::complex<T>, boost::fusion::vector2<T, T>, void>
        {
            typedef boost::fusion::vector2<T,T> type;

            template <typename Context>
                static type call(std::complex<T> const& attr, Context& context)
                {
                    return { attr.real(), attr.imag() };
                }
        };

} } }

namespace karma = boost::spirit::karma;

int main()
{
    karma::rule<boost::spirit::ostream_iterator, boost::fusion::vector2<double, double>()> 
        static const rule = 
                            '(' << karma::double_ << ", " << karma::duplicate [ !karma::double_(0.0) << karma::double_ ] << ')' 
                          | karma::double_ << karma::omit [ karma::double_ ];

    std::vector<std::complex<double>> const values {
                { 123, 4 },
                { 123, 0 },
                { 123, std::numeric_limits<double>::infinity() },
                { std::numeric_limits<double>::quiet_NaN(), 0 },
                { 123, -1 },
            };

    std::cout << karma::format_delimited(*rule, '\n', values);
}
