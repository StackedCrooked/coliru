#include <string>

using namespace std;

class CLI{
    string commands[2];
public:
    CLI() : commands{"create", "login"} {}

    void addCommand(), start(), getCommand(string);
};

int main() {}