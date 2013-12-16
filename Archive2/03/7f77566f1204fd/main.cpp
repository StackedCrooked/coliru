#include <iostream>
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>


#define Assert(cmd) \
    std::cout << #cmd << " => " << ((cmd) ? "PASS" : "FAIL") << std::endl;


template<typename T, unsigned Capacity>
struct Queue
{
    Queue() : data_(static_cast<T*>(malloc(sizeof(T) * Capacity))), written_(), read_() {}
    
    Queue(const Queue&) = delete;
    Queue& operator=(const Queue&) = delete;
    
    ~Queue()
    {
        for (auto& el : *this)
        {
            el.~T();
        }
        free(data_);
    }
    
    T* begin()
    {
        return data_ + read_;
    }
    
    T* end()
    {
        return data_ + written_;
    }
    
    T& front()
    {
        assert(read_ < written_);
        return data_[read_];
    }
    
    T& back()
    {
        assert(read_ < written_);
        return data_[written_ - 1];
    }
    
    bool empty() const
    {
        return read_ == written_;
    }
    
    uint32_t size() const
    {
        assert(read_ <= written_);
        return written_ - read_;
    }
    
    void push(T t)
    {
        std::cout << "push " << t << std::flush;
        if (written_ == Capacity)
        {
            assert(read_ > 0 && "Capacity has been exceeded!");
            std::move(begin(), end(), data_);
            written_ -= read_;
            read_ = 0;
            std::cout << " (moved-to-start)" << std::flush;
        }
        
        new (&data_[written_++]) T(std::move(t));
        
        
        std::cout << " => " << std::flush << (*this) << std::endl;
    }
    
    T pop()
    {
        std::cout << "pop  " << std::flush;
        assert(read_ < written_ && "Queue is empty!");
        T result = std::move(data_[read_++]);
        std::cout << result << " => " << std::flush << (*this) << std::endl;
        return result;
    }    
    
    friend std::ostream& operator<<(std::ostream& os, Queue<T, Capacity>& queue)
    {
        os << '[' << std::flush;
        for (auto& el : queue)
        {            
            os << el;
            if (&el != &queue.back())
            {
                os << '-';
            }
        }
        
        os << "]";
        
        if (queue.empty())
        {
            os << " (empty)";
        }
        else
        {
            os << " front=" << queue.front() << " back=" << queue.back() << " offset=" << (queue.begin() - queue.data_);
        }
        return os;
    }
    
    T* data_;
    uint32_t written_;
    uint32_t read_;
};


int main()
{
    Queue<int, 5> buffer;
    buffer.push(__COUNTER__);
    buffer.push(__COUNTER__);
    buffer.push(__COUNTER__);
    buffer.push(__COUNTER__);
    buffer.push(__COUNTER__);
    buffer.pop();
    buffer.pop();
    buffer.push(__COUNTER__);
    buffer.push(__COUNTER__);
}