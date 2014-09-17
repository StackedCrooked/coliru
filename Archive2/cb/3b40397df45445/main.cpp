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
            // ** initialization (ie - config defaults)
            ConfigData RuntimeConfig = {
                .section_1 = { 15, 20 },  
            };
        }
    
        ConfigData const & getRTConfig()
        { return RuntimeConfig; }
        
        
        struct ConfigFromFile
        { 
            // can modify RuntimeConfig since it declared in this
            // compilation unit
        };
    }
}


int main(void)
{
    // get the read-only version
    auto const & cdata1 = stuff::config::getRTConfig();
    auto const & cdata2 = stuff::config::getRTConfig();
    
    printf("%p\n%p\n", &cdata1, &cdata2);
}