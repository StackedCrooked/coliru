#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <algorithm>
#include <deque>
#include <list>
#include <unordered_map>
#include <utility>
#include <functional>
//#include "kunde.h"
//#include "angestellter.h"


class DataClass {
    int data;
public:
    DataClass( int d=0 ) : data(d) {}
    int getData() const { return data; }
    /*friend bool operator==(const DataClass& d1, const DataClass& d2) {
        return (d1.data == d2.data);
    }*/
    friend class DataClassHash;
    friend class DataEqual;
};

class DataClassHash {
public:
    std::size_t operator() (const DataClass& d) const {
        return d.getData() % 4;
    }
};

class DataEqual {
public:
    bool operator() (const DataClass& d1, const DataClass& d2)  {
        return (d1.data == d2.data);
    }
};


int main() {
    std::unordered_multimap<DataClass, int, DataClassHash, DataEqual> valData;
    valData.emplace( DataClass(101), 1234);
    valData.emplace( DataClass(100), 3213);
    valData.emplace( DataClass(202), 4325);
    valData.emplace( DataClass(199), 3311);
    valData.emplace( DataClass(100), 4323);
    valData.emplace( DataClass(101), 1234);
    valData.emplace( DataClass(300), 1234);

    for( const auto& elem : valData) {
        std::cout << "Bucket   : " << valData.bucket(elem.first.getData()) << std::endl;
        std::cout << "Schlüssel: " << elem.first.getData() << std::endl;
        std::cout << "Element  : " << elem.second << std::endl;
    }
    for(auto i=0; i < valData.bucket_count(); ++i) {
        std::cout << "Bucket " << i << " hat " << valData.bucket_size(i) << " Elemente\n";
    }


    
    
    
}



