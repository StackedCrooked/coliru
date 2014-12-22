#include <iostream>
#include <string>
#include <vector>

template <typename SentenceContainerType>
    static std::vector<Rule<SentenceContainerType>> computeMatches(const SentenceContainerType& sentence){
        const auto begin = std::begin(sentence);
        const auto end = std::end(sentence);
        std::vector<Rule<SentenceContainerType>> result;
        for(auto it = std::find(begin, end, "and"); it != end; it = std::find(it, end, "and")){
	std::cout << "found an instance of the word " << *it << std::endl;
            auto index = std::distance(begin, it);
	std::cout << "\t@" << index << " (on a " << sentence.size() << " long sentence)" << std::endl;
            if(index > 0 && (index + 1) < integer_cast<decltype(index)>(sentence.size()) ){
	    std::cout << "\tlet's make a DummyRule out of: " << integer_cast<size_t>(index-1) << " and " <<  integer_cast<size_t>(index+1) << std::endl;
	    auto data = DummyRule(integer_cast<size_t>(index-1), integer_cast<size_t>(index+1) );
	    std::cout << "\tthe DummyRule constructor went all right" << std::endl;
	    std::cout << "\tlet's now make a Rule" << std::endl;
	    auto rule = Rule<SentenceContainerType>(data);
	    std::cout << "\tthe Rule constructor went all right" << std::endl;

	    
	    std::cout << "\tLet's push back (result.size() = " << result.size() << ")" << std::endl;
	    try{
		    result.push_back(rule);
		    std::cout << "\tpushing back was all right" << std::endl;
		    std::cout << "\t(result.size() = " << result.size() << ")" << std::endl;
	    }
	    catch(...){
		    std::cout << "\tDIDN'T MANAGE TO EMPLACE_BACK. Got an exception" << std::endl;
	    }
	    pass(index - 1 >= 0);
	    pass(integer_cast<size_t>(index + 1) < sentence.size());
            }
            std::advance(it, 1);
	std::cout << "\tfor the record, the next word is: \"" << *it << "\". I'm starting from there to find a new occourrence of \"and\"" << std::endl;
	pass(it != end);
        }
        return result;
    }
    
[==========] Running 1 test from 1 test case.
[----------] Global test environment set-up.
[----------] 1 test from OntologyMatchingConjunctions
[ RUN      ] OntologyMatchingConjunctions.RuleMatchingSmokeTest
found an instance of the word and
        @1 (on a 19 long sentence)
        let's make a DummyRule out of: 0 and 2
        the DummyRule constructor went all right
        let's now make a Rule
        the Rule constructor went all right
        Let's push back (result.size() = 0)
        pushing back was all right
        (result.size() = 1)
        for the record, the next word is: "dogs". I'm starting from there to fin
d a new occourrence of "and"
found an instance of the word and
        @5 (on a 19 long sentence)
        let's make a DummyRule out of: 4 and 6
        the DummyRule constructor went all right
        let's now make a Rule
        the Rule constructor went all right
        Let's push back (result.size() = 1)
unknown file: error: SEH exception with code 0xc00000fd thrown in the test body.

[  FAILED  ] OntologyMatchingConjunctions.RuleMatchingSmokeTest (196 ms)
    
    

int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
}
