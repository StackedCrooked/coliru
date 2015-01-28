#include <boost/spirit/include/qi.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>

#include <iostream>

namespace qi = boost::spirit::qi;
typedef boost::multiprecision::cpp_dec_float_50 Float;

int main()
{
    std::string const m_caracs("f21.0i51.24v58.65c47.3s5.54d57.68e54.23h24.42");

    Float m_sten, m_feal, m_felt, m_inte, m_sag, m_ende, m_asko, m_vit;

    //auto num = qi::as_string[qi::raw[qi::double_]]; // this would parse exponents like 57.68e54
    auto num = boost::proto::deep_copy(qi::as_string[+qi::char_("-+0-9.")]);
    if (qi::parse(m_caracs.begin(), m_caracs.end(),
                'f' >> num >> 'i' >> num >> 'v' >> num >>
                'c' >> num >> 's' >> num >> 'd' >> num >>
                'e' >> num >> 'h' >> num,
                m_sten, m_feal, m_felt, m_inte, m_sag, m_ende, m_asko, m_vit
             ))
    {
        std::cout <<
            'f' << m_sten <<
            'i' << m_feal <<
            'v' << m_felt <<
            'c' << m_inte <<
            's' << m_sag  <<
            'd' << m_ende <<
            "e" << m_asko <<
            'h' << m_vit  << '\n';
    }
}
