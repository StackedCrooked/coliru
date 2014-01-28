ln -s main.cpp main.c
echo c89 && gcc -std=c89 -Wall -Wextra -pedantic-errors -c main.c && echo -e 'done!\n'
echo c99 && gcc -std=c99 -Wall -Wextra -pedantic-errors -c main.c && echo -e 'done!\n'
echo c1x && gcc -std=c1x -Wall -Wextra -pedantic-errors -c main.c && echo -e 'done!\n'
echo gnu89 && gcc -Wall -Wextra -pedantic-errors -c main.c && echo -e 'done!\n'