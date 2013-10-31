ln -s main.cpp ./main.s
gcc main.s -nostdlib -o a.out && ./a.out