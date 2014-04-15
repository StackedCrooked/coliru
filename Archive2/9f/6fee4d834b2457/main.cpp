#include  <stdio.h>
#include  <string.h>
#include  <stdlib.h>
#include  <pthread.h>

struct test {
    char str[32];
	int x;
};

void *tfunc(void*) {
	struct test *eg = (struct test *)malloc(sizeof(struct test));
	strcpy(eg->str,"hello world");
	eg->x = 666;
	pthread_exit(eg);
}


int main (void) {
	pthread_t id;
	struct test *resp;

	pthread_create(&id,NULL,tfunc,NULL);
	pthread_join(id,(void**)&resp);

	printf("%s %d\n",resp->str,resp->x);

	free(resp);

	return 0;
}