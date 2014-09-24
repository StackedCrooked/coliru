#include <iostream>                        // cout, endl, << 

//auto apply_list = [](auto cont, auto ...args)
//{
//    return cont(args...);
//}
auto make_list = [](auto ...args) 
{ 
    auto applied = [=](auto cont){ 
        return cont(args...);
    };    
    return applied; 
}; 
 
auto head = [](auto closure_list) 
{ 
    auto continuator_head = [](auto first, auto ...rest){ 
        return first; 
    };    
    return closure_list(continuator_head); 
}; 
 
auto tail = [](auto closure_list) 
{ 
    auto continuator_tail = [=](auto first, auto ...rest)     { 
        return make_list(rest...); 
    };    
    return closure_list(continuator_tail); 
}; 
 
auto length = [](auto closure_list) 
{
    auto continuator_length = [](auto ...args) { 
        return sizeof...(args); 
    };
    
    return closure_list(continuator_length); 
};
 
auto log = [](auto closure_list)
{
    auto continuator_log = [=](auto ...args)
    {
        auto comma = "";
        auto print = [comma](auto x) mutable { std::cout << comma << x ; comma = ","; return x; };
    
        std::cout << "[";
        auto result = make_list(print(args)...);
        std::cout << "]";
        return result;
    };
    
    return closure_list(continuator_log);
};

int test1()
{
    auto len = length(make_list(1, '2', "3"));    
    std::cout << "len :" << len << std::endl;
    
    auto hd  = head(make_list(1, '2', "3"));    
    std::cout << "head :" << hd << std::endl;
    
    std::cout << "log :"; log(make_list(1, '2', "three")); std::cout << std::endl;
    
    auto tl  = log(tail(log(tail(log(tail(log(make_list(1, '2', "three", "four"))))))));
            
    return 0;
}

int main()
{
    test1();
}


