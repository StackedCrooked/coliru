#include <unordered_map>
#include <vector>
#include <boost/variant.hpp>

class UBO
{
    using UBOData = boost::variant<float, std::vector<float>>;
    std::unordered_map<std::string, UBOData> dataMap;
    public: 
    UBO() : dataMap(){}
    UBOData &operator[](const std::string& key)
    {
        return dataMap[key];
    }
};
int main()
{
   UBO ubo;
   ubo["scale"]       = 0.5f;
   ubo["translation"] = std::vector<float>{ 0.1f, 0.1f, 0.0f };
   ubo["rotation"]    = std::vector<float>{ 90.0f, 0.0f, 0.0f, 1.0f };
}