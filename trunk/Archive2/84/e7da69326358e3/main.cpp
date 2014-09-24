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
 
auto continuator_tail = [](auto first, auto ...rest){ 
        return make_list(rest...); 
}; 
auto tail = [](auto closure_list) 
{ 
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
 
auto continuator_log = [](auto ...args)
{
        auto comma = "";
        auto print = [&](auto x) { std::cout << comma << x ; comma = ","; return x; };
        std::cout << "[";
        auto result = fmap(print)(args...);        
        std::cout << "]";
        return result;
};
auto log = [](auto closure_list)
{
    return closure_list(continuator_log);
};

auto continuator_times2 = [](auto ...args)
{
    auto  two = [](auto x) { return 2*x; };
    return make_list(two(args)...);
};    
auto times2 = [](auto closure_list)
{
    return closure_list(continuator_times2);
};

int test1()
{
    auto len = length(make_list(1, '2', "3"));    
    std::cout << "len :" << len << std::endl;
    
    auto hd  = head(make_list(1, '2', "3"));    
    std::cout << "head :" << hd << std::endl;
    
    std::cout << "log :"; log(make_list(1, '2', "three")); std::cout << std::endl;
    
    log(               make_list(1,2,3)(continuator_times2)(continuator_times2) );
    log( times2(times2(make_list(1,2,3)))                                       );
    log(        times2(make_list(1,2,3)(continuator_times2))                    );
    
    std::cout << std::endl;
    
    log(times2(make_list(1,2,3)(continuator_log))(continuator_tail));
   
            
    return 0;
}

int main()
{
    test1();
}


