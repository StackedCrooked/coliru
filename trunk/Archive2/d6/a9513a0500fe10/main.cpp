#include <string>
#include <unordered_map>

enum class ModbusStatus {SUCCESS = 0, EIDENTIFIER};
struct DatabaseT {};

std::unordered_map<std::string, DatabaseT> databases_;

struct MessageManagerClass {

    template<class K, class V>
    ModbusStatus RegisterDatabase(K&& intf, V&& db)
    {
        ModbusStatus status = ModbusStatus::SUCCESS;

        const auto it = databases_.find(intf);
        if(it != databases_.end())
        { 
            //LOG(ERR) << "Interface " << intf << " defined twice";
            return ModbusStatus::EIDENTIFIER;
        } 
        databases_.emplace(std::forward<K>(intf), std::forward<V>(db));

        return status;
    }

};


int main() {
    MessageManagerClass mManager;
    
    std::string name; DatabaseT db;

    // Example 1
    mManager.RegisterDatabase(name, db); // 1 copy (per arg) in total by unordered_map::emplace()
    // name and db still valid here, as they have not been moved

    // Example 2
    mManager.RegisterDatabase(std::move(name), std::move(db)); // 1 move in total (per arg), not two moves!
    // name and db cannot be used anymore, as they have been moved

    // Example 3
    mManager.RegisterDatabase(std::string("name"), DatabaseT{}); // again, 1 move in total from the temporaries
    // name and db cannot be used anymore, as they have been moved
}
