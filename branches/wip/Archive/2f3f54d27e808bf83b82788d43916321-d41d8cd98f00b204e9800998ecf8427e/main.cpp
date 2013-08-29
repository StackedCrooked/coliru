


// HTTP method tag types
struct GET {};
struct POST {};


// Accept-header tag types
struct text_html {};
struct text_json {};


struct HTTPServer
{
    void route(GET, text_html)
    {
        // ... 
    }
    
    void route(POST, text_json)
    {
        // ... 
    }
    
    // Fallback for unsupported routes
    template<typename Method, typename Accept>
    void route(Method, Accept)
    {
        throw std::runtime_error("No route!");
    }
};
