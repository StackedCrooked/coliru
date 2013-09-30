    #include <iostream>
    #include <iomanip>
    
    struct some_type
    {
        int i;
    };
    
    void my_deleter(some_type* p)
    {
        std::cout << "my_deleter called!" << std::endl;
        delete p;
    }
    
    #include <memory>
    int main()
    {
        std::shared_ptr<int> pm;
        
        {
            // Note: better use make_shared
            auto x = new some_type;
            // create a shared_ptr that owns x and a deleter
            std::shared_ptr<some_type> po(x, my_deleter);
            std::cout << po.use_count() << std::endl;
            
            // share ownership of x and the deleter with pm
            pm = std::shared_ptr<int>(po, &po->i);
            std::cout << po.use_count() << std::endl;

            // po gets destroyed
        }
        std::cout << pm.use_count() << std::endl;
        std::cout << "get_deleter == 0? " << std::boolalpha
                  << (nullptr == std::get_deleter<decltype(my_deleter)>(pm))
                  << std::endl;
    }