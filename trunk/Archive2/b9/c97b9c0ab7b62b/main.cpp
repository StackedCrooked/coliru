#include <iostream>
#include <algorithm>
#include <iterator>
#include <cstdlib>
#include <set>
#include <map>

namespace ccnet
{
    
    enum class master_command_code
    {
        RESET                   = 0x30,
        GET_STATUS              = 0x31,
    };
    
    enum class slave_message_type
    {
        GENERAL = 1, // response to a master command bearing data
        ACK     = 0,
        NACK    = 0xff,
        ILLEGAL = 0x30,
        UNKNOWN = 2 // if we are unable to identify the data
    };
    
    /** Slave message set. */
    typedef std::set<slave_message_type> slave_messsage_set_type;
    
    const slave_messsage_set_type& allowed_reply(master_command_code code);
} // namespace ccnet

const ccnet::slave_messsage_set_type& ccnet::allowed_reply(master_command_code code)
{
    typedef std::map<master_command_code, slave_messsage_set_type> master_slave_table_map;
    
    static const master_slave_table_map table =
    {
        // applicable in all states
        { master_command_code::RESET,
            { slave_message_type::ACK, slave_message_type::NACK } },
        
        { master_command_code::GET_STATUS,
            { slave_message_type::GENERAL, slave_message_type::NACK } }
    }; // <-- assert here
    
    const auto it = table.find(code);
    if (it == table.end())
    {
        throw std::invalid_argument("bogus code");
    }
    
    return it->second;
}

int main()
{
    auto x = ccnet::allowed_reply(ccnet::master_command_code::RESET);
    std::cout << "Success!" << std::endl;
    return 0;
}