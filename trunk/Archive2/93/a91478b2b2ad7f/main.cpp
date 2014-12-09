#include <iostream>
#include <memory>
#include <cstring>
#include <string>
#include <stdint.h>
#include <map>


namespace {
    struct Foo {
        Foo(std::string s) : data(new std::string(s)) { }
        Foo(int32_t s) : data(new int32_t(s)) { }
        Foo(int16_t s) : data(new int16_t(s)) { }
        Foo(float s) : data(new float(s)) { }
        
        float getFloatValue() { return *(float*)data; }
        int32_t getIntValue() { return *(int32_t*)data; }
        int16_t getShortValue() { return *(int16_t*)data; }
        std::string getStringValue() { return *(std::string*)data; }
        
        private: void* data;
    };
    
    typedef std::shared_ptr<Foo> FooPtr;
    
    std::map<std::string, FooPtr> sMap;
    
    float getFloat(std::string key) { return sMap.find(key)->second->getFloatValue(); }
    int32_t getInt(std::string key) { return sMap.find(key)->second->getIntValue(); }
    int16_t getShort(std::string key) { return sMap.find(key)->second->getShortValue(); }
    std::string getString(std::string key) { return sMap.find(key)->second->getStringValue(); }
    
    FooPtr at(std::string key) {
        auto it = sMap.find(key); 
        if (it != sMap.end()) {
            return it->second;
        }
        return NULL;
    }
    
};


int main(int argc, const char* argv[]) {
    std::string aKey = "a";
    std::string bKey = "b";
    std::string cKey = "c";
    std::string dKey = "d";
    
    sMap[aKey] = FooPtr(new Foo("testA"));
    sMap[bKey] = FooPtr(new Foo((int32_t)123));
    sMap[cKey] = FooPtr(new Foo((int16_t)56)); 
    sMap[dKey] = FooPtr(new Foo(32.5f));
    
    std::cout << "a: " << getString("a") << std::endl;
    std::cout << "b: " << getInt("b") << std::endl;
    std::cout << "c: " << getShort("c") << std::endl;
    std::cout << "d: " << getFloat("d") << std::endl;
    
    //std::cout << "e: " << getString("e") << std::endl;
    
    FooPtr p = at("e");
    std::cout << "e: " << p << std::endl;
    //std::cout << "e: " << p->getStringValue() << std::endl;
    
    
    return 0;
}