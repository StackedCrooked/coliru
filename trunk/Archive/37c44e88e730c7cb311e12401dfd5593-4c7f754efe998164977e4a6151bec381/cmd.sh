g++-4.8 -O3 -DUSE_ITERATOR -S main.cpp -o - > iterator
g++-4.8 -O3                -S main.cpp -o - > pointer

echo "''***********                                                  ************"
echo "  * pointer *                                                  * iterator *"
echo "  ***********                                                  ************"
echo 
diff -y pointer iterator 