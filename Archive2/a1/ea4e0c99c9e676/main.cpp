#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/adapted/struct.hpp>
#include <boost/make_shared.hpp>
#include <boost/foreach.hpp>

struct CommandBase
{
    virtual void commandAction()
    {
        std::cout << "This is a base command. You should never see this!" << std::endl;
    }
    virtual ~CommandBase() = default;
};

struct CommandHolder
{
    CommandHolder() = default;
    template <typename Command> CommandHolder(Command cmd) 
        : storage(new concrete_store<Command>{ std::move(cmd) }) { }

    operator CommandBase&() { return storage->get(); }
  private:
    struct base_store {
        virtual ~base_store() {}; 
        virtual CommandBase& get() = 0;
    };
    template <typename T> struct concrete_store : base_store {
        concrete_store(T v) : wrapped(std::move(v)) { }
        virtual CommandBase& get() { return wrapped; }
      private:
        T wrapped; 
    };

    boost::shared_ptr<base_store> storage;
};

struct AnyCommand : CommandBase
{
    AnyCommand() = default;
    template <typename Command> AnyCommand(Command cmd) 
        : holder(std::move(cmd)) { }

    virtual void commandAction() override { 
        static_cast<CommandBase&>(holder).commandAction();
    }
  private:
    CommandHolder holder;
};

struct CommandTypeA : public CommandBase
{
    int valueA;
    int valueB;
    CommandTypeA() = default;
    CommandTypeA(int va, int vb) : valueA(va), valueB(vb) { }
    virtual void commandAction()
    {
        std::cout << "CommandType A! ValueA: " << valueA << " ValueB: " << valueB << std::endl;
    }
};

struct CommandTypeB : public CommandBase
{
    double valueA;
    std::string valueB;
    CommandTypeB() = default;
    CommandTypeB(double va, std::string vb) : valueA(va), valueB(std::move(vb)) { }
    virtual void commandAction()
    {
        std::cout << "CommandType B! valueA: " << valueA << " string: " << std::string(valueB.begin(), valueB.end()) << std::endl;
    }
};

struct CommandTypeC : public CommandBase
{
    std::string labelName;
    std::vector<AnyCommand> commands;
    CommandTypeC() = default;
    CommandTypeC(std::string ln, std::initializer_list<AnyCommand> cmds) : labelName(std::move(ln)), commands(cmds) { }
    virtual void commandAction()
    {
        std::cout 
             << "Subroutine: " << std::string(labelName.begin(), labelName.end())
             << " has "        << commands.size() << " commands:" << std::endl;

        BOOST_FOREACH(AnyCommand& c, commands)
        {
            c.commandAction();
        }          
    }
};

namespace qi = boost::spirit::qi;

BOOST_FUSION_ADAPT_STRUCT(
   CommandTypeA,
   (int, valueA)
   (int, valueB)
)

BOOST_FUSION_ADAPT_STRUCT(
   CommandTypeB,
   (double, valueA)
   (std::string, valueB)
)

BOOST_FUSION_ADAPT_STRUCT(
   CommandTypeC,
   (std::string, labelName)
   (std::vector<AnyCommand>, commands)
)

template<typename Iterator, typename Skipper = qi::space_type>
struct CommandParser : qi::grammar<Iterator, std::vector<AnyCommand>(), Skipper>
{
    CommandParser() : CommandParser::base_type(commands)
    {
        using namespace qi;
        CommandARule = int_    >> int_           >> "CMD_A";
        CommandBRule = double_ >> lexeme[+(char_ - space)] >> "CMD_B";
        CommandCRule = ':' >> lexeme [+graph - ';'] >> commands >> ';';

        command  = CommandARule | CommandBRule | CommandCRule;
        commands = +command;
    }
    protected:
    qi::rule<Iterator, CommandTypeA(),            Skipper> CommandARule;
    qi::rule<Iterator, CommandTypeB(),            Skipper> CommandBRule;
    qi::rule<Iterator, CommandTypeC(),            Skipper> CommandCRule;
    qi::rule<Iterator, AnyCommand(),              Skipper> command;
    qi::rule<Iterator, std::vector<AnyCommand>(), Skipper> commands;
};

int main()
{
    //AnyCommand erased = CommandTypeC( "hello", { CommandTypeB(3.14, "π"), CommandTypeA(-42, 42) });
    //erased.commandAction();

    std::string const input =
        ":group             \n"
        "     3.14  π CMD_B \n"
        "     -42  42 CMD_A \n"
        "     -inf -∞ CMD_B \n"
        "     +inf +∞ CMD_B \n"
        ";                  \n"
        "99 0 CMD_A";

    auto f(begin(input)), l(end(input));

    std::vector<AnyCommand> commandList;
    CommandParser<std::string::const_iterator> p;
    bool success = qi::phrase_parse(f, l, p, qi::space, commandList);

    if (success) {
        BOOST_FOREACH(AnyCommand& c, commandList) {
            c.commandAction();
        }
    } else {
        std::cout << "Parsing failed\n";
    }

    if (f!=l) {
        std::cout << "Remaining unparsed input '" << std::string(f,l) << "'\n";
    }
}
