#include <iostream>                        // cout, endl, << 

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
    auto continuator_length = [](auto ...z) { 
        return sizeof...(z); 
    };
    
    return closure_list(continuator_length); 
};
 
auto print = [](auto closure_list)
{
    auto continuator_print = [](auto first, auto ...rest)
    {
        std::cout << first;
        if (length(rest) == 0)
            std::cout << std::endl;
        ???            
    };
    return closure_list(continuator_print);
};

int test1()
{
    auto len = length(make_list(1, '2', "3"));    
    std::cout << len << std::endl;
    
    auto hd  = head(make_list(1, '2', "3"));    
    std::cout << hd << std::endl;
    
    auto tl  = tail(tail(make_list(1, '2', "three")));    
    std::cout << head(tl) << std::endl;
    print((tail(make_list(1, '2', "three")));
        
    return 0;
}

int main()
{
    test1();
}


