set -x; g++ -std=c++11 -Os -Wall -pedantic -Wextra main.cpp && ./a.out && stat ./a.out
g++ -std=c++11 -Os -DSECOND -Wall -pedantic -Wextra main.cpp && ./a.out && stat ./a.out
g++ -std=c++11 -O0 -Wall -pedantic -Wextra main.cpp && ./a.out && stat ./a.out
g++ -std=c++11 -O0 -DSECOND -Wall -pedantic -Wextra main.cpp && ./a.out && stat ./a.out
g++ -std=c++11 -Os -DUSE_PTR -Wall -pedantic -Wextra main.cpp && ./a.out && stat ./a.out
g++ -std=c++11 -Os -DUSE_PTR -DSECOND -Wall -pedantic -Wextra main.cpp && ./a.out && stat ./a.out
g++ -std=c++11 -O0 -DUSE_PTR -Wall -pedantic -Wextra main.cpp && ./a.out && stat ./a.out
g++ -std=c++11 -O0 -DUSE_PTR -DSECOND -Wall -pedantic -Wextra main.cpp && ./a.out && stat ./a.out