#define BOOST_SPIRIT_USE_PHOENIX_V3
//#define BOOST_SPIRIT_DEBUG

#include <boost/fusion/adapted.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp> // for debug output/streaming
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>

namespace qi = boost::spirit::qi;
namespace phx= boost::phoenix;

namespace wavefront { namespace obj
{
} }

namespace blender { namespace mtl // material?
{
    struct Ns { int exponent; }; // specular exponent
    struct Reflectivity { double r, g, b; };

    using Name = std::string;
    using Ka   = Reflectivity;
    using Kd   = Reflectivity;
    using Ks   = Reflectivity;

    using dissolve_factor = double;
    enum class illumination_model {
            color,          // 0     Color on and Ambient off
            color_ambient,  // 1     Color on and Ambient on
            highlight,      // 2     Highlight on
            reflection_ray, // 3     Reflection on and Ray trace on
            glass_ray,      // 4     Transparency: Glass on
                            //       Reflection: Ray trace on
            fresnel_ray,    // 5     Reflection: Fresnel on and Ray trace on
            refract_ray,    // 6     Transparency: Refraction on
                            //       Reflection: Fresnel off and Ray trace on
            refract_ray_fresnel,// 7 Transparency: Refraction on
                            //       Reflection: Fresnel on and Ray trace on
            reflection,     // 8     Reflection on and Ray trace off
            glass,          // 9     Transparency: Glass on
                            //       Reflection: Ray trace off
            shadow_invis,   // 10    Casts shadows onto invisible surfaces
    };

    struct material
    {
        Name                                _Name;
        boost::optional<Ns>                 _Ns;
        boost::optional<Reflectivity>       _Ka;
        boost::optional<Reflectivity>       _Kd;
        boost::optional<Reflectivity>       _Ks;
        boost::optional<dissolve_factor>    _d;
        boost::optional<illumination_model> _illum;
    };

    using mtl_file = std::vector<material>;

    ///////////////////////////////////////////////////////////////////////
    // Debug output helpers
    std::ostream& operator<<(std::ostream& os, blender::mtl::illumination_model o)
    {
        using blender::mtl::illumination_model;
        switch(o)
        {
            case illumination_model::color:               return os << "0(Color on and Ambient off)";
            case illumination_model::color_ambient:       return os << "1(Color on and Ambient on)";
            case illumination_model::highlight:           return os << "2(Highlight on)";
            case illumination_model::reflection_ray:      return os << "3(Reflection on and Ray trace on)";
            case illumination_model::glass_ray:           return os << "4(Transparency: Glass on/Reflection: Ray trace on)";
            case illumination_model::fresnel_ray:         return os << "5(Reflection: Fresnel on and Ray trace on)";
            case illumination_model::refract_ray:         return os << "6(Transparency: Refraction on/Reflection: Fresnel off and Ray trace on)";
            case illumination_model::refract_ray_fresnel: return os << "7(Transparency: Refraction on/Reflection: Fresnel on and Ray trace on)";
            case illumination_model::reflection:          return os << "8(Reflection on and Ray trace off)";
            case illumination_model::glass:               return os << "9(Transparency: Glass on/Reflection: Ray trace off)";
            case illumination_model::shadow_invis:        return os << "10(Casts shadows onto invisible surfaces)";
            default: return os << "ILLEGAL VALUE";
        }
    }

    std::ostream& operator<<(std::ostream& os, blender::mtl::Reflectivity const& o)
    {
        return os << "{r:" << o.r << ",g:" << o.g << ",b:" << o.b << "}";
    }

    std::ostream& operator<<(std::ostream& os, blender::mtl::material const& o)
    {
        using namespace boost::spirit::karma;
        return os << format("material {"
                   "\n\tNs:"    << (auto_  | "(unspecified)")
                << "\n\tKa:"    << (stream | "(unspecified)")
                << "\n\tKd:"    << (stream | "(unspecified)")
                << "\n\tKs:"    << (stream | "(unspecified)")
                << "\n\td:"     << (stream | "(unspecified)")
                << "\n\tillum:" << (stream | "(unspecified)")
                << "\n}", o);
    }
} }

