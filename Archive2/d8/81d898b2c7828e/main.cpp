

class Item
{
public: 
    template<typename T>
    explicit Item(T&& t)
    {
        // ...
    }

    
    Item(Item&) = default; // (!)
    
    Item(const Item&) = default;
    Item& operator=(const Item&) = default;
    
    Item(Item&&) noexcept = default;
    Item& operator=(Item&&) noexcept = default;
    
    ~Item() = default;
    
    // ...
};
