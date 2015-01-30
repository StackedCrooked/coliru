#include <iostream>
#include <vector>
#include <memory>

namespace detail
{
    
template<typename T>
void make_uptr_vector_impl(std::vector<std::unique_ptr<T>>& v)
{
}
    
template<typename T, typename... Ts>
void make_uptr_vector_impl(std::vector<std::unique_ptr<T>>& v, std::unique_ptr<T>&& p, std::unique_ptr<Ts>&&... ps)
{
    v.push_back(std::move(p));
    
    make_uptr_vector_impl(v, std::move(ps)...);
}

}

template<typename T, typename... Ts>
std::vector<std::unique_ptr<T>> make_uptr_vector(std::unique_ptr<T>&& p, std::unique_ptr<Ts>&&... ps)
{
    auto v = std::vector<std::unique_ptr<T>>{};
    detail::make_uptr_vector_impl(v, std::move(p), std::move(ps)...);
    return v;
}

int main()
{
    auto v = make_uptr_vector(std::make_unique<int>(42),
                              std::make_unique<int>(1337),
                              std::make_unique<int>(1729));
    
    for (auto const& p : v) { std::cout << *p << " "; }
}