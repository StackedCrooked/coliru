#include <string>
#include <iostream>
#include <map>

using namespace std;

namespace local
{
    void test2(void); void test1(void); template<typename A> void dumpMapReverse(const A &map);
}

int main(void)
{
    local::test2();
}

namespace local
{
    void test2(void)
    {
        map<int, string> mapIS;
        
        cout << "Init 3, 4, 5." << mapIS[3] << mapIS[4] << mapIS[5]
             << "\n\tResults:" << endl;
        dumpMapReverse(mapIS);
        
        mapIS[4] = "middle";
        
        cout << "\nForced 4 set."
             << "\n\tResults:" << endl;
        dumpMapReverse(mapIS);
    }
    
    void test1(void)
    {
        std::map<std::string,int> my_map;
        
        my_map["y"] = 23;
        my_map["z"] = 24;
        my_map["w"] = 12;
        my_map["x"] = 11;
        
        /*
        auto itit(my_map.cbegin());
        advance(itit, 1);
        auto itit2(itit);
        advance(itit2, 2);
        my_map.erase(itit, itit2);
        */
        
        // use for() to limit scope of eraseAt variable
        for (const auto eraseAt(my_map.find("y")); my_map.cend() != eraseAt; )
        {
            my_map.erase(eraseAt);
            break;
        }
        
        dumpMapReverse(my_map);
    }
    
    template<typename A> void dumpMapReverse(const A &map)
    {
        for (auto eachEntry = map.crbegin(); map.crend() != eachEntry; ++eachEntry)
        {
            std::cout << (*eachEntry).first << " - " << (*eachEntry).second << std::endl;
        }
    }
}
