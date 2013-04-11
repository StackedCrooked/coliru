#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;

class BankAccount {
private:
    double accountBalance;
    string name;        
public:
    BankAccount();
    BankAccount(string,double);
    double deposit(double);
    double withdraw(double);
    void checkBalance();                    
};

BankAccount::BankAccount()
{
    accountBalance=0;
    name="";
}

BankAccount::BankAccount(string name,double money)
{
    name=name;
    accountBalance=accountBalance;                                
}

double BankAccount::deposit(double money)
{
    accountBalance+=money;
    return accountBalance;
}

double BankAccount::withdraw(double money)
{
    accountBalance-=money;
    return accountBalance;
};            

void BankAccount::checkBalance()
{
    cout<<"The balance on the account is $"<<accountBalance<<"!!"<<endl;     
};                                                                                                             
int main(int argc, char *argv[])
{
    int c;
    double m;
    string n;
    cout<<"==================Bank======="<<endl;
    cout<<"[1] Open a new Bank Account |"<<endl;
    cout<<"[2] Deposit money           |"<<endl;
    cout<<"[3] Withdraw money          |"<<endl;
    cout<<"[4] Check balance           |"<<endl;
    cout<<"============================="<<endl;
    cout<<endl;
    cout<<"What would you like to do :";
    cin>>c;

    switch (c){
    case 1:
        cout<<"Ok I see you want to open a new Bank Account"<<endl;
        cout<<"But first answer a few questions:"<<endl;
        cout<<"What is your name? ";
        cin>>n;
        cout<<"Next tell me the amount of money you wish to open your account with: ";
        cin>>m;
        BankAccount::BankAccount(n,m);
        cout<<"OK all set, "<<n<<"!!"<<endl;
        break;
    case 2:
        cout<<"How much money would you like to deposit? : ";
        cin>>m;
        BankAccount.deposit(m);
        break;
    case 3:
        cout<<"How much money would you like to withdraw? : ";
        cin>>m;
        BankAccount.withdraw(m);
        break;
    case 4:
        cout<<"OK I'll check your balance"<<endl;
        BankAccount.checkBalance();               
        break;
    }
    system("PAUSE");
    return EXIT_SUCCESS;
}