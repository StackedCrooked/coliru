#include <string>
#include <iostream>
#include <sstream>
#include <iterator>
#include <vector>
#include <algorithm>

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

int main()
{
    std::vector <MyStr> testVec = {
        MyStr(4, "key 4"), 
        MyStr(3, "key 3"), 
        MyStr(3, "key 3"), 
        MyStr(2, "key 2"), 
        MyStr(2, "key 2"), 
        MyStr(2, "key 2")
    };

    //auto comparator = [](const MyStr& lhs, const MyStr& rhs) {
    //    return lhs.key < rhs.key;
    //};
    
    std::vector <MyStr> foursBucket;
    std::vector <MyStr> threesBucket;
    std::vector <MyStr> twosBucket;
    
    auto ostriter = std::ostream_iterator<MyStr>(std::cout, ",");
    std::for_each(testVec.begin(), testVec.end(), 
        [&](const MyStr& next){
            switch (next.key) {
            case 4:
                foursBucket.push_back(next);
                break;
            case 3:
                threesBucket.push_back(next);
                break;
            case 2:
                twosBucket.push_back(next);
                break;
            }
        });
    std::cout << "Elements with Key Value 2" << std::endl;
    std::copy(twosBucket.begin(), twosBucket.end(), ostriter);
    std::cout << std::endl;
    std::cout << "Elements with Key Value 3" << std::endl;
    std::copy(threesBucket.begin(), threesBucket.end(), ostriter);
    std::cout << std::endl;
    std::cout << "Elements with Key Value 4" << std::endl;
    std::copy(foursBucket.begin(), foursBucket.end(), ostriter);
    std::cout << std::endl;
}
