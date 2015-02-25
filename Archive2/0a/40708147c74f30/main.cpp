#include <time.h>
#include <assert.h>
#include <iostream>
#include <iomanip>

int main(int argc, char **argv){
    assert(argc == 2);

	int offset = atoi(argv[1]);

	time_t t_now = time(NULL);

	struct tm me = *localtime(&t_now);

	struct tm him = me;
	him.tm_hour += offset;
	mktime(&him);

	for (int i = 0; i < 24; i++) {
		std::cout << std::put_time(&me, "%H");
		std::cout << std::put_time(&him, "\t%H\n");

		++me.tm_hour;
		++him.tm_hour;
		mktime(&me);
		mktime(&him);
	}
}
