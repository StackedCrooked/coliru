//producer consumer
#include<iostream>
#include<unistd.h>
#include<semaphore.h>
#include<pthread.h>

using namespace std;

const int BUFFER_SIZE = 6;
sem_t fillCount, emptyCount;
pthread_mutex_t mutex;
int buffer[BUFFER_SIZE];

int out = 0;

void insertItem(int item)
{
    static int in = 0;
    buffer[in] = item;
    in = (in+1)%BUFFER_SIZE;
    cout << "producer produced " << item << endl;
}

void removeItem()
{
    static int out = 0;
    int item = buffer[out];
    out = (out+1)%BUFFER_SIZE;
    cout << "consumer consumed " << item << endl;
}

void *consumer(void *temp)
{
    while(true)
    {
        sem_wait(&fillCount);
        pthread_mutex_lock(&mutex);
        removeItem();
        pthread_mutex_unlock(&mutex);
        sem_post(&emptyCount);
    }
}
void *producer(void * temp)
{
    int item;
    while(true)
    {
        sem_wait(&emptyCount);
        item = rand()%100;
        pthread_mutex_lock(&mutex);
        insertItem(item);
        pthread_mutex_unlock(&mutex);
        sem_post(&fillCount);
    }
}

int main()
{
    sem_init(&fillCount, 0, 0); //middle 0 says that this mutex is only shared within this "process"
    sem_init(&emptyCount, 0, BUFFER_SIZE);
    pthread_mutex_init(&mutex, NULL);
    pthread_t th[8];
    for(int i=0;i<4;i++)
        pthread_create(&th[i], NULL, producer, NULL);
    for(int i=4;i<8;i++)
        pthread_create(&th[i], NULL, consumer, NULL);
        
    sleep(3);
}
            
    
    