BOOST_FUSION_ADAPT_STRUCT(blender::mtl::Reflectivity,(double, r)(double, g)(double, b))
BOOST_FUSION_ADAPT_STRUCT(blender::mtl::Ns, (int, exponent))
BOOST_FUSION_ADAPT_STRUCT(blender::mtl::material,
        (boost::optional<blender::mtl::Ns>, _Ns)
        (boost::optional<blender::mtl::Ka>, _Ka)
        (boost::optional<blender::mtl::Kd>, _Kd)
        (boost::optional<blender::mtl::Ks>, _Ks)
        (boost::optional<blender::mtl::dissolve_factor>, _d)
        (boost::optional<blender::mtl::illumination_model>, _illum))

namespace blender { namespace mtl { namespace parsing
{
    template <typename It>
        struct grammar : qi::grammar<It, qi::blank_type, mtl_file()>
    {
        template <typename T=qi::unused_type> using rule = qi::rule<It, qi::blank_type, T>;

        rule<Name()>               _Name;
        rule<Ns()>                 _Ns;
        rule<Reflectivity()>       _Ka;
        rule<Reflectivity()>       _Kd;
        rule<Reflectivity()>       _Ks;
        rule<dissolve_factor()>    _d;
        rule<illumination_model()> _illum;

        rule<mtl_file()> start;
        rule<material()> _material;
        rule<void(material&)> statement;
        rule<> comment;

        grammar() : grammar::base_type(start)
        {
            using namespace qi;
            using phx::bind;
            using blender::mtl::material;

            _Name    = "newmtl" >> lexeme [ +graph ];
            _Ns      = "Ns"     >> double_;
            _Ka      = "Ka"     >> double_ >> double_ >> double_;
            _Kd      = "Kd"     >> double_ >> double_ >> double_;
            _Ks      = "Ks"     >> double_ >> double_ >> double_;
            _d       = "d"      >> double_;
            _illum  %= "illum"  >> qi::int_ [ _pass = (_1>=0) && (_1<=10) ];

            comment  = '#' >> *(char_ - eol);

            statement=
                     comment
                   | _Ns    [ bind(&material::_Ns, _r1) = _1 ]
                   | _Ka    [ bind(&material::_Ka, _r1) = _1 ]
                   | _Kd    [ bind(&material::_Kd, _r1) = _1 ]
                   | _Ks    [ bind(&material::_Ks, _r1) = _1 ]
                   | _d     [ bind(&material::_d,  _r1) = _1 ]
                   | _illum [ bind(&material::_illum, _r1) = _1 ]
                   ;

            _material = -comment % eol
                    >> _Name [ bind(&material::_Name, _val) = _1 ] >> eol
                    >> -statement(_val) % eol;

            start = _material % -eol;

//          BOOST_SPIRIT_DEBUG_NODES(
//                  (start)
//                  (statement)
//                  (_material)
//                  (_Name) (_Ns) (_Ka) (_Kd) (_Ks) (_d) (_illum)
//                  (comment))
        }

};

} } }

#include <fstream>

template <typename T>
void dump(T const& data)
{
    using namespace boost::spirit::karma;
    std::cout << __PRETTY_FUNCTION__
        << "\n-----\n"
        << format(stream % eol, data)
        << "\n-----\n";
}

void testMtl(const char* const fname)
{
    std::ifstream mtl(fname, std::ios::binary);
    mtl.unsetf(std::ios::skipws);
    boost::spirit::istream_iterator f(mtl), l;

    using namespace blender::mtl::parsing;
    static const grammar<decltype(f)> p;

    blender::mtl::mtl_file data;
    bool ok = qi::phrase_parse(f, l, p, qi::blank, data);

    std::cout << "phrase_parse -> " << std::boolalpha << ok << "\n";
    std::cout << "remaining input: '" << std::string(f,l) << "'\n";

    dump(data);
}

int main()
{
    testMtl("untitled.mtl");
}
