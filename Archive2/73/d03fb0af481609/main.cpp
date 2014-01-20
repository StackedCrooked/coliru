#include<stdio.h>
#include<pthread.h>

void produce(int *buf)
{
    
}

void consume(int *buf)
{
    
}

struct
{
    int buf[10];
    int *read;
    int *write;
} buffer;

int main()
{
 struct buffer buf;
 memcpy()
 pthread_t thread1, thread2;
 int r1 = pthread_create(&thread1, NULL, produce, buf);
 int r2 = pthread_create(&thread2, NULL, consume, buf);

 pthread_join(&thread1, NULL);
 pthread_join(&thread2, NULL);
 return 0;
}