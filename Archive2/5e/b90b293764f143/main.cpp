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
        return data_[(written_ - read_) - 1];
    }
    
    uint32_t size() const
    {
        assert(read_ <= written_);
        return written_ - read_;
    }
    
    void push(T t)
    {
        if (written_ == Capacity)
        {
            assert(read_ > 0 && "Capacity has been exceeded!");
            memcpy(data_, data_ + read_, read_);
            written_ -= read_;
            read_ = 0;
        }
        
        new (&data_[written_++]) T(std::move(t));
    }
    
    T pop()
    {
        assert(read_ < written_ && "Queue is empty!");
        T& old = data_[read_++];
        T result = std::move(old);
        old.~T();
        return result;
    }    
    
    friend std::ostream& operator<<(std::ostream& os, Queue<T, Capacity>& queue)
    {
        os << '[' << std::flush;
        for (auto& el : queue)
        {
            os << el << ' ' << std::flush;
        }
        return os << ']' << std::flush;
    }
    
    T* data_;
    uint32_t written_;
    uint32_t read_;
};


int main()
{
    Queue<int, 3> buffer;
    buffer.push(__COUNTER__); std::cout << "front=" << buffer.front() << std::flush << ' ' << "back=" << buffer.back() << ' ' << "buffer=" << buffer << std::endl;
    buffer.push(__COUNTER__); std::cout << "front=" << buffer.front() << std::flush << ' ' << "back=" << buffer.back() << ' ' << "buffer=" << buffer << std::endl;
    buffer.push(__COUNTER__); std::cout << "front=" << buffer.front() << std::flush << ' ' << "back=" << buffer.back() << ' ' << "buffer=" << buffer << std::endl;
    
    std::cout << "pop: " << buffer.pop() << std::endl;
    std::cout << "pop: " << buffer.pop() << std::endl;
    std::cout << "pop: " << buffer.pop() << std::endl;
    
    buffer.push(__COUNTER__); std::cout << "front=" << buffer.front() << std::flush << ' ' << "back=" << buffer.back() << ' ' << "buffer=" << buffer << std::endl;
    buffer.push(__COUNTER__); std::cout << "front=" << buffer.front() << std::flush << ' ' << "back=" << buffer.back() << ' ' << "buffer=" << buffer << std::endl;
    buffer.push(__COUNTER__); std::cout << "front=" << buffer.front() << std::flush << ' ' << "back=" << buffer.back() << ' ' << "buffer=" << buffer << std::endl;
    
    std::cout << "pop: " << buffer.pop() << std::endl;
    std::cout << "pop: " << buffer.pop() << std::endl;
    std::cout << "pop: " << buffer.pop() << std::endl;
}