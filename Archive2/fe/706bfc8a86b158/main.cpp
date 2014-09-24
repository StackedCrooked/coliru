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

auto fmap = [](auto func) { 
    return [=](auto ...z) { return make_list(func(z)...); };
};

auto log = [](auto closure_list) 
{
    auto continuator_log = [=](auto ...args) { 
        std::cout << "[";
        auto comma  = "";
        auto print  = [&](auto x) { std::cout << comma << x ; comma = ","; return x; };
        auto logger = fmap(print);
        auto ret    = logger(args...);
        std::cout << "] ";
        return ret;
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
    
    auto t1  = log(tail(log(tail(log(tail(log(make_list(1, '2', "three", "four"))))))));
            
    return 0;
}

int main()
{
    test1();
}


