#include <boost/variant.hpp>

#include <iostream>
#include <string>

boost::variant<int, double, std::string> variant;

template <typename FirstArg, typename... OtherArgs>
auto bar(const std::type_info& variant_type_info) -> decltype(typeid(FirstArg) == variant_type_info ? boost::get<FirstArg>(variant) : bar<OtherArgs...>(variant_type_info))
{
    if (typeid(FirstArg) == variant_type_info)
    {
        return boost::get<FirstArg>(variant);
    }
    
    return bar<OtherArgs...>(variant_type_info);
}

template <typename... VariantArgs>
auto foo(const boost::variant<VariantArgs...>& variant) -> decltype(bar<VariantArgs...>(variant.type()))
{
    return bar<VariantArgs...>(variant.type());
}

int main()
{
    variant = 0.5;
    const auto& baz = foo(variant);
    std::cout << baz << '\n';
}
