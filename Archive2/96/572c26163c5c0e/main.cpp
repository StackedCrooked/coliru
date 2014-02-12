#include <iostream>
using namespace std;

class AccountInfo
{
public:
    int Acnumber;
    char ID;
};

class Account
{
public:
    AccountInfo Operation()
    {
        AccountInfo s;
        s.ID = 'M';
        return s;
    }
};

int main()
{
    Account a;
    AccountInfo s = a.Operation();
    cout << s.ID << endl;
    return 0;
}