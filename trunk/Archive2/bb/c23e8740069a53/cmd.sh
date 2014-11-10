clang++ -std=c++14 -stdlib=libc++ -O2 -Wall -Wextra -pedantic-errors main.cpp -lsupc++
./a.out <<< "All the world's a stage, And all the men and women merely players" 
echo 'example.txt contains:' && cat example.txt