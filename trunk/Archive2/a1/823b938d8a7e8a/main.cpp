#!/bin/bash

ln -s /Archive2/21/deff3f19530b38/main.cpp snapshot.h
ln -s /Archive2/b4/ff59564eb6d72c/main.cpp snapshot.cpp
ln -s /Archive2/a9/0969ae0e503fda/main.cpp main.cpp


by_val() { g++ -c -std=c++11 -O2 -fstrict-aliasing -Wall -pedantic  $1 ; }
by_ref() { g++ -c -std=c++11 -O2 -fstrict-aliasing -Wall -pedantic -DREF=1 $1 ; }

run_test() { 
    rm -f *.o
    rm -f a.out
    $1 main.cpp
    $1 snapshot.cpp
    g++ main.o snapshot.o
    for i in {1..4} ; do ./a.out ; done
}


printf "=== BENCHMARK ===\n"
run_test by_val
run_test by_ref

printf "\n\n=== SOURCES ===\n"
for file in snapshot.h snapshot.cpp main.cpp ; do
  printf "${file}:\n$(while IFS='' read line ; do echo "    $line" ; done <$file)\n\n"
done