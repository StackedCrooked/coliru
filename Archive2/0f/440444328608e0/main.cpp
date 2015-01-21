#include <string>
#include <iostream>
#include <cstring>
using namespace std;

struct user
{
    char name[255];
    char address[255];
    enum gender_enum {gender_male, gender_female} gender;
    char contact[255];
    char username[255];
    char password[255];
};

std::istream& operator>>(std::istream& in, user& userdata) {
    in.getline(userdata.name, 255);
    in.getline(userdata.address, 255);
    
    char genderstring[255];
    in.getline(genderstring, 255);
    if (strcmp(genderstring,"female")==0)
        userdata.gender = user::gender_female;
    else
        userdata.gender = user::gender_male;
        
    in.getline(userdata.username, 255);
    in.getline(userdata.password, 255);
    return in;
}

std::ostream& operator<<(std::ostream& cout, const user& userdata) {
    cout << "Name : " << userdata.name << '\n';
    cout << "Address : " << userdata.address << '\n';
    
    if (userdata.gender==user::gender_female)
        cout << "Gender : Female\n";
    else
        cout << "Gender : Male\n";
        
    cout << "Username : " << userdata.username << '\n';
    cout << "Password : " << userdata.password << '\n';
    return cout;
}

#include <sstream>

int main() {

    //ifstream in("owner.txt");
    std::istringstream in("james\nc 18 6 endah regal\nmale\n0104252455\nrodgo.james\nkilkil\n");

    if (!in) {
        cout << "Cannot open input file.\n";
        return 1;
    }

    user newuser;
    while (in >> newuser) {
        cout << newuser << endl;
    }

    //system("pause");
  }
  