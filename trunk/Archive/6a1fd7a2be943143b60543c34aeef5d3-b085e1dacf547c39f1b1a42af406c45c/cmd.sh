set +x
compile() { g++-4.8 -DCOUNT=${1} -std=c++11 -O2 -Wall -pedantic main.cpp && printf "${1}\t$(du -sh a.out)\n" ; }
printf "COUNT\tBINARY SIZE\n"
compile 0 ; compile 1 ; compile 2 ; compile 4 ; compile 8