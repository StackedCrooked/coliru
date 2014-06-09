//accounting.h

#include <cstdint>
#include <iostream>
#include <string>

int operator"" _debits(const char *literal) {
   return std::stoi(literal);   
}

struct accounting {
   accounting(int bal) : balance(bal){}
   
   accounting operator+(int rhs) const {
      return balance + rhs;
   }
   
   int balance;
};

int printf(const char *, const accounting &acc) {
   std::cout << "bal: " << acc.balance;
   return 0;
}








//MAIN FILE
//#include <accounting.h> //see above
#include <stdio.h>

int main()
{
    accounting bank = 100_debits;
    bank = bank + 200_debits;
    return printf("bal: %accounting\n", bank);
}

