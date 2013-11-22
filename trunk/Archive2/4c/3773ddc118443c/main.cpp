#include <iostream>
#include <memory>
#include <string>
#include <string.h>


struct ByteRange
{
    struct Copy {};
    struct Ref {};
    
    ByteRange() : mBegin(), mEnd(), mOwn(false) {}
    
    // Creates a ByteRange which contains a reference to the data.
    ByteRange(const char* b, const char* e, Ref) :
        mBegin(b),
        mEnd(e),
        mOwn(false)
    {
    }
    
    // Creates a ByteRange which contains a copy of the data.
    ByteRange(const char* b, const char* e, Copy)
    {        
        auto len = e - b;
        mBegin = new char[len];
        mEnd = mBegin + len;
        memcpy(const_cast<char*>(mBegin), b, len);
        mOwn = true;
    }
    
    ByteRange(ByteRange&& rhs) :
        mBegin(rhs.mBegin),
        mEnd(rhs.mEnd),
        mOwn(rhs.mOwn)
    {
        rhs.mBegin = rhs.mEnd = nullptr;
        rhs.mOwn = false;
    }
    
    ByteRange& operator=(ByteRange&& rhs)
    {
        mBegin = rhs.mBegin;
        mEnd = rhs.mEnd;
        mOwn = rhs.mOwn;
        
        rhs.mBegin = rhs.mEnd = nullptr;
        rhs.mOwn = false;
        return *this;
    }
    
    ~ByteRange()
    {
        if (mOwn)
        {
            delete [] mBegin;
        }
    }
    
    ByteRange copy() const
    {
        return ByteRange(begin(), end(), Copy());
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
    
    const char* data() const
    {
        return mBegin;
    }
    
    void swap(ByteRange& rhs)
    {
        std::swap(mBegin, rhs.mBegin);
        std::swap(mEnd, rhs.mEnd);
        std::swap(mOwn, rhs.mOwn);
    }

private:
    friend std::ostream& operator<<(std::ostream& os, const ByteRange& ByteRange)
    {
        return os << "[" << std::string(ByteRange.begin(), ByteRange.end()) << "]";
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


struct DataSource
{
    struct Real {};
    struct Fake {};
    
    static std::shared_ptr<DataSource> CreateFake()
    {
        return std::make_shared<FakeDataSource>();
    }
    
    static std::shared_ptr<DataSource> CreateReal()
    {
        return std::make_shared<RealDataSource>();
    }
    
    DataSource(bool inFake) :
        mFake(inFake)
    {
    }
    
    bool fake() const
    {
        return mFake;
    }
    
    ByteRange read(unsigned mdl)
    {
        if (mFake)
        {
            static_cast<FakeDataSource&>(*this).do_read(mdl);
        }
        else
        {
            static_cast<RealDataSource&>(*this).do_read(mdl);
        }
    }
    
    ByteRange write(const char* data, unsigned len)
    {
        assert(!mFake);
        if (!mFake)
        {
            static_cast<RealDataSource&>(*this).do_write(data, len);
        }
    }
    
private:
    bool mFakeData;    
};


struct FakeDataSource : DataSource
{
    ByteRange do_read(unsigned mdl)
    {
        if (mBuffer.size() < mdl)
        {
            mBuffer.resize(mdl);
        }
        return ByteRange(mBuffer.data(), mBuffer.data() + mdl, ByteRange::Ref());
    }    
    
    std::string mBuffer;
};


struct RealDataSource : DataSource
{
    void write(const char* data, unsigned len)
    {
        append(mBuffer, data, len);
    }   
    
    ByteRange read(unsigned len, ByteRange::Ref)
    {
        ByteRange(current(), current() + len);
        consume(mBuffer, len);
    }    
    
    std::string mBuffer;
};


int main()
{
    auto&& message = "Hello";
    auto&& message2 = "Goodbye";
    print_type(message);
    
    using std::begin;
    using std::end;
    using std::swap;
    
    
    ByteRange s1(begin(message), end(message), ByteRange::Ref());
    ByteRange s2(begin(message2), end(message2), ByteRange::Copy());
    
    ByteRange s3 = std::move(s2);
    std::cout << s1 << s2 << s3 << std::endl; 
    
    s2 = std::move(s3);
    std::cout << s1 << s2 << s3 << std::endl; 
    
    swap(s1, s2);
    std::cout << s1 << s2 << s3 << std::endl;
}




