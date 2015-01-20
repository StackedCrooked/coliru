#include<iostream>
#include<unistd.h>
#include<pthread.h>

using namespace std;
pthread_mutex_t rd, wrt; // rd is just for synchronizing access to readCount
                           // wrt takes care that either there is one writer inside or many readers
string s = "rahul nangia";
int n = s.size();
int readCount = 0;


void *reader(void *t)
{
    pthread_mutex_lock(&rd);
    readCount++;
    if(readCount == 1)
        pthread_mutex_lock(&wrt);
    pthread_mutex_unlock(&rd);
    
    cout << "reader "<<s << endl;
    
    pthread_mutex_lock(&rd);
    readCount--;
    if(readCount == 0)
        pthread_mutex_unlock(&wrt);
    pthread_mutex_unlock(&rd);
    return NULL;
}

void *writer(void *t)
{
    pthread_mutex_lock(&wrt);
    s[rand()%n] = rand()%26 + 'a';
    s[rand()%n] = rand()%26 + 'a';
    s[rand()%n] = rand()%26 + 'a';
    cout << "writer " << s << endl;
    pthread_mutex_unlock(&wrt);
    return NULL;
}
    
int main()
{
    pthread_mutex_init(&wrt, NULL);
    pthread_mutex_init(&rd, NULL);
    
    pthread_t th[500];
    int i =0;
    while(i+1 < 500)
    {
        pthread_create(&th[i], NULL, writer, NULL);
        pthread_create(&th[i], NULL, reader, NULL);
    }
    sleep(15);
}
    