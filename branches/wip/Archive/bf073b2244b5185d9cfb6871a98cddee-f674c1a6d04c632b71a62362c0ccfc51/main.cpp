#include <iostream>

struct bad_any_cast {};

template <class Concept>
class any : public Concept::any_concept
{
public:
    template <class T>
    any(const T& val)
    {
        helper = new typename Concept::template any_helper<T>(val);
    }

    ~any()
    {
        delete helper;
    }

    template <class T>
    friend T any_cast(const any<Concept>& a)
    {
        auto p = dynamic_cast<typename Concept::template any_helper<T>*>(a.helper);
        if (p)
        {
            return p->val;
        }
        throw bad_any_cast();
    }


private:
    friend typename Concept::any_concept;

    typename Concept::any_helper_base* helper;
};

struct incrementable
{

    struct any_helper_base
    {
        virtual void increment() = 0;
        virtual ~any_helper_base() {}
    };


    template <class T>
    struct any_helper : public any_helper_base
    {
        T val;

        any_helper(T val) : val(val) {}

        virtual void increment()
        {
            ++val;
        }
    };
    
    class any_concept
    {
    public:
        any<incrementable>& operator++()
        {
            auto& self = static_cast<any<incrementable>&>(*this);
            self.helper->increment();
            return self;
        }
    };


};

int main()
{
    any<incrementable> a(5);
    ++a;

    std::cout << any_cast<int>(a) << std::endl;
}




