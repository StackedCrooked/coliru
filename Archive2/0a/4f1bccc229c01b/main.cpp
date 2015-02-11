
struct FixedPool
{
    FixedPool()
    {
        blocks_.reserve(100);
    }
    
    void* allocate(std::size_t block_size)
    {   
        if (blocks_.empty())
        {
            // prefetch 10 blocks
            // cast to char* to enable pointer arithmetic
            char* memory = static_cast<char*>(malloc(10 * block_size));
            
            // store last 9 blocks in pool
            for (int i = 1; i != 10; ++i)
            {
                auto offset = i * 10;
                blocks_.push_back(memory + offset);
            }
            
            // return the first block
            return memory;
        }
        
        auto result = blocks_.back();
        blocks_.pop_back();
        return result;
    }
    
    void deallocate(void* data, std::size_t)
    {
        blocks_.push_back(static_cast<char*>(data));
    }
    
    std::size_t size() const
    {
        return blocks_.size();
    }
    
    std::vector<char*> blocks_;
};
