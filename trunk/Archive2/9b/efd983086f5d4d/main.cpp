#include <iostream>
#include <utility>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>


struct DataBlock
{   
    DataBlock(uint32_t inSize) :
        data_(malloc(inSize)),
        size_(inSize)
    {
    }
    
    DataBlock(const DataBlock& rhs) :
        data_(malloc(rhs.size())),
        size_(rhs.size())
    {
        memcpy(data(), rhs.data(), size());
    }
    
    DataBlock(DataBlock&& rhs) :
        data_(rhs.data()),
        size_(rhs.size())
    {
        rhs.data_ = NULL;
        rhs.size_ = 0;
    }
    
    ~DataBlock()
    {
        free(data_);
    }
    
    const void* data() const { return data_; }    
    void* data() { return data_; }    
    uint32_t size() const { return size_; }
    
private:    
    void*    data_;
    uint32_t size_;
};


int main()
{
    DataBlock block(4);
    std::cout << "block.size="  << block.size() << std::endl;
    
    auto copy = block;
    std::cout << "block.size="  << block.size() << "  copy.size="  << copy.size() << std::endl;
    
    auto moved = std::move(copy);
    std::cout << "block.size="  << block.size() << "  copy.size="  << copy.size() << "  moved.size="  << moved.size() << std::endl;
}
