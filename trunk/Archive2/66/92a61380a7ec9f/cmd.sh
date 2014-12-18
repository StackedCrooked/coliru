clang++ -std=c++11 -stdlib=libc++ -O2 -Wall -pedantic main.cpp && { echo "*** clang & libc++ ***" ; ./a.out ; } >libc++.output
g++ -std=c++11 -O2 -Wall -pedantic main.cpp && { echo "*** gcc & stdlib++ ***" ; ./a.out ; }  >stdlibc++.output
diff -y stdlibc++.output libc++.output