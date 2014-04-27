#include <boost/fusion/adapted/struct.hpp>
#include <boost/spirit/include/qi.hpp>
#include <fstream>

namespace qi = boost::spirit::qi;

namespace Ast
{
    enum Command  { NO_CMD, TARGET, SENSOR, PAIR };
    enum Modifier { NO_MODIFIER, ON, OFF, ERASE };

    struct ModifiedCommand
    {
        Command cmd  = NO_CMD;
        Modifier mod = NO_MODIFIER;
    };

    struct OtherCommand
    {
        std::string token;
        OtherCommand(std::string token = "") : token(std::move(token))
        { }
    };

    typedef boost::variant<int, double> Operand;

    typedef boost::variant<Operand, ModifiedCommand, OtherCommand> RpnMachineInstruction;
    typedef std::vector<RpnMachineInstruction> RpnMachineProgram;

    // for printing, you can adapt this to execute the stack instead
    struct Print : boost::static_visitor<std::ostream&>
    {
        Print(std::ostream& os) : os(os) {}
        std::ostream& os;

        std::ostream& operator()(Ast::Command cmd) const {
            switch(cmd) {
                case TARGET: return os << "TARGET" << " ";
                case SENSOR: return os << "SENSOR" << " ";
                case PAIR:   return os << "PAIR"   << " ";
                case NO_CMD: return os << "NO_CMD" << " ";
                default:     return os << "#INVALID_COMMAND#" << " ";
            }
        }

        std::ostream& operator()(Ast::Modifier mod) const {
            switch(mod) {
                case ON:          return os << "[ON]"          << " ";
                case OFF:         return os << "[OFF]"         << " ";
                case ERASE:       return os << "[ERASE]"       << " ";
                case NO_MODIFIER: return os << "[NO_MODIFIER]" << " ";
                default:    return os << "#INVALID_MODIFIER#" << " ";
            }
        }

        std::ostream& operator()(double d) const { return os << "double:" << d << " "; }
        std::ostream& operator()(int    i) const { return os << "int:"    << i << " "; }

        std::ostream& operator()(Ast::OtherCommand const& cmd) const {
            return os << "'" << cmd.token << "'\n";
        }

        std::ostream& operator()(Ast::ModifiedCommand const& cmd) const {
            (*this)(cmd.cmd);
            (*this)(cmd.mod);
            return os << "\n"; 
        }

        template <typename... TVariant>
        std::ostream& operator()(boost::variant<TVariant...> const& v) const { 
            return boost::apply_visitor(*this, v); 
        }
    };

}

BOOST_FUSION_ADAPT_STRUCT(Ast::ModifiedCommand, (Ast::Command, cmd)(Ast::Modifier, mod))

template <typename It, typename Skipper = qi::space_type>
struct RpnGrammar : qi::grammar<It, Ast::RpnMachineProgram(), Skipper>
{
    RpnGrammar() : RpnGrammar::base_type(_start)
    {
        _command.add("TARGET", Ast::TARGET)("SENSOR", Ast::SENSOR)("PAIR", Ast::PAIR);
        _modifier.add("ON", Ast::ON)("OFF", Ast::OFF)("ERASE", Ast::ERASE);

        _start         = *_instruction;
        _instruction   = _operand | _mod_command | _other_command;

        _operand       = _strict_double | qi::int_;

        _mod_command   = _command >> _modifier;
        _other_command = qi::as_string [ +qi::char_("A-Z") ];
    }

  private:
    qi::rule<It, Ast::RpnMachineProgram(),     Skipper> _start;
    qi::rule<It, Ast::RpnMachineInstruction(), Skipper> _instruction;
    qi::rule<It, Ast::ModifiedCommand(),       Skipper> _mod_command;
    qi::rule<It, Ast::Operand(),               Skipper> _operand;

    // note: omitting the Skipper has the same effect as wrapping with `qi::lexeme`
    qi::rule<It, Ast::OtherCommand()> _other_command;

    qi::real_parser<double, boost::spirit::qi::strict_real_policies<double> > _strict_double;
    qi::symbols<char, Ast::Command>  _command;
    qi::symbols<char, Ast::Modifier> _modifier;
};

int main()
{
    std::ifstream ifs("input.txt");
    typedef boost::spirit::istream_iterator It;
    ifs.unsetf(std::ios::skipws);

    RpnGrammar<It> grammar;

    It f(ifs), l;
    Ast::RpnMachineProgram program;
    bool ok = qi::phrase_parse(f, l, grammar, qi::space, program);

    if (ok)
    {
        std::cout << "Parse succeeded, " << program.size() << " stack instructions\n";
        std::for_each(
                program.begin(),
                program.end(),
                Ast::Print(std::cout));
    }
    else
    {
        std::cout << "Parse failed\n";
    }

    if (f != l)
    {
        std::cout << "Remaining unparsed: '" << std::string(f,l) << "'\n";
    }
}
