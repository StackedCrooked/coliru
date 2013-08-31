#include <fstream>
#include <iostream>

int main()
{
    system("ps -o pid,comm,state,ppid,pgrp,session,tty > input.txt");

    try {
        std::ifstream file("input.txt");

        file.exceptions(std::ifstream::goodbit);

        std::string _, comm, state, ppid, pgrp, session, tty_nr;
        while (file >> _ >> comm >> state >> ppid >> pgrp >> session >> tty_nr)
        {
            for (auto&& s : { _, comm, state, ppid, pgrp, session, tty_nr })
                std::cout << s << "\t";
            std::cout << "\n";
        }
        file.close();
    } catch (const std::ifstream::failure& e) {
        std::cout << "Exception!!!! " << e.what();
    }
}
