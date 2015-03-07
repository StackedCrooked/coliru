#include <atomic>
#include <utility>


template<typename T>
struct Cow
{
    explicit Cow(const T& t) : mImpl(new Impl(t)) {}
    
    Cow(const Cow& rhs) : mImpl(rhs.mImpl)
    {
        ++mImpl->mRefCount;
    }
    
    Cow& operator=(const Cow& rhs)
    {
        Cow(rhs).swap(*this);
        return *this;
    }
    
    ~Cow()
    {
        if (!--mImpl->mRefCount)
        {
            delete mImpl;
        }
    }
    
    void swap(Cow& rhs)
    {
        using std::swap;
        swap(mImpl, rhs.mImpl);
    }
    
    
private:
    struct Impl
    {
        std::atomic<int> mRefCount;
        T t;
    };
    
    Impl* mImpl;
};


int main()
{
    Cow<int> cow(1);
}
