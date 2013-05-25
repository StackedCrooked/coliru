#include <stdint.h>


struct HTTPServer
{
    HTTPServer(uint16_t port);
    
    struct POST{};
    struct GET{};
        
    // reads the headers and then dispatches to handle_body
    void handle(std::istream&, std::ostream&);
        
    void handle_body(POST, std::istream&, std::ostream&);
    
    void handle_body(GET, std::istream&, std::ostream&);
    
};