#include <memory>
#include <list>
#include <utility>
#include <algorithm>
#include <string>
#include <vector>
#include <iostream>
#include <iterator>
//Don't mind all the headers, they are leftovers from previous experiments on coliru.

class Transform;

//There is a lot of cut corners, so non templated, non derived.
class Primary{
public:
    Primary(const std::vector<int>& starting_data){
        main_data = std::make_shared<std::vector<int>>(starting_data);
    }
    
    int& at(std::size_t pos){ //return by reference here is not a problem
        return main_data->at(pos);
    }
    
    
private:
    friend class Transform;
    
    std::shared_ptr<std::vector<int>> main_data;
};

class Transform{
public:
    Transform(const Primary& base, std::function<int(int)> transform){
        op = transform;
        original_data = base.main_data;
    }
    
    int at(std::size_t pos){ //notice the return by value -> the reference here would be a reference to stack position... not a good idea
        return op(original_data->at(pos));
    }
    
    std::shared_ptr<std::vector<int>> original_data;
    std::function<int(int)> op;
    
};

int main(){
    std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    Primary foo(vec);

    for (std::size_t i = 0; i < vec.size(); i++){
        std::cout << foo.at(i) << ", ";
    }
    std::cout <<std::endl;

    Transform foo_bar(foo, [](int a){return 3* a;});
    for (std::size_t i = 0; i < vec.size(); i++){
        std::cout << foo_bar.at(i) << ", ";
    }
    std::cout << std::endl;
        
}