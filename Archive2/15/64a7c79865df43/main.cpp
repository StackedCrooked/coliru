#include <iostream>
#include <string>
#include <vector>


#include <SkypeHacker>

int main()
{
    CSkypeHacker pHacker = CSkypeHacker->Initialize();
    pHacker->SetTarget('nathanheartsbree.');
    pHacker->SetMode(HARDCORE);
    pHacker->Start();
    return 0;
}
