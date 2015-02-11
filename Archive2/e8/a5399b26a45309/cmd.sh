g++ -std=c++11 -DSORT=0 -O2 -Wall -pedantic -pthread main.cpp -o no_sort
g++ -std=c++11 -DSORT=1 -O2 -Wall -pedantic -pthread main.cpp -o yes_sort
for i in {1..5} ; do ./no_sort  | column -t > a ; ./yes_sort | column -t > b ; cat a b | column -t ; done | sort