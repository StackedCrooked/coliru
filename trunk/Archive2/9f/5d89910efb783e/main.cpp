#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <utility>


struct DataBlock
{   
    DataBlock(std::size_t inSize) :
        data_(std::malloc(inSize)),
        size_(inSize)
    {
    }
    
    DataBlock(const DataBlock& rhs) :
        data_(std::malloc(rhs.size())),
        size_(rhs.size())
    {
        std::memcpy(data(), rhs.data(), size());
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
    std::size_t size() const { return size_; }
    
private:    
    void* data_;
    std::size_t  size_;
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
