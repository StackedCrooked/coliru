cat main.cpp | perl -p -e 's,_[A-Z]_,,g' | perl -p -e 's,\b__,,g' | perl -p -e 's,\b_([A-Z])(\w+),\L\1\l\2,g' > main2.cpp
diff -y main.cpp main2.cpp