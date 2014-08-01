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
};

struct StructB {
    std::string mValue;
};

struct StructC {
    std::string mValue;
};

int main()
{
    StructA a = {"A Value"};
    StructB b = {"B Value"};
    StructC c = {"C Value"};
    PairMaker<StructA, StructB> pairMaker;
    PairMaker<StructA, std::pair<StructB, StructC>> partiallySpecializedPairMaker;
    std::pair<StructA, StructB> primaryPairMaker = pairMaker(a, b);
    std::pair<StructA, StructC> specialPairMaker = partiallySpecializedPairMaker(a, std::make_pair(b,c));
    std::cout << "pair.first=" << primaryPairMaker.first.mValue 
        <<  ", pair.second=" << primaryPairMaker.second.mValue << std::endl;
    std::cout << "pair.first=" << specialPairMaker.first.mValue 
        <<  ", pair.second=" << specialPairMaker.second.mValue << std::endl;
    auto comp = [](const std::pair<int, StructA>& lhs, const std::pair<int, StructA>& rhs) -> bool { 
        return lhs.second.mValue < rhs.second.mValue; 
    };
    StructA a1 = {"A Value1"};
    StructA a2 = {"A Value2"};
    auto pairSet = std::set<std::pair<int, StructA>, decltype(comp)>(comp) = {std::make_pair(1, a1), std::make_pair(1, a2)};
}
