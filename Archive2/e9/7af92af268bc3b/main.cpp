#include <iostream>
#include <type_traits>
#include <string>
 
class Logger
{
public:
    Logger() {}
    Logger(const Logger&) = delete;
    Logger operator= (const Logger&) = delete;
    
    static void save(const std::string& str) {
        m_history += str + "\n";
    }
    
    static const std::string& getHistory() {
        return m_history;
    }
    
private:
    static std::string m_history;
};

std::string Logger::m_history;

struct Foo
{
    Foo()  { Logger::save("Foo erstellt.");  }
    ~Foo() { Logger::save("Foo geloescht."); }
};

static Foo g_f;
 
int main() {
    std::cout << Logger::getHistory() << std::endl;
    return 0;
}