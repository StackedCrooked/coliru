#include <iostream>
#include <string>
#include <set>

using namespace std;

struct ProgramState {

    int run_menu() {
        while (cin) {
            cout << "Choose from the following options!!\n1: Login\n2: Create an account: ";
            int option = 0;
            if (cin >> option) {
                switch (option) {
                    case 1:
                        menuitem_log();
                        break;
                    case 2:
                        menuitem_create();
                        break;
                    default:
                        cout << "fail";
                        return 1;
                }
            } else {
                if (cin.eof())
                    return 1;
                cin.clear();
                cin.ignore(1ul << 10, '\n');
            }
        }
        return 0;
    }

  private:
    void menuitem_log() {
        string usr;

        cout << "enter your username\t";
        if (cin >> usr)
        { 
            auto match = users.find(User{ usr, "" });

            string pass;
            cout << "Please enter your password!\t";

            if (std::cin >> pass && match != users.end() && pass == match->password) {
                cout << "count bodies like sh33p" << endl << "\n              welcome      " << usr << "\n";
            } else {
                cout << "user name or password incorrect\n";
            }
        } // todo error handling (see run_menu() and menuitem_create())
    }

    void menuitem_create() {
        cout << "please enter a username: ";
        User newuser;
        while (cin >> newuser.name) {
            if (users.end() == users.find(newuser)) {
                break;
            }
            cout << "error username taken; enter a username: " << endl;
        }

        if (cin) {
            cout << endl << "please enter a password!\n";
            if (cin >> newuser.password) {
                cout << "success!";
                users.insert(newuser);
            }
        }

        if (!cin) {
            exit(255); // input error is just... the end
        }
    }

    struct User {
        string name, password;

        bool operator<(User const &u) const { return name < u.name; }
    };

    set<User> users;
};


int main() { 
    ProgramState state;
    return state.run_menu(); 
}
