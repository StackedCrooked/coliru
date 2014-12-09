/*
    Copyright 2013 Adobe Systems Incorporated
    Distributed under the MIT License (see license at
    http://stlab.adobe.com/licenses.html)
    
    This file is intended as example code and is not production quality.
*/

#include <cassert>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <boost/noncopyable.hpp>


/******************************************************************************/
// Library

class Rule {
  public:
    template <typename T>
    Rule(T self) : self( std::make_shared<model<T>>( std::move(self) ) ) {}
    
    template <typename Container>
    friend std::vector<Container> expandSentence(const Rule& x, const Container& sentence){
            return x.self->apply(sentence);;
        }
    
  private:
    using Container = std::vector<std::string>;
    
    struct concept_t : private boost::noncopyable {
        virtual ~concept_t() = default;
        virtual std::vector<Container> apply(const Container&) const = 0;
    };
    template <typename T>
    struct model : concept_t {
        model(T data) : data( std::move(data) ) {}
        std::vector<Container> apply(const Container& position) const {
            return expandSentence(data,  position);
        }
        
        private:
            T data;
    };
    
   std::shared_ptr<const concept_t> self;
};

using Rules = std::vector<Rule>;

template <typename Container>
std::vector<Container> expandSentence(const Rules& rules, const Container& sentence)
{
    std::vector<Container> result;
    
    std::cout << "<Rules>";
    auto index = 0u;
    for (auto& e : rules){
        std::cout << std::endl;
        std::cout << "rule " << index++ << ":" << std::endl;
        const auto& sentences = expandSentence(e, sentence);
        
        auto sentenceIndex = 0u;
        for(auto& s : sentences){
            result.push_back(s);
            std::cout << "sentence " << sentenceIndex++ << ":" << std::endl;
            for(auto& token : s){
                std::cout << token << std::endl;
            }
            std::cout << std::endl;
        }
    }
    std::cout << "</Rules>" << std::endl;
    
    return result;
}

/******************************************************************************/
// Client

struct DummyRule {
    DummyRule(size_t first, size_t second) : first(first), second(second){
    }
    size_t first;
    size_t second;
};

template <typename Container>
std::vector<Container> expandSentence(const DummyRule& rule, const Container& sentence){  
    Container sentence1;
    for(auto i = 0u; i < rule.first; ++i){
        sentence1.push_back(sentence.at(i));
    }
    sentence1.push_back(sentence.at(rule.first));
    for(auto i = rule.second+1; i < sentence.size(); ++i){
        sentence1.push_back(sentence.at(i));
    }
    
    Container sentence2;
    for(auto i = 0u; i < rule.first; ++i){
        sentence2.push_back(sentence.at(i));
    }
    sentence2.push_back(sentence.at(rule.second));
    for(auto i = rule.second+1; i < sentence.size(); ++i){
        sentence2.push_back(sentence.at(i));
    }  
    
    std::vector<Container> result;
    result.push_back(sentence1);
    result.push_back(sentence2);
    return result;
}

int main(){
    std::vector<std::string> sentence;
    sentence.emplace_back("cats");
    sentence.emplace_back("and");
    sentence.emplace_back("dogs");
    sentence.emplace_back("befriend");
    sentence.emplace_back("men");
    sentence.emplace_back("and");
    sentence.emplace_back("women");
    Rules rules;
    rules.emplace_back(DummyRule(0, 2));
    rules.emplace_back(DummyRule(4, 6));
    expandSentence(rules, sentence);
}
