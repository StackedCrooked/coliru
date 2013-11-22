#include <iostream>
#include <memory>
#include <string>
#include <string.h>


struct Segment
{
    struct Copy {};
    struct Ref {};
    
    static constexpr Copy copy{};
    static constexpr Ref ref{};
    
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
    
    ~Segment()
    {
        if (mOwn)
        {
            delete [] mBegin;
        }
    }
    
    Segment(const Segment& rhs) :
        Segment(rhs.mOwn ? Segment(rhs.mBegin, rhs.mEnd, copy) : Segment(rhs.mBegin, rhs.mEnd, ref), EnsureMove())
    {
    }
    
    Segment& operator=(Segment rhs)
    {
        swap(rhs);
        return *this;
    }
    
    Segment(Segment&& rhs) :
        mBegin(rhs.mBegin),
        mEnd(rhs.mEnd),
        mOwn(rhs.mOwn)
    {
        rhs.mOwn = false;
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
    struct EnsureMove {};
    
    Segment(Segment&& rhs, EnsureMove) : Segment(std::move(rhs)) {}
    
    friend std::ostream& operator<<(std::ostream& os, const Segment& segment)
    {
        return os << "Segment(\"" << segment.begin() << "\")";
    }
    Segment() : mBegin(), mEnd(), mOwn() {}
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
    
    
    Segment s1(begin(message), end(message), Segment::ref);
    Segment s2(begin(message2), end(message2), Segment::copy);
    
    std::cout << s1 << ", " << s2 << std::endl;    
    s1 = s2; 
    
    s2 = std::move(s1);
    std::cout << s1 << ", " << s2 << std::endl;
    
    s1 = std::move(s2);
    std::cout << s1 << ", " << s2 << std::endl;
    
    std::cout << sizeof(Segment) << std::endl;
}