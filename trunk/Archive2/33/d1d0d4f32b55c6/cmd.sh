ln -s main.cpp main.c
echo '---- clang c90 pedantic errors ------------' && clang -std=c90 -O2 -Wall -Wextra -pedantic-errors -c main.c 
echo '---- gcc c90 pedantic errors ------------' && gcc -std=c90 -O2 -Wall -Wextra -pedantic-errors -c main.c 
echo '---- clang c90 pedantic ------------' && clang -std=c90 -O2 -Wall -Wextra -pedantic -c main.c 
echo '---- clang c90 pedantic ------------' && gcc -std=c90 -O2 -Wall -Wextra -pedantic -c main.c