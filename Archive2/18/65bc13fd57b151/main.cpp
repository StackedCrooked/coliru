#include "process.hpp" // amalgamate version for Coliru
#include <string> 
#include <vector> 
#include <iostream> 

using namespace boost::process; 

int main() 
{ 
    std::string exec = find_executable_in_path("rev"); 
    std::vector<std::string> args = boost::assign::list_of("rev"); 

    context ctx; 
    ctx.environment = self::get_environment(); 
    ctx.stdin_behavior = capture_stream(); 
    ctx.stdout_behavior = capture_stream(); 
    child c = launch(exec, args, ctx); 

    postream &os = c.get_stdin();
    pistream &is = c.get_stdout(); 

    os << "some\ncookies\nfor\ntasting";
    os.close();

    std::cout << is.rdbuf(); 
} 
