#define BOOST_SPIRIT_DEBUG
#include <boost/fusion/adapted/struct.hpp>
#include <boost/spirit/include/qi.hpp>

namespace qi = boost::spirit::qi;

namespace ast {
    using boost::optional;
    using boost::variant;

    using nickname = std::string;
    using hostname = std::string;

    struct qualified_nickname {
        nickname nickname_;
        std::string user_;
        hostname host_; // TODO detail if required
    };

    using prefix = variant<hostname, qualified_nickname>;

    enum class wellknown_cmd { PRIVMSG = 0x1000, /*TODO*/ };

    using command = variant<wellknown_cmd, std::string>;

    using param  = std::string;
    using params = std::vector<param>; // max 15

    struct irc_message {
        optional<prefix> prefix_;
        command          command_;
        params           params_;
    };

    static inline std::ostream& operator<<(std::ostream& os, wellknown_cmd      const&) { return std::operator<<(os, "[wellknown_cmd]");      }
}

BOOST_FUSION_ADAPT_STRUCT(ast::irc_message,
        (boost::optional<ast::prefix>,prefix_)
        (ast::command,command_)
        (ast::params,params_)
    )

BOOST_FUSION_ADAPT_STRUCT(ast::qualified_nickname,
        (ast::nickname,nickname_)
        (std::string,user_)
        (ast::hostname,host_)
    )

