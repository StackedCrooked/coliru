

    #include <iostream>
    #include <memory>
    #include <unordered_set>
    #include <algorithm>
    
    int main()
    {
        std::unordered_set<std::unique_ptr<int>> items;
        items.emplace(new int(10));
        int const *rawPtr = items.emplace(new int(20)).first->get();
        items.emplace(new int(30));
        items.emplace(new int(40));
        
        auto it = std::find_if(begin(items), 
                               end(items), 
                               [&](std::unique_ptr<int> const & item) 
                               { return item.get() == rawPtr; });

        if ( it != end(items) )
             std::cout << **it << std::endl; //should print 20!
        else
             std::cout << "item not found" << std::endl;
    }