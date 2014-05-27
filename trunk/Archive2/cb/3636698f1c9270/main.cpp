#include <string>

using namespace std;

class CLI{
    string commands[2] = {"create", "login"};
public:
    void addCommand(), start(), getCommand(string);
};

int main() {}