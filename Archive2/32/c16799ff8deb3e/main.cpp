//
// Self-modifying function table
//
// (from "Advanced C++ Metaprogramming" by Davide Di Gennaro)
//

#include <iostream>

template<typename T, int N>
struct CircularBuffer
{   
    CircularBuffer() :
        push_back_function_(&assign_at<0>::apply)
    {
    }
    
    void push_back(const T& t)
    {
        // invoke the function pointer
        push_back_function_(*this, t);
    }
    
    const T& operator[](std::size_t idx) const
    { return data_[idx % N]; }
    
private:
    template<int K>
    struct assign_at
    {
        static void apply(CircularBuffer<T, N>& buf, const T& t)
        {
            std::cout << "K=" << K << " t=" << t << "\n";
            
            // assign the value
            buf.data_[K] = t;
            
            // update the function pointer so that it will assign at (K+1)%N next time.
            buf.push_back_function_ = &assign_at<(K+1)%N>::apply;
            
        }
    };
    
    using push_back_function_t = void (*)(CircularBuffer<T, N>&, const T&);
  
    T data_[N];
    push_back_function_t push_back_function_;
};


int main()
{
    CircularBuffer<int, 3> buf;
    buf.push_back(4);
    buf.push_back(7);
    buf.push_back(3);
    buf.push_back(1);
    buf.push_back(5);
    buf.push_back(8);
}
