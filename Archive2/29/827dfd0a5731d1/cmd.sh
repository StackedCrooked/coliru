clang++ -std=c++11 -O2 -I /usr/include/python2.7 -Wall -pedantic main.cpp -lboost_python -lpython2.7 -shared -fPIC -o pythonIterator.so
python2.7 <<HERE
import pythonIterator;
for i in pythonIterator.Foo(): 
    print i
HERE