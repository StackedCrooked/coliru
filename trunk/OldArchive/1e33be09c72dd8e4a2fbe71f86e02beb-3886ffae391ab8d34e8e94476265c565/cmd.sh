g++-4.8 -O3 -DUSE_ITERATOR -fverbose-asm -S main.cpp -o - > iterator
g++-4.8 -O3                -fverbose-asm -S main.cpp -o - > pointer
echo "  * pointer *                                                  * iterator *"
diff -y pointer iterator | perl -p -e 's,ILi(\d+)EEvv,\1,g'



