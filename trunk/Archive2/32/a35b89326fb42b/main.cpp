int  read_balance(void);
void write_balance(int balance);

#include <iostream>
#include <limits>

int main()
{
    while(std::cin.good())
    {
        std::cout << "0. Request balance"       << std::endl;
        std::cout << "1. Transfer an amount"    << std::endl;
        std::cout << "2. Quit"                  << std::endl;
        std::cout << "Please enter menu number" << std::endl;

        int selection = 2;
        if(std::cin >> selection)
        {
            std::cout << "INPUT: selection:" << selection << "\n"; // for online demo
            switch(selection)
            {
            case 0:
                std::cout << "The current account balance is " << read_balance() << std::endl;
                break;

            case 1:
                {
                    std::cout << "You have choosen to transfer an amount" << std::endl;
                    std::cout << "How much do you wish to transfer from the shop account?"<<std::endl;

                    int amount = 0;
                    if (std::cin >> amount)
                    {
                        std::cout << "INPUT: amount:" << amount << "\n"; // for online demo
                        int balance = read_balance();
                        if(amount<=0)
                        {
                            std::cout << "Amount must be positive\n";
                        }
                        else if(balance < amount)
                        {
                            std::cout << "Insufficient funds\n";
                        }
                        else
                        {
                            int new_balance = balance - amount;
                            write_balance(new_balance);
                            std::cout << "New account balance: " << new_balance << std::endl;
                        }
                    } else
                    {
                        // bad input cleared outside the switch
                    }
                }
                break;

            case 2:
                return 0;
                break;

            default:
                std::cout << "Ooops, invalid selection!" << std::endl;
                break;
            }
        }

        std::cout << "Before ignore: "
                  << (std::cin.good()?" good":"")
                  << (std::cin.bad()?" bad":"")
                  << (std::cin.fail()?" fail":"")
                  << (std::cin.eof()?" eof":"") << "\n";

        if(std::cin.eof())
        {
            std::cout << "Bye\n";
            return 0;
        }
        if(std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(99999, '\n');
            std::cout << "Invalid input\n";
            // note eof() can be true here
        }
    }
}

#include <fstream>

int read_balance(void)
{
    std::ifstream f;
    f.exceptions(std::ios::failbit | std::ios::badbit);
    f.open("shop-account.txt");
    int balance;
    f >> balance;
    f.close();
    return balance;
}

void write_balance(int balance)
{
    std::ofstream f;
    f.exceptions(std::ios::failbit | std::ios::badbit);
    f.open("shop-account.txt");
    f << balance;
    f.close();
}

