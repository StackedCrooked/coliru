#include <cstdlib>
#include <pthread.h>
#include <unistd.h>


static pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t c = PTHREAD_COND_INITIALIZER;


void test() noexcept
{
    try 
    {
        pthread_mutex_lock(&m);
        pthread_cond_wait(&c, &m);
        pthread_cond_wait(&c, &m);
    }
    catch (...)
    {
    }
}


static void *tf (void *)
{
    test();
    return nullptr;
}


int main ()
{
    pthread_t t;
    pthread_create(&t, NULL, tf, NULL);
    sleep(1);
    pthread_cancel(t);
    pthread_join(t, NULL);
}
