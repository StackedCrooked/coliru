#include <fstream>
#include <iostream>

int main()
{
    //system("ps -o pid,comm,state,ppid,pgrp,session,tty > input.txt");
    system("od a.out -t x8 -Anone | xargs -n256 | tr -d ' ' | xargs -n7 | head -n100 > input.txt");
    system("echo 'too short' >> input.txt");

    try {
        std::ifstream file("input.txt");

        //file.exceptions(std::ifstream::badbit);
        file.exceptions(std::ifstream::goodbit);
        //file.exceptions(std::ifstream::eofbit);

        std::string _, comm, state, ppid, pgrp, session, tty_nr;
        while (file >> _ >> comm >> state >> ppid >> pgrp >> session >> tty_nr)
        {
            for (auto&& s : { _ , comm, state, ppid, pgrp, session, tty_nr })
                std::cout << s << "\t";
            std::cout << "\n";
        }
        file.close();
    } catch (const std::ifstream::failure& e) {
        std::cout << "Exception!!!! " << e.what();
    }
}
