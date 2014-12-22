#include <iostream>
#include <boost/xpressive/xpressive.hpp>
#include <vector>
#include <string>

struct Data {
    struct Range{
        size_t begin;
        size_t end;
        std::string str;
    };  
    Range wholeMatch;
    std::vector<Range> subMatches;
}; 

std::vector<Data> computeTokens(
        const std::string& tagsString,
        const boost::xpressive::sregex& matchPattern,
        const boost::xpressive::sregex& termsPattern){    

    std::vector<Data> result;

    for(auto it = boost::xpressive::sregex_iterator(std::begin(tagsString), std::end(tagsString), matchPattern);
            it != boost::xpressive::sregex_iterator();
            ++it){
        const auto what = *it;
        std::string wholeMatch = what[0].str();

        Data thisMatch;
        thisMatch.wholeMatch.begin = what.position(0u);
        thisMatch.wholeMatch.end = thisMatch.wholeMatch.begin + what.length(0u);
        thisMatch.wholeMatch.str = wholeMatch;
        for(auto it = boost::xpressive::sregex_iterator(std::begin(wholeMatch), std::end(wholeMatch), termsPattern);
            it != boost::xpressive::sregex_iterator();
            ++it){
            if(it->position() < 0){
                continue;
            }   
            size_t begin = thisMatch.wholeMatch.begin + it->position();
            size_t end = begin + it->length();
            thisMatch.subMatches.emplace_back(Data::Range{begin, end, it->str()});
        }   

        result.push_back(std::move(thisMatch));
    }   

    return result;
} 

int main()
{
    std::string hello( "w-w-&w-" );

    using namespace boost::xpressive;

    static const sregex finalConj = as_xpr('+') | (!as_xpr(',') >> ((as_xpr('&') >> 'V') | (as_xpr('&') >> 'n') | as_xpr('&') | 'V')); // (\+|(,?(&|V|&/V|&n)))
    static const sregex noConjLookahead = ~before((set = ',','V','&','+')) >> ~before((as_xpr('&') >> 'n')); // (?<!,|&|V|\+)(?<!&n)
    static const sregex noConjLookbehind = ~after((set = ',','V','&','+')) >> ~after((as_xpr('&') >> 'n')); // (?<!,|&|V|\+)(?<!&n)
    static const sregex coordinandNoParentheses = +(~(set = ',', 'V', '&', '+', '(', ')')); // ([^,V&\+\(\)]+)
    static const sregex somethingInsideParentheses = '(' >> +(~as_xpr('(')) >> ')' ; // \([^\)]+\)
    static const sregex coordinandWithinSlashes = +(~as_xpr('/')); // ([^/]+)
    static const sregex coordinandWithinHyphens = +(~(set = ',', 'V', '&', '+', '/', '-')); // ([^,V&\+/-]+)
    static const sregex hyphenFinalCoordinand = +(~(set = ',','V','&','n','+','-')) >> '-'; // ([^,V&n\+-]+-)

    
    static const sregex coordinand = ~(set = ',', 'V', '&', 'n', '+', '/') >> +( *(~(set = ',', 'V', '&', 'n', '+', '/')) >> ~after(as_xpr('&')) >> !as_xpr('/') >> ~before(as_xpr('V')) >> *(~(set = ',', 'V', '&', 'n', '+', '/')) ) ; // ([^,V&n\+/]([^,V&n\+/]*(?<!&)/?(?!V)[^,V&n\+/]*)+)
    
    
    /*
    (?<!-)
    ([^,V&/-]+-)
    \1+
    finalConj
    \1
    noConjLookahead
    */
    static const sregex matchPattern = \
        ~after(as_xpr('-')) >> \
        (s1 = (+(~(set = ',','V','&','/','-')) >> '-')) >> \
        +(s1) >> \
        finalConj >> \
        s1 >> \
        noConjLookahead
    ;

    auto matchesVector = computeTokens(hello, matchPattern, hyphenFinalCoordinand);
    for(const auto& matches : matchesVector){
        std::cout << "whole match: " << matches.wholeMatch.str << ", begin: " << matches.wholeMatch.begin << ", end: " << matches.wholeMatch.end << std::endl;
        for(const auto& match : matches.subMatches){
            std::cout << '\t' << match.str << ", begin: " << match.begin << ", end: " << match.end << std::endl;
        }
        std::cout << std::endl;
    }

    return 0;
}
