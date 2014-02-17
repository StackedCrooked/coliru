#include <unordered_map>
#include <string>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <functional>

void move_north() 
{
    std::cout << "moved north\n";
}
void move_south() 
{
    std::cout << "moved south\n";
}

std::unordered_map<std::string, std::function<void()>> command_list;
void load_abreviations(std::string command, std::function<void()> call) 
{
    if (command.size()) {
        command_list[command] = call;
        load_abreviations(command.substr(0, command.length()-1), call);
    }
}
void load_commands() 
{
    load_abreviations("north", move_north);
    load_abreviations("south", move_south);
}
void do_command(std::string command) 
{
    std::transform(command.begin(), command.end(), command.begin(), ::tolower);
    auto it = command_list.find(command);
    if (it != command_list.end())
        it->second();
    else
        std::cout << "did not understand command: " << command << '\n';
}

int main() {
    load_commands();
    do_command("NoR");
    do_command("sOu");
    do_command("WeS");
}
    