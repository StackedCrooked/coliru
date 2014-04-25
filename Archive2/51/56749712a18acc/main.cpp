#include <boost/lexical_cast.hpp>
#include <string>



// private header
namespace rpc {
namespace detail {

template<typename T>
struct Identity { };

std::string serialize_impl(int n, Identity<int>);
std::string serialize_impl(bool n, Identity<bool>);
std::string serialize_impl(double n, Identity<double>);

void deserialize_impl(std::string s, int& n);
void deserialize_impl(std::string s, bool& b);
void deserialize_impl(std::string s, double& d);

} } // namespace rpc::detail



// public header
namespace rpc {


// serialize object to string
template<typename T>
std::string serialize(const T& t)
{
    using namespace detail;
    // Passing Identity<T> as a second argument to
    // avoid unexpected overloads.
    // (E.g enum can not trigger the int overload.)
    return serialize_impl(t, Identity<T>());
}


template<typename T>
T deserialize(std::string s)
{
    using namespace detail;
    T t;
    
    // NOTE: overload by non-const ref is less likely to result
    // in suprises. However, it's still possible that T::operator int&
    // is defined. So we also use Identity<T> here as second param.
    deserialize_impl(s, t, Identity<T>());
    return t;
}


} // namespace rpc


namespace rpc {
namespace detail {
    

std::string serialize_impl(int n, Identity<int>)
{
    return std::to_string(n);
}


std::string serialize_impl(bool b, Identity<bool>)
{
    return b ? "true" : "false";
}


std::string serialize_impl(double d, Identity<double>)
{
    return std::to_string(d);
}


void deserialize_impl(std::string s, int& n, Identity<int>)
{
    std::istringstream iss(s);
    iss >> n;
}


void deserialize_impl(std::string s, bool& b, Identity<bool>)
{
    if (s == "true" || s == "1")
    {
        b = true;
        return;
    }
    
    if (s == "false" || s == "0")
    {
        b = false;
        return;
    }
    
    throw bool();
}


void deserialize_impl(std::string s, double& d, Identity<double>)
{
    std::istringstream iss(s);
    iss >> d;
}


} } // namespace rpc::detail


int main()
{
    using namespace rpc;
    std::cout << std::boolalpha
              << deserialize<int>(serialize(2)) << ' '
              << deserialize<bool>(serialize(true)) << ' '
              << deserialize<double>(serialize(3.4));
}
