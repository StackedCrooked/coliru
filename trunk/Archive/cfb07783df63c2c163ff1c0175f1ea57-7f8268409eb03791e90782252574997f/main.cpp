#include <boost/shared_ptr.hpp>

struct RtR
{
    template<typename Ptr>
    operator Ptr()
    {
        return Ptr();
    }

    template<typename Ptr>
    operator Ptr() const
    {
        return Ptr();
    }
};

class TestRtR
{
    void test()
    {
        boost::shared_ptr<int> intPtr(new int);
        intPtr = get();
    }

    void test() const
    {
        boost::shared_ptr<const int> intPtr(new int);
        intPtr = get();
    }

    RtR get()
    {
        RtR ret;
        return ret;
    }

    const RtR get() const
    {
        const RtR ret;
        return ret;
    }
};

int
main()
{
    
}