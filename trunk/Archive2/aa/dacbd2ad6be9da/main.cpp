//#define BOOST_SPIRIT_DEBUG
#include <boost/fusion/adapted/struct.hpp>
#include <boost/spirit/include/qi.hpp>
#include <map>

namespace qi = boost::spirit::qi;

namespace ast {

    struct nil {
        friend std::ostream& operator<<(std::ostream& os, nil) { return os << "<nil>"; }
    };

    using value = boost::variant<nil, double, std::string>;

    struct parameter {
        std::string _key;
        value       _val;
    };

    enum class action {
        get, 
        set,
    };

    using parameters = std::vector<parameter>;

    struct packet {
        action      _action;
        parameters  _params;
    };

    using packets = std::vector<packet>;

    static std::ostream& operator<<(std::ostream& os, action a) { 
        switch(a) {
            case action::get: return os << "GET"; 
            case action::set: return os << "SET"; 
        }
        return os << "(other)"; 
    }
}

BOOST_FUSION_ADAPT_STRUCT(ast::parameter,(std::string,_key)(ast::value,_val))
BOOST_FUSION_ADAPT_STRUCT(ast::packet,(ast::action,_action)(ast::parameters,_params))

template <typename It, typename Skipper=qi::space_type>
   struct grammar : qi::grammar<It, ast::packets(), Skipper> {

       grammar():grammar::base_type(start) {
           using qi::raw;
           using qi::no_case;

           param_key_.add
               ("delay")
               ("mode");

           start      = *(packet_ >> ';');

           packet_    = 
               (no_case["get"] >> qi::attr(ast::action::get) >> *(',' >> get_param_))
             | (no_case["set"] >> qi::attr(ast::action::set) >> *(',' >> set_param_))
             ;

           get_param_ = raw[no_case[param_key_]] >> qi::attr(ast::value());
           set_param_ = raw[no_case[param_key_]] >> "," >> value_;

           value_     = qi::double_ | string_;
           string_    = '"' >> *~qi::char_('"') >> '"';

           BOOST_SPIRIT_DEBUG_NODES((start)(packet_)(get_param_)(set_param_)(value_)(string_))
       }

    private:

       qi::symbols<char, std::string> param_key_;
       qi::rule<It, ast::parameter(), Skipper> set_param_, get_param_;
       qi::rule<It, ast::packets(),   Skipper> start;
       qi::rule<It, ast::packet(),    Skipper> packet_;
       qi::rule<It, ast::value(),     Skipper> value_;
       qi::rule<It, std::string()>             string_;
   };

struct request_context {

    std::map<std::string, ast::value> properties;

    request_context() 
        : properties { { "MODE", 2 }, { "DELAY", 300 } } // defaults
    {
    }

    boost::optional<ast::packet> process_request(ast::packet& packet) {
        switch (packet._action) {
            case ast::action::get:
                for(auto& param : packet._params) {
                    param._val = properties[param._key];
                }
                return packet;
            case ast::action::set:
                for(auto& param : packet._params) {
                    std::cout << "DEBUG: setting property '" << param._key << "' to value '" << param._val << "'\n";
                    properties[param._key] = param._val;
                }
                return boost::none;
            default:
                throw std::runtime_error("bad packet"); // TODO proper exception type
        };
    }
};

int main()
{
    for (std::string const input : {
            "GET,DELAY,MODE;" 
            "SET,DELAY,0,MODE,\"we can have string values too\";GET,MODE;SET,MODE,42;GET,MODE,DELAY;" 
            }) 
    {
        using It = std::string::const_iterator;
        It f(input.begin()), l(input.end());

        grammar<It> p;
        ast::packets parsed;
        bool ok = qi::phrase_parse(f,l,p,qi::space,parsed);

        if (ok) {
            std::cout << parsed.size() << " packets successfully parsed\n";

            request_context ctx;

            for(auto& packet : parsed)
            {
                auto response = ctx.process_request(packet);

                if (response) {
                    std::cout << "response: " << response->_action;
                    for(auto& kv : packet._params) {
                        std::cout << "," << kv._key << "," << kv._val;
                    }
                    std::cout << ";\n";
                }
            }
        } else {
            std::cout << "Parse error\n";
        }

        if (f!=l)
            std::cout << "Remaining unparsed input: '" << std::string(f,l) << "'\n";
    }
}
