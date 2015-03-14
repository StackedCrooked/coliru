set -x; 
g++ -std=c++11 -O0 -Wall -pedantic -Wextra main.cpp && ./a.out; SZ1=`stat -c "%s" ./a.out`
g++ -std=c++11 -O0 -DSECOND -Wall -pedantic -Wextra main.cpp && ./a.out; SZ2=`stat -c "%s"  ./a.out`; expr $SZ2 - $SZ1
g++ -std=c++11 -O3 -Wall -pedantic -Wextra main.cpp && ./a.out; SZ1=`stat -c "%s" ./a.out`
g++ -std=c++11 -O3 -DSECOND -Wall -pedantic -Wextra main.cpp && ./a.out; SZ2=`stat -c "%s"  ./a.out`; expr $SZ2 - $SZ1
g++ -std=c++11 -O0 -DUSE_PTR -Wall -pedantic -Wextra main.cpp && ./a.out; SZ1=`stat -c "%s" ./a.out`
g++ -std=c++11 -O0 -DUSE_PTR -DSECOND -Wall -pedantic -Wextra main.cpp && ./a.out; SZ2=`stat -c "%s"  ./a.out`; expr $SZ2 - $SZ1
g++ -std=c++11 -O3 -DUSE_PTR -Wall -pedantic -Wextra main.cpp && ./a.out; SZ1=`stat -c "%s" ./a.out`
g++ -std=c++11 -O3 -DUSE_PTR -DSECOND -Wall -pedantic -Wextra main.cpp && ./a.out; SZ2=`stat -c "%s"  ./a.out`; expr $SZ2 - $SZ1