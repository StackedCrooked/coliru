#include <memory>
#include <iostream>

template<typename T>
class Sharable : public std::enable_shared_from_this<T>
{
public:
    std::shared_ptr<T> const _sthis; // automatic shared_ptr to THIS
    using std::enable_shared_from_this<T>::shared_from_this;

    static void NoOpDeleter(T*) noexcept
    {
    }

public:
    Sharable() noexcept :
        _sthis{static_cast<T*>(this), NoOpDeleter} // DO NOT delete _sthis, it is freed by ~T()
    {
    }

    // disallow copying this class
    Sharable(Sharable const &other) = delete;
    Sharable(Sharable &&other) = delete;

    virtual ~Sharable() noexcept = default;

    Sharable& operator=(Sharable const&) = delete; // disallow assignment

    operator std::shared_ptr<T>() noexcept
    {
        return shared_from_this();
    }

    long use_count() const
    {
        return _sthis.use_count();
    }
};

// implementing class
template<typename T>
class SharableObject : public Sharable<SharableObject<T>>
{
public:
    SharableObject() noexcept = default;
    ~SharableObject() noexcept = default;
};

int main(int, char**)
{
    std::shared_ptr<SharableObject<int>> so1{new SharableObject<int>};
    SharableObject<int> so2;
    {
        auto p = so1.get()->shared_from_this();
        std::cout << "so1: " << so1.use_count() << ", so1->_sthis: " << so1->_sthis.use_count() << ", p: " << p.use_count() << std::endl;
        
        auto q = so1.get()->shared_from_this();
        std::cout << "so1: " << so1.use_count() << ", so1->_sthis: " << so1->_sthis.use_count() << ", p: " << p.use_count() << ", q: " << q.use_count() << std::endl;
        
        auto p2 = so2.shared_from_this();
        std::cout << "so2: " << so2.use_count() << ", so2->_sthis: " << so2._sthis.use_count() << ", p2: " << p2.use_count() << std::endl;
    }
    
    std::cout << "so1: " << so1.use_count() << ", so1->_sthis: " << so1->_sthis.use_count() << ", so2: " << so2.use_count() << ", so2->_sthis: " << so2._sthis.use_count() << std::endl;
    // prints 1, 1
    return 0;
}