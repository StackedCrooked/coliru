echo -e "\ng++#######################################\n"
g++ -std=c++1y -Wall -Wextra -Wuninitialized -pedantic main.cpp && ./a.out
echo -e "\nclang++###################################\n"
clang++ -std=c++1y -Wall -Wextra -pedantic main.cpp -stdlib=libc++ && ./a.out