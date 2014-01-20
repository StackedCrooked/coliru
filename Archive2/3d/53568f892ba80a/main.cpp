#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<string.h>

void lock_mutex()
struct buffer
{
    int buf[10];
    int *read;
    int *write;
    void (*lock)(
};

void* produce(void *bufIn)
{
    struct buffer *buf = (struct buffer*)(bufIn);
    return (void*)0;
}

void* consume(void *buf)
{
    struct buffer *buf = (struct buffer*)(bufIn);
    return (void*)0;
}

void init_buffer(struct buffer *buf)
{
    memset(buf->buf, 0, sizeof(buf->buf));
    buf->read = buf->buf;
    buf->write = buf->buf;       
}

int main()
{
    struct buffer buf;
    init_buffer(&buf);
    
    pthread_t thread1, thread2;
    int r1 = pthread_create(&thread1, NULL, produce, (void*)&buf);
    int r2 = pthread_create(&thread2, NULL, consume, (void*)&buf);
    
    pthread_join(&thread1, NULL);
    pthread_join(&thread2, NULL);
    return 0;
}