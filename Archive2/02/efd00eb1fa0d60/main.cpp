/* Test the storage and execution of Lambda functions mapped to string keys
 *
 */

#include <iostream>
#include <functional>
#include <map>
#include <string>

using namespace std;

class Command {

public:
    Command() {}
    static std::map <string, function <bool(void)>> commandMap;
    static void Execute(string command) {
        auto search = commandMap.find(command);
        if(search != commandMap.end()) {
            function <bool(void)> f = search->second;
            f();
        } else {
            cout << command << " is not a valid command." << endl;
        }
    }
};

Command::commandMap = {
    {
        "Take inventory", [&]() {
            cout << "Taking inventory!" << endl;
                return true;
        }
    }, {
        "Random command", [&]() {
        cout << "Doing random command thing!" << endl;
            return true;
        }
    }
};

int main() {
    Command::Execute("Take inventory");
    /*string input = "";
    do {
        cout << "Please enter a command." << endl;
        cin >> input;
        cmd->Execute(input);
    } while (input != "Close");
    */
    return 0;
}

