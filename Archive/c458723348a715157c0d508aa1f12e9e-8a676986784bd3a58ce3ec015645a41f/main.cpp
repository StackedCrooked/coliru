#include <string>
using std::string;

struct bankBranch {
    bankBranch(int, string, int){}
};

class bankAccount
{
public:
  bankAccount(int, int, int, string, int);
private:
  bankBranch homeBranch;
};

bankAccount::bankAccount(int accountNumber, int accountBalance, int homebsbnumber, 
string homeaddress, int homepostcode) : homeBranch(homebsbnumber, homeaddress, homepostcode) {}

int main(){}