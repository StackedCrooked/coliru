OPTIONS = -DCOLIRU_SANDBOX_MEMORY_LIMIT=10000000 -std=c++0x -Wall -Wextra -Werror

all:
	g++ ${OPTIONS} -fPIC -c malloc_hook.cpp
	g++ ${OPTIONS} -shared -Wl,-soname,malloc-sandbox -ldl -o libmalloc-sandbox.so malloc_hook.o
	g++ ${OPTIONS} -o test main.cpp
	LD_PRELOAD=./libmalloc-sandbox.so ./test || "Termination was intended!" 2>/dev/null || true
