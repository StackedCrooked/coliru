//thread in C
//wait is for process, join is for thread
#include<stdio.h>
#include<pthread.h>

struct data
{
    int n;
    char c;
};

void * print(void *st)
{
    data * d = (data *) st;
    int n = d->n;
    for(int i = 0; i< n; i++)
        printf("%c ", d->c);
    return NULL;
}
int main()
{
    pthread_t t1, t2;
    data t1_arg, t2_arg;
    setbuf(stdout, NULL);
    t1_arg.n = 500;
    t2_arg.n = 500;
    t1_arg.c = '1';
    t2_arg.c = '0';
    pthread_create(&t1, NULL, print, &t1_arg);
    pthread_create(&t2, NULL, print, &t2_arg);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
}