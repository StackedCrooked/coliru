clang++ -std=c++14 -O2 -I/usr/include/python2.7 -Wall -pedantic main.cpp -lboost_python -lpython2.7 -shared -fPIC -o example.so
python2.7 <<EOF
import example
assert(example.func(type("test")) == -1)
assert(example.func(example.A) == 0)
assert(example.func(example.B) == 1)
assert(example.isSubclassA(example.A))
assert(example.isSubclassA(example.B))
assert(not example.isSubclassA(example.C))
assert(example.func("test") == -1)
assert(example.func(example.A()) == 0)
assert(example.func(example.B()) == 1)
assert(example.isSubclassA(example.A()))
assert(example.isSubclassA(example.B()))
assert(not example.isSubclassA(example.C()))
EOF
echo $?