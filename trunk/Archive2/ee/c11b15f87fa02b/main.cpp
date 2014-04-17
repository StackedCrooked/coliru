#include <boost/variant.hpp>
#include <memory>

//struct foo { friend bool operator<(foo, foo) { return true; } };
typedef int foo;
typedef int bar;
typedef int baz;
typedef int qux;


struct t_type_A { int key; foo value; };
struct t_type_B { int key; bar value; };
struct t_type_C { int key; baz value; };
struct t_type_D { int key; qux value; };

bool operator<(const t_type_A &, const t_type_A &);
bool operator<(const t_type_B &, const t_type_B &);
bool operator<(const t_type_C &, const t_type_C &);
bool operator<(const t_type_D &, const t_type_D &);

bool operator==(const t_type_A &, const t_type_A &);
bool operator==(const t_type_B &, const t_type_B &);
bool operator==(const t_type_C &, const t_type_C &);
bool operator==(const t_type_D &, const t_type_D &);

typedef std::shared_ptr<t_type_C> t_shared_C;
typedef std::shared_ptr<t_type_D> t_shared_D;

typedef boost::variant<t_type_A, t_type_B, t_shared_C, t_shared_D> t_variant;

class variant_less : public boost::static_visitor<bool>
{
private:
    template<typename T>
    result_type impl(const T &left, const T &right) const
    {
            return left.value < right.value || (left.value == right.value && left.key < right.key);
    }

    template<typename T, typename U>
    result_type impl(const T &left, const U &right) const
    {
            return left.key < right.key;
    }
    
    template<typename T>
    static T const& unpack(T const& p)
    {
        return p;
    }
    template<typename T>
    static T const& unpack(std::shared_ptr<T> const& p)
    {
        return *p;
    }
    
public:
    template<typename T, typename U>
    result_type operator()(const T& left, const U& right) const
    {
        return impl(unpack(left), unpack(right));
    }
};

int main()
{
    t_variant x = std::make_shared< t_type_C >();
    t_variant y = std::make_shared< t_type_D >();
    
    boost::apply_visitor(variant_less{}, x, y);
}