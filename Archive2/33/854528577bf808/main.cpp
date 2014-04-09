#include <map>
#include <stdexcept>
#include <string>
#include <typeinfo>
#include <boost/shared_ptr.hpp>

class Variant
{
public:
    Variant() { }

    template<class T>
    Variant(T value) : impl_(new Impl<T>(value))
    {
    }

    template<class T>
    T getValue() const
    {
        return dynamic_cast<Impl<T>&>(*impl_).getValue();
    }

    template<class T>
    void setValue(const T& value)
    {
        impl_.reset(new Impl<T>(value));
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Variant& variant)
    {
        variant.impl_->print(os);
        return os;
    }

private:
    struct Base
    {
        virtual ~Base() {};
        
        virtual void print(std::ostream& os) = 0;
    };

    template<class T>
    struct Impl : public Base
    {
        Impl(const T& value) : mValue(value) { }

        ~Impl() {}

        T getValue() const { return mValue; }
        
        void print(std::ostream& os)
        {
            os << mValue;
        }

        T mValue;
    };

    boost::shared_ptr<Base> impl_;
};

int main()
{
    // Store int
    Variant v(10);
    std::cout << "v=" << v << std::endl;

    // Store float
    v.setValue<float>(12.34);
    std::cout << "v=" << v << std::endl;

    std::cout << "\n\nGet with wrong type (will throw bad_cast): " << std::endl;
    v.getValue<bool>();
    return 0;
}