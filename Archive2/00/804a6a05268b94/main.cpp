#include <iostream>
#include <map>
#include <memory>
#include <mutex>


struct Item
{
    // secret storage
    // allows higher-level code to store something private here
    template<typename T>
    T& getSecret()
    {
        auto key = &typeid(T);
        auto it = mSecrets.find(key);
        if (it == mSecrets.end())
        {
            return *static_cast<T*>(mSecrets.insert(std::make_pair(key, std::make_shared<T>())).first->second.get());
        }

        return *static_cast<T*>(it->second.get());
    }
    
    std::map<const std::type_info*, std::shared_ptr<void>> mSecrets;    
};



int main()
{
    // user code
    Item item;        
    item.getSecret<std::string>() = "Hai";
    item.getSecret<std::string>() += "Bai";        
    std::cout << item.getSecret<std::string>() << std::endl;
}

