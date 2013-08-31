g++-4.8 -O3 -DUSE_ITERATOR -S main.cpp -o - > iterator
g++-4.8 -O3                -S main.cpp -o - > pointer

echo "iterator								pointer"
echo "========								======="
diff -y iterator pointer

