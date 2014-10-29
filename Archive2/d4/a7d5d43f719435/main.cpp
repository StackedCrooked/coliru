#include <iostream>
#include <string>

enum Severity
{
    SEV_INFORMATIONAL,
    SEV_WARNING,
    SEV_ERROR,
    SEV_FATAL
};

std::ostream& operator << (std::ostream& out, Severity s)
{
    switch (s)
    {
        case SEV_INFORMATIONAL: out << "info"; break;
        case SEV_WARNING: out << "warning"; break;
        case SEV_ERROR: out << "error"; break;
        case SEV_FATAL: out << "fatal"; break;
        default: out << "unknown severity"; break;
    }
    
    return out;
}

enum Category
{
    CAT_STARTUP,
    CAT_CONFIGURATION,
    // ...
};

std::ostream& operator << (std::ostream& out, Category c)
{
    switch (c)
    {
        case CAT_STARTUP: out << "startup"; break;
        case CAT_CONFIGURATION: out << "configuration"; break;
        // ...
        default: out << "unknown category"; break;
    }
    
    return out;
}

class Logger
{
public:
    template<typename F>
    void Log(Severity s, Category c, F&& f)
    {
        if (IsInterested(s, c))
        {
            LogMessage(s, c, (std::forward<F>(f))());
        }
    }
    
private:
    bool IsInterested(Severity s, Category c) const
    {
        if (s == SEV_ERROR) 
        { 
            return true; 
        }
        else 
        { 
            return (c == CAT_STARTUP); 
        }
    }
    
    void LogMessage(Severity s, Category c, std::string msg)
    {
        std::cout << std::move(msg) << " (" << s << ", " << c << ")" << std::endl;
    }
};

int main()
{
    Logger l;
    
    int count = 42;
    l.Log(SEV_INFORMATIONAL, CAT_STARTUP, [=]
    {
        return "This will be logged: " + std::to_string(count);
    });
    
    l.Log(SEV_WARNING, CAT_CONFIGURATION, [=]
    {
        return "This will not be logged: " + std::to_string(count);
    });
    
    l.Log(SEV_ERROR, CAT_CONFIGURATION, [=]
    {
        return "This will be logged: " + std::to_string(count);
    });
}