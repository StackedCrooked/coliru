set +x;
printf "Without copy/swap: " ; g++ -std=c++11 -O2 -Wall -pedantic -pthread main.cpp && ./a.out
printf "With copy/swap: " ; g++ -std=c++11 -DUSE_COPY_SWAP -O2 -Wall -pedantic -pthread main.cpp && ./a.out