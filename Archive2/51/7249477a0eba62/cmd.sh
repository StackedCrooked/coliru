ln -s main.cpp main.c
echo -e '\n\nc89' && gcc -std=c89 -Wall -Wextra -pedantic-errors -c main.c && echo -e 'done!\n\n'
echo c99 && gcc -std=c99 -Wall -Wextra -pedantic-errors -c main.c && echo done!