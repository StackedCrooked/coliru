#include <future>

std::future<std::string> get_resource_impl(const std::string& name);
bool get_from_cache(const std::string& name, std::string&);


std::future<std::string> get_resource(const std::string& name)
{    
    std::string cached_result;
    if (get_from_cache(name, cached_result))
    {
        return cached_result; // how to wrap in std::future?
    }
    
    return get_resource_impl();
}