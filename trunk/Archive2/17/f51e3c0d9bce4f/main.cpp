#include <string>
#include <iostream>

#include "boost/optional.hpp"

namespace auth_asset {

class Unexpected;

template <typename T>
class Expected;

template <typename T>
struct IsExpected : std::false_type {};
template <typename T>
struct IsExpected<Expected<T>> : std::true_type{};

class Unexpected
{
public:
  explicit Unexpected(std::string&& error) : error_(std::move(error)) { }
  explicit Unexpected(const std::string& error) : error_(error) { }

  const std::string& error() const { return error_; }

private:
  std::string error_;
};

template <typename T>
class Expected
{
public:
  typedef Expected<T> ThisType;
  typedef T ValueType;  

  // default constructor
  Expected() : unexpected_("Not initialized") {}

  // from value
  Expected(const T& value) : value_(value) { }

  // from rvalue reference
  Expected(T&& value) : value_(std::move(value)) { }

  // from unexpected
  Expected(const Unexpected& unexpected) 
    : unexpected_(unexpected)
  { }

  Expected(Unexpected&& unexpected) 
    : unexpected_(std::move(unexpected))
  { }

  // extract value
  // precondition : valid() == true
  const T& operator*() const { return *value_; }
  T& operator*() { return *value_; }

  const T& value() const { return *value_; }
  T& value() { return *value_; }

  const T* operator->() const { return &(*value_); }
  T* operator->() { return &(*value_); }

  // extract error
  // precondition : valid() == false
  const Unexpected& unexpected() const { return *unexpected_; }
  const std::string& error() const { return unexpected().error(); }

  // check if value is set
  bool valid() const { return value_.is_initialized(); }

private:
  boost::optional<T> value_;
  boost::optional<Unexpected> unexpected_;
};

#define ASSET_MAKE_UNEXPECTED(x) \
  auth_asset::Unexpected(std::string("[") + __FUNCTION__ + ":" + std::to_string(__LINE__) + "] " + x)

#define ASSET_EXPECT(V, EXPR) \
auto BOOST_JOIN(expected,V) = EXPR; \
if (!BOOST_JOIN(expected,V).valid()) return BOOST_JOIN(expected,V).unexpected(); \
auto V = *BOOST_JOIN(expected,V)

template <typename T>
inline std::ostream& operator<<(std::ostream& os, const Expected<T>& v)
{
  if (v.valid())
    os << v.value();
  else
    os << "error: " << v.error();
  return os;
}

}    // end namespace auth_asset

////////////////////////////////////////////////////////////////////////////////////////
// use optional
////////////////////////////////////////////////////////////////////////////////////////
namespace use_optional {

boost::optional<int> parse_int(std::string s)
{
    try { 
        return std::stol(s); 
    } 
    catch (const std::exception& e) {
        std::cerr << __FUNCTION__ << ":" << __LINE__ << ", error!!" << std::endl;
        return boost::none;
    }
}

boost::optional<std::string> convert_to_string(int i)
{
    try { 
        return std::to_string(i+1); 
    } 
    catch (const std::exception& e) {
        std::cerr << __FUNCTION__ << ":" << __LINE__ << ", error!!" << std::endl;
        return boost::none;
    }
}

boost::optional<std::string> func(std::string input)
{
    auto i1 = parse_int(input);
    if (!i1)
        return boost::none;
    auto s1 = convert_to_string(*i1);
    if (!s1)
        return boost::none;
    auto i2 = parse_int(*s1);
    if (!i2)
        return boost::none;
    auto s2 = convert_to_string(*i2);
    if (!s2)
        return boost::none;
    return *s2;
}

void run()
{
    std::cout << "= use_optional =============================" << std::endl;
    auto ret1 = func("123");
    if (!ret1)
        std::cout << "error." << std::endl;
    else
        std::cout << "success." << *ret1 << std::endl;
    auto ret2 = func("abc");
    if (!ret2)
        std::cout << "error." << std::endl;
    else
        std::cout << "success." << *ret2 << std::endl;
}

}

////////////////////////////////////////////////////////////////////////////////////////
// use expected
////////////////////////////////////////////////////////////////////////////////////////
namespace use_expected {

auth_asset::Expected<int> parse_int(std::string s)
{
    try { 
        return std::stol(s); 
    } 
    catch (const std::exception& e) {
        return ASSET_MAKE_UNEXPECTED(e.what());
    }
}

auth_asset::Expected<std::string> convert_to_string(int i)
{
    try { 
        return std::to_string(i+1); 
    } 
    catch (const std::exception& e) {
        return ASSET_MAKE_UNEXPECTED(e.what());
    }
}

auth_asset::Expected<std::string> func(std::string input)
{
    auto i1 = parse_int(input);
    if (!i1.valid())
        return i1.unexpected();
    auto s1 = convert_to_string(*i1);
    if (!s1.valid())
        return s1.unexpected();
    auto i2 = parse_int(*s1);
    if (!i2.valid())
        return i2.unexpected();
    auto s2 = convert_to_string(*i2);
    if (!s2.valid())
        return s2.unexpected();
    return *s2;
}

void run()
{
    std::cout << "= use_expected =============================" << std::endl;
    auto ret1 = func("123");
    if (!ret1.valid())
        std::cout << "error. " << ret1.error() << std::endl;
    else
        std::cout << "success." << *ret1 << std::endl;
    auto ret2 = func("abc");
    if (!ret2.valid())
        std::cout << "error. " << ret2.error() << std::endl;
    else
        std::cout << "success." << *ret2 << std::endl;
}

}

////////////////////////////////////////////////////////////////////////////////////////
// use expected plus macro
////////////////////////////////////////////////////////////////////////////////////////
namespace use_expected_plus_macro {

auth_asset::Expected<int> parse_int(std::string s)
{
    try { 
        return std::stol(s); 
    } 
    catch (const std::exception& e) {
        return ASSET_MAKE_UNEXPECTED(e.what());
    }
}

auth_asset::Expected<std::string> convert_to_string(int i)
{
    try { 
        return std::to_string(i+1); 
    } 
    catch (const std::exception& e) {
        return ASSET_MAKE_UNEXPECTED(e.what());
    }
}

auth_asset::Expected<std::string> func(std::string input)
{
    ASSET_EXPECT(i1, parse_int(input));
    ASSET_EXPECT(s1, convert_to_string(i1));
    ASSET_EXPECT(i2, parse_int(s1));
    ASSET_EXPECT(s2, convert_to_string(i2));
    return s2;
}

void run()
{
    std::cout << "= use_expected_plus_macro ==================" << std::endl;
    auto ret1 = func("123");
    if (!ret1.valid())
        std::cout << "error. " << ret1.error() << std::endl;
    else
        std::cout << "success." << *ret1 << std::endl;
    auto ret2 = func("abc");
    if (!ret2.valid())
        std::cout << "error. " << ret2.error() << std::endl;
    else
        std::cout << "success." << *ret2 << std::endl;
}

}

int main()
{
    use_optional::run();
    use_expected::run();
    use_expected_plus_macro::run();
}