ln -s main.cpp main.c
echo -e 'C\n----'
time gcc -std=c1x -O2 -Wall -Wextra -pedantic-errors main.c -o c.out
du C
----

real	0m0.149s
user	0m0.032s
sys	0m0.072s
8077	c.out
Enter the number : 
you entered: 12345
please type in your first name: 
Hello engr

real	0m0.003s
user	0m0.000s
sys	0m0.000s

C++
----

real	0m0.637s
user	0m0.484s
sys	0m0.144s
13857	cpp.out
Enter the number :
you entered: 12345
Enter your first name :
Hello engr

real	0m0.005s
user	0m0.000s
sys	0m0.004s
-b c.out
time ./c.out <<< '12345 engr'
echo -e '\nC++\n----'
time g++-4.8 -std=c++11 -O2 -Wall -Wextra -pedantic-errors main.cpp -o cpp.out
du -b cpp.out
time ./cpp.out <<< '12345 engr'