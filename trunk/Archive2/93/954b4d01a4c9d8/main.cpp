#include <iostream>
#include <memory>
#include <map>

struct NoOpDeleter{
    void operator()(std::string* ptr){
        std::cout << "Not deleting for:" << *ptr << "\n";
    }
};

std::shared_ptr<std::string> get(int id){
    static std::map<int,std::string> cache;
    static bool once = false;
    if(!once){
        cache[0] = "Test0";
        cache[1] = "Test1";
    }
    
    //Create the value
    if(cache.find(id) == std::end(cache)){
        return std::make_shared<std::string>("Example");
    }else{
        return std::shared_ptr<std::string>(&(cache[id]), NoOpDeleter());
    }
}

int main(){
    auto test0 = get(0);
    auto test1 = get(1);
    auto testExample = get(2);
    std::cout << *test0 << "\n";
    std::cout << *test1 << "\n";
    std::cout << *testExample << "\n";
    
    return 0;
}