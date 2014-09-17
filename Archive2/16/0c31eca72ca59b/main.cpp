#include <iostream>


namespace stuff
{
    namespace config
    {
        // ** definition
        struct ConfigData
        {
            struct Section_1
            {
                int x, y;
            } section_1;
        };
        
        namespace //anon
        {
            // ** initialization
            ConfigData RuntimeConfig = {
                .section_1 = { 15, 20 },  
            };
        }
    
        ConfigData const & getRTConfig()
        { return RuntimeConfig; }
        
        struct ConfigFromFile
        { 
            // can modify RuntimeConfig
        };
    }
}


int main(void)
{
    auto const & cdata = getRTConfig();
    
}