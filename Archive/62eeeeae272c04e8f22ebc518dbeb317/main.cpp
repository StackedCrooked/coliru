#include <iostream>
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
    Variant(T inValue) :
        mImpl(new VariantImpl<T>(inValue)),
        mClassName(typeid(T).name())
    {
    }

    template<class T>
    T getValue() const
    {
        if (typeid(T).name() != mClassName)
        {
            throw std::logic_error("Non-matching types!");
        }

        return dynamic_cast<VariantImpl<T>*>(mImpl.get())->getValue();
    }

    template<class T>
    void setValue(T inValue)
    {
        mImpl.reset(new VariantImpl<T>(inValue));
        mClassName = typeid(T).name();
    }

private:
    struct AbstractVariantImpl
    {
        virtual ~AbstractVariantImpl() {}
    };

    template<class T>
    struct VariantImpl : public AbstractVariantImpl
    {
        VariantImpl(T inValue) : mValue(inValue) { }

        ~VariantImpl() {}

        T getValue() const { return mValue; }

        T mValue;
    };

    boost::shared_ptr<AbstractVariantImpl> mImpl;
    std::string mClassName;
};

int main()
{
    // Store int
    Variant v(10);
    int a = 0;
    a = v.getValue<int>();
    std::cout << "a = " << a << std::endl;

    // Store float
    v.setValue<float>(12.34);
    float d = v.getValue<float>();
    std::cout << "d = " << d << std::endl;

    // Store map<string, string>
    typedef std::map<std::string, std::string> Mapping;
    Mapping m;
    m["one"] = "uno";
    m["two"] = "due";
    m["three"] = "tre";
    v.setValue<Mapping>(m);
    Mapping m2 = v.getValue<Mapping>();
    std::cout << "m2[\"one\"] = " << m2["one"] << std::endl;
    return 0;
}