namespace grammars {
    template <typename It>
    struct irc_message : qi::grammar<It, ast::irc_message()> {
        irc_message() : irc_message::base_type(message) {
            using namespace qi;
            constexpr auto CR    = '\r';
            constexpr auto LF    = '\n';
            constexpr auto NUL   = '\0';
            constexpr auto SPACE = ' ';
            constexpr auto crlf  = "\r\n";
            auto nospcrlfcl = boost::proto::deep_copy(char_ - NUL - CR - LF - SPACE - ':');
            auto user_char  = boost::proto::deep_copy(char_ - NUL - CR - LF - SPACE - '@');
            auto special    = boost::proto::deep_copy(char_("[]\\`_^{|}"));
            auto key_char   = boost::proto::deep_copy(char_("\x01-\x05\x07-\x08\x0C\x0E-\x1F\x21-\x7F"));

            // The extracted message is parsed into the components <prefix>,
            // <command> and list of parameters (<params>).
            //
            // The Augmented BNF representation for this is:
            //
            // message    =  [ ":" prefix SPACE ] command [ params ] crlf
            message  =
                        -(':' >> prefix >> SPACE)
                     >> command
                     >> params
                     >> crlf
                     ;

            // prefix     =  servername / ( nickname [ [ "!" user ] "@" host ] )
            prefix   =
                       qualified_nickname
                     | hostname
                     ;

            // command    =  1*letter / 3digit
            command  = no_case[wellknown_cmd_] | as_string[+alpha | (digit>digit>digit)]
                     ;

            // params     =  *14( SPACE middle ) [ SPACE ":" trailing ]
            //            =/ 14( SPACE middle ) [ SPACE [ ":" ] trailing ]
            //
            // nospcrlfcl =  %x01-09 / %x0B-0C / %x0E-1F / %x21-39 / %x3B-FF ; any octet except NUL, CR, LF, " " and ":"
            // middle     =  nospcrlfcl *( ":" / nospcrlfcl )
            // trailing   =  *( ":" / " " / nospcrlfcl )
            params   = repeat(0,14) [ SPACE >> middle ] >> -(SPACE >> trailing);
            middle   = raw [ nospcrlfcl >> *(':' | nospcrlfcl) ];
            trailing = raw [ +(nospcrlfcl|':'|SPACE) ];

            //
            qualified_nickname =
                       nickname >> '!' >> user >> '@' >> host
                     | nickname >> attr("")    >> '@' >> host // keeping the fields aligned here
                     | nickname >> attr("")    >>    attr("")
                     ;

            nickname = raw [ (letter|special) >> repeat(0,8)[letter|digit|special|'-'] ];
            user     = +user_char;
            host     = raw [ hostname|hostaddr ];
            hostname = shortname % '.';
            hostaddr = +char_("0-9.")        // ipv4
                     | +char_("0-9a-fA-F:"); // ipv6

            shortname= (letter|digit) >> *(letter|digit|'-');

            BOOST_SPIRIT_DEBUG_NODES(
                    (message)(prefix)(command)(params)(middle)(trailing)(nickname)
                    (nickname)(servername)(hostname)(host)(shortname)(hostaddr)
                )
/*
 *    target     =  nickname / server
 *    msgtarget  =  msgto *( "," msgto )
 *    msgto      =  channel / ( user [ "%" host ] "@" servername )
 *    msgto      =/ ( user "%" host ) / targetmask
 *    msgto      =/ nickname / ( nickname "!" user "@" host )
 *    channel    =  ( "#" / "+" / ( "!" channelid ) / "&" ) chanstring
 *                  [ ":" chanstring ]
 *    servername =  hostname
 *    host       =  hostname / hostaddr
 *    hostname   =  shortname *( "." shortname )
 *    shortname  =  ( letter / digit ) *( letter / digit / "-" )
 *                  *( letter / digit )
 *                    ; as specified in RFC 1123 [HNAME]
 *    hostaddr   =  ip4addr / ip6addr
 *    ip4addr    =  1*3digit "." 1*3digit "." 1*3digit "." 1*3digit
 *    ip6addr    =  1*hexdigit 7( ":" 1*hexdigit )
 *    ip6addr    =/ "0:0:0:0:0:" ( "0" / "FFFF" ) ":" ip4addr
 *    nickname   =  ( letter / special ) *8( letter / digit / special / "-" )
 *    targetmask =  ( "$" / "#" ) mask
 *                    ; see details on allowed masks in section 3.3.1
 *    chanstring =  %x01-07 / %x08-09 / %x0B-0C / %x0E-1F / %x21-2B
 *    chanstring =/ %x2D-39 / %x3B-FF
 *                    ; any octet except NUL, BELL, CR, LF, " ", "," and ":"
 *    channelid  = 5( %x41-5A / digit )   ; 5( A-Z / 0-9 )
 *
 *  Other parameter syntaxes are:
 *
 *    user       =  1*( %x01-09 / %x0B-0C / %x0E-1F / %x21-3F / %x41-FF )
 *                    ; any octet except NUL, CR, LF, " " and "@"
 *    key        =  1*23( %x01-05 / %x07-08 / %x0C / %x0E-1F / %x21-7F )
 *                    ; any 7-bit US_ASCII character,
 *                    ; except NUL, CR, LF, FF, h/v TABs, and " "
 *    letter     =  %x41-5A / %x61-7A       ; A-Z / a-z
 *    digit      =  %x30-39                 ; 0-9
 *    hexdigit   =  digit / "A" / "B" / "C" / "D" / "E" / "F"
 *    special    =  %x5B-60 / %x7B-7D
 *                     ; "[", "]", "\", "`", "_", "^", "{", "|", "}"
 *
 *  NOTES:
 *      1) The <hostaddr> syntax is given here for the sole purpose of
 *         indicating the format to follow for IP addresses.  This
 *         reflects the fact that the only available implementations of
 *         this protocol uses TCP/IP as underlying network protocol but is
 *         not meant to prevent other protocols to be used.
 *
 *      2) <hostname> has a maximum length of 63 characters.  This is a
 *         limitation of the protocol as internet hostnames (in
 *         particular) can be longer.  Such restriction is necessary
 *         because IRC messages are limited to 512 characters in length.
 *         Clients connecting from a host which name is longer than 63
 *         characters are registered using the host (numeric) address
 *         instead of the host name.
 *
 *      3) Some parameters used in the following sections of this
 *         documents are not defined here as there is nothing specific
 *         about them besides the name that is used for convenience.
 *         These parameters follow the general syntax defined for
 *         <params>.
 */
        }

    private:
        qi::rule<It, ast::irc_message()>        message;
        qi::rule<It, ast::prefix()>             prefix;
        qi::rule<It, ast::command()>            command;
        qi::rule<It, ast::params()>             params;
        qi::rule<It, ast::param()>              middle, trailing;
        qi::rule<It, ast::qualified_nickname()> qualified_nickname;
        qi::rule<It, ast::nickname()>           nickname;
        qi::rule<It, ast::hostname()>           servername;
        qi::rule<It, std::string()>             user, key, host;
        //
        qi::rule<It> hostname, shortname, hostaddr;
        qi::alpha_type letter;

        struct wc : qi::symbols<char, ast::wellknown_cmd> {
            wc() {
                add
                    ("privmsg", ast::wellknown_cmd::PRIVMSG)
                    ;
            }
        } wellknown_cmd_;
    };
}

int main() {
    using It = boost::spirit::istream_iterator;
    grammars::irc_message<It> parser;

    It it(std::cin >> std::noskipws), end;
    ast::irc_message data;
    bool ok = qi::parse(it, end, parser, data);

    if (ok) {
        std::cout << "Parse success\n";
    } else {
        std::cout << "Parse failed\n";
    }

    if (it != end)
        std::cout << "Remaining unparsed: '" << std::string(it,end) << "'\n";
}
