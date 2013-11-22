#include <iostream>
#include <memory>
#include <string>
#include <string.h>


struct Segment
{
    struct Copy {};
    struct Ref {};
    
    // Creates a segment which contains a reference to the data.
    Segment(const char* b, const char* e, Ref) :
        mBegin(b),
        mEnd(e),
        mOwn(false)
    {
    }
    
    // Creates a segment which contains a copy of the data.
    Segment(const char* b, const char* e, Copy)
    {        
        auto len = e - b;
        mBegin = new char[len];
        mEnd = mBegin + len;
        memcpy(const_cast<char*>(mBegin), b, len);
        mOwn = true;
    }
    
    Segment(Segment&& rhs) :
        mBegin(rhs.mBegin),
        mEnd(rhs.mEnd),
        mOwn(rhs.mOwn)
    {
        rhs.mBegin = rhs.mEnd = nullptr;
        rhs.mOwn = false;
    }
    
    Segment& operator=(Segment&& rhs)
    {
        mBegin = rhs.mBegin;
        mEnd = rhs.mEnd;
        mOwn = rhs.mOwn;
        
        rhs.mBegin = rhs.mEnd = nullptr;
        rhs.mOwn = false;
        return *this;
    }
    
    ~Segment()
    {
        if (mOwn)
        {
            delete [] mBegin;
        }
    }
    
    Segment copy() const
    {
        return Segment(begin(), end(), Copy());
    }
    
    const char* begin() const
    {
        return mBegin;
    }
    
    const char* end() const
    {
        return mEnd;
    }
    
    std::size_t size() const
    {
        return mEnd - mBegin;
    }
    
    bool empty() const
    {
        return !size();
    }
    
    const char* data()
    {
        return mBegin;
    }
    
    void swap(Segment& rhs)
    {
        std::swap(mBegin, rhs.mBegin);
        std::swap(mEnd, rhs.mEnd);
        std::swap(mOwn, rhs.mOwn);
    }

private:
    friend std::ostream& operator<<(std::ostream& os, const Segment& segment)
    {
        return os << "[" << std::string(segment.begin(), segment.end()) << "]";
    }
    
    const char* mBegin;
    const char* mEnd;
    bool mOwn;
};


template<typename T>
void print_type(T&&)
{
    std::cout << __PRETTY_FUNCTION__ << " (size=" << sizeof(T) << ")" << std::endl;
}


int main()
{
    auto&& message = "Hello";
    auto&& message2 = "Goodbye";
    print_type(message);
    
    using std::begin;
    using std::end;
    using std::swap;
    
    
    Segment s1(begin(message), end(message), Segment::Ref());
    Segment s2(begin(message2), end(message2), Segment::Copy());
    
    Segment s3 = std::move(s2);
    std::cout << s1 << s2 << s3 << std::endl; 
    
    s2 = std::move(s3);
    std::cout << s1 << s2 << s3 << std::endl; 
    
    swap(s1, s2);
    std::cout << s1 << s2 << s3 << std::endl;
}