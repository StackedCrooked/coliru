#include <map>
#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <iterator>
#include <vector>
#include <algorithm>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec) {
        os << el << ' ';
    }
    return os;
}

struct MyStr
{
    int key;
    std::string strval;

    MyStr(int key, const std::string& rStrVal) 
        : key(key)
        , strval(rStrVal) 
    {}

    // let stream operators be friend functions instead of members!
    inline friend std::ostream& operator << (std::ostream& os, const MyStr& val) {
        os << "key[" << val.key << "], strval['" << val.strval << "']";
        return os;
    }

    bool operator < (const MyStr& str) const {
        return (key > str.key);
    }
};

// makes a pair object suitable for insertion into a multimap
struct PairMaker {
    template<typename A>
    std::pair<int, A> operator() (const A& a) const {
        return std::make_pair(a.key, a);
    }
};


template<typename InputIt, typename OutputIt, typename PairMaker>
    OutputIt my_copy (InputIt first, InputIt last, OutputIt result, PairMaker pairMaker)
{
    while (first!=last) {
        *result = pairMaker(*first);
        ++result; ++first;
    }
    return result;
}

int main()
{    
    std::vector <MyStr> testVec = {
        MyStr(4, "value 4"),
        MyStr(4, "value 04"),
        MyStr(4, "value 004"),
        MyStr(3, "value 3"),
        MyStr(3, "value 03"),
        MyStr(9, "value 9"),
        MyStr(9, "value 09"), 
        MyStr(9, "value 009"), 
        MyStr(9, "value 0009"), 
        MyStr(7, "value 7"), 
        MyStr(7, "value 07"), 
        MyStr(1, "value 1")
    };
    
    // target data type orderd according to a key - 
    // in this case a read command index
    std::multimap<int, MyStr> tempMap;

    std::transform (testVec.cbegin(), testVec.cend(), 
        std::inserter (tempMap, tempMap.begin()),
        [](const MyStr& a){
            return std::make_pair(a.key, a);
        });
        
    // use transformation to transform between vector and multimap
    std::cout << "transform vector => multimap" <<std::endl;
    std::cout << "============================\n" << std::endl;
    std::cout << "multimap size:" << tempMap.size() << std::endl;
    std::cout << "multimap contents:"  << std::endl;
    std::cout << "==================" << std::endl;
    std::for_each(tempMap.cbegin(), tempMap.cend(), 
        [](const std::multimap<int, MyStr>::value_type& rValue){
            std::cout 
            << "key[" << rValue.first 
            << "] value:" << rValue.second.strval 
            << std::endl;
        });
    
    std::cout << std::endl;
    
    // now add more entries to the end of the current map
    // using a specialization of the std::copy algorithm
    // that takes a custom pair maker template argument
    PairMaker pairMaker;
    my_copy(testVec.cbegin(), testVec.cend(), 
        std::inserter(tempMap, tempMap.end()), pairMaker);
    std::cout << "std::copy specialization" <<std::endl;
    std::cout << "multimap size:" << tempMap.size() << std::endl;
    std::cout << "multimap contents:"  << std::endl;
    std::cout << "==================" << std::endl;
    std::for_each(tempMap.cbegin(), tempMap.cend(), 
        [](const std::multimap<int, MyStr>::value_type& rValue){
            std::cout 
            << "key[" << rValue.first 
            << "] value:" << rValue.second.strval 
            << std::endl;
        });
    
    std::cout << std::endl;
    
    std::multimap<int,MyStr> mmap = {
        std::make_pair(4, MyStr(4, "value 4")),
        std::make_pair(4, MyStr(4, "value 04")),
        std::make_pair(4, MyStr(4, "value 004")),
        std::make_pair(3, MyStr(3, "value 3")),
        std::make_pair(3, MyStr(3, "value 03")),
        std::make_pair(9, MyStr(9, "value 9")), 
        std::make_pair(9, MyStr(9, "value 09")), 
        std::make_pair(9, MyStr(9, "value 009")), 
        std::make_pair(9, MyStr(9, "value 0009")), 
        std::make_pair(7, MyStr(7, "value 7")), 
        std::make_pair(7, MyStr(7, "value 07")), 
        std::make_pair(1, MyStr(1, "value 1"))
    };
    
    //auto ostriter = std::ostream_iterator<std::pair<int,std::string>>(std::cout, ",");
    for (auto iter = tempMap.cbegin(); iter != tempMap.cend(); ) {
        /* ... process *itr ... */
        auto range = tempMap.equal_range(iter->first);
        std::cout << "processing [" 
            << std::distance (range.first, range.second) 
            << "] entries with key[" << range.first->first 
            << "]" << std::endl;
        //std::copy (range.first, range.second, ostriter);
//        std::for_each(range.first, range.second, 
//            [](const std::multimap<int, MyStr>::value_type& rValue){
//                std::cout 
//                << "key[" << rValue.first 
//                << "] value:" << rValue.second.strval 
//                << std::endl;
//            });
        // advance to the next range
        iter = range.second;
    }    
    return 0;
}
