f() { g++-4.8 main.cpp -S -DAND -O3 -o main1 && g++-4.8 main.cpp -S -DMOD -O3 -o main2 && diff --side-by-side -s main1 main2 ; }
declare -f f ; f