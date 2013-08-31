set -x
g++-4.8 -O3 -DUSE_ITERATOR -fverbose-asm -S main.cpp -o - > iterator
g++-4.8 -O3                -fverbose-asm -S main.cpp -o - > pointer

cat iterator
cat pointer

