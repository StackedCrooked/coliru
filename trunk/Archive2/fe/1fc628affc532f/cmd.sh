set -x; 
g++ -std=c++1y -O0 -Wall -pedantic -Wextra main.cpp && ./a.out; SZ1=`stat -c "%s" ./a.out`
g++ -std=c++1y -O0 -DSECOND -Wall -pedantic -Wextra main.cpp && ./a.out; SZ2=`stat -c "%s"  ./a.out`; expr $SZ2 - $SZ1
g++ -std=c++1y -O3 -Wall -pedantic -Wextra main.cpp && ./a.out; SZ1=`stat -c "%s" ./a.out`
g++ -std=c++1y -O3 -DSECOND -Wall -pedantic -Wextra main.cpp && ./a.out; SZ2=`stat -c "%s"  ./a.out`; expr $SZ2 - $SZ1
g++ -std=c++1y -O0 -DUSE_PTR -Wall -pedantic -Wextra main.cpp && ./a.out; SZ1=`stat -c "%s" ./a.out`
g++ -std=c++1y -O0 -DUSE_PTR -DSECOND -Wall -pedantic -Wextra main.cpp && ./a.out; SZ2=`stat -c "%s"  ./a.out`; expr $SZ2 - $SZ1
g++ -std=c++1y -O3 -DUSE_PTR -Wall -pedantic -Wextra main.cpp && ./a.out; SZ1=`stat -c "%s" ./a.out`
g++ -std=c++1y -O3 -DUSE_PTR -DSECOND -Wall -pedantic -Wextra main.cpp && ./a.out; SZ2=`stat -c "%s"  ./a.out`; expr $SZ2 - $SZ1