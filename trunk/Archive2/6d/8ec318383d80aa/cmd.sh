g++ -std=c++14 -DUGLY_LOOP  -O2 -Wall -pedantic -pthread main.cpp -o ugly_loop
g++ -std=c++14 -DCLEAN_LOOP -O2 -Wall -pedantic -pthread main.cpp -o clean_loop
{ for i in {1..4} ; do ./clean_loop ; done ; for i in {1..4} ; do ./ugly_loop  ; done ; } | column -t