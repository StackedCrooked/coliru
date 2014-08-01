#include <iostream>
#include <string>
#include <set>
#include <vector>

template<typename A, typename B>
struct PairMaker {
    std::pair<A, B> operator() (const A& arg1, const B& arg2) const {
        std::cout << "pairmaker primary template" << std::endl;
        return std::make_pair(arg1, arg2);
    }
};

// PairMaker partial specialization 
template<typename C, typename D, typename E>
struct PairMaker<C, std::pair<D, E>> {
    std::pair<C, E> operator() (const C& arg1, const std::pair<D, E>& arg2) const {
        std::cout << "pairmaker partial specialization" << std::endl;
        return std::make_pair(arg1, arg2.second);
    }
};

struct StructA {
    std::string mValue;
    inline friend std::ostream& operator << (
        std::ostream& os, const StructA& a) {
        os << a.mValue;
        return os;        
    }
};

struct StructB {
    std::string mValue;
    inline friend std::ostream& operator << (
        std::ostream& os, const StructB& a) {
        os << a.mValue;
        return os;        
    }
};

struct StructC {
    std::string mValue;
    inline friend std::ostream& operator << (
        std::ostream& os, const StructC& a) {
        os << a.mValue;
        return os;        
    }
};

int main()
{
    StructA a = {"A Value"};
    StructB b = {"B Value"};
    StructC c = {"C Value"};
    PairMaker<StructA, StructB> p1;
    // this is the partially specialized version of the simple pair maker
    // that makes an A,C pair when the 2nd arg is a pair object
    PairMaker<StructA, std::pair<StructB, StructC>> p2;
    
    std::pair<StructA, StructB> pairMaker = p1(a, b);
    // this will invoke the partial specialization version above
    std::pair<StructA, StructC> specialPairMaker = p2(a, std::make_pair(b,c));
    
    std::cout << "pair.first=" << pairMaker.first.mValue 
        <<  ", pair.second=" << pairMaker.second.mValue << std::endl;
    std::cout << "pair.first=" << specialPairMaker.first.mValue 
        <<  ", pair.second=" << specialPairMaker.second.mValue << std::endl;
        
    // now for the second experiment - a custom comparator for a std::set 
    // for this we need to use decltype for the lambda
    auto comp = [](const std::pair<int, StructA>& lhs, const std::pair<int, StructA>& rhs) -> bool { 
        return lhs.second.mValue < rhs.second.mValue; 
    };
    
    StructA a1 = {"A1"};
    StructA a2 = {"A2"};
    
    // uniform initialization of the pairset with custom comparator
    auto pairSet = std::set<std::pair<int, StructA>, decltype(comp)>(comp) = {
        std::make_pair(2, a1), std::make_pair(1, a2)
    };
    
    for (const auto& next : pairSet) {
        std::cout << "pair.first=" << next.first << ", pair.second=" << next.second << std::endl;
    }
}
