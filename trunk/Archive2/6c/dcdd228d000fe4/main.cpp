#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define BUF_LENGTH_VALUE 64

typedef struct
{
    pthread_mutex_t input_lock;
    pthread_cond_t input_cond;
    size_t n_bytes;
    int finished;
    unsigned char in_buf[BUF_LENGTH_VALUE];
} pthread_data_t;

// producer thread
void * produce_bytes(void *t_data)
{
    pthread_data_t *d = (pthread_data_t *)t_data;
    d->finished = 0;
    
    pthread_mutex_lock(&d->input_lock);
    while (1)
    {
        unsigned char in_buf[BUF_LENGTH_VALUE];
        size_t n_bytes = 0;
        
        // read without a latch.
        pthread_mutex_unlock(&d->input_lock);
        n_bytes = fread(in_buf, sizeof(in_buf[0]), sizeof(in_buf), stdin);
        pthread_mutex_lock(&d->input_lock);
        
        // only post if we read actual data.
        if (n_bytes > 0)
        {
            // wait for space to become available.
            while (d->n_bytes != 0)
                pthread_cond_wait(&d->input_cond, &d->input_lock);

            // we have a zero-buffer.
            memcpy(d->in_buf, in_buf, n_bytes);
            d->n_bytes = n_bytes;
            
            fprintf(stdout, "PRODUCER ...signaling consumer...\n");
            pthread_cond_signal(&d->input_cond);
        }
        else if (feof(stdin) || ferror(stdin))
            break;
    }
    
    // still have the mutex locked. set finished state and
    //  signal the connsumer its time to shutdown
    d->finished = 1;
    pthread_mutex_unlock(&d->input_lock);
    pthread_cond_signal(&d->input_cond);
    return NULL;
}

void* consume_bytes(void *t_data)
{
    pthread_data_t *d = (pthread_data_t *)t_data;
    
    pthread_mutex_lock(&d->input_lock);
    while (1)
    {
        // wait until data is available or we're finished
        while (d->n_bytes == 0 && !d->finished)
            pthread_cond_wait(&d->input_cond, &d->input_lock);
        
        if (d->n_bytes)
        {
            fprintf(stdout, "CONSUMER ...received %zu bytes\n", d->n_bytes);

            // reset the buffer and signal the producer more space
            //  is available for producing more data.
            d->n_bytes = 0;
            pthread_cond_signal(&d->input_cond);
        }
        
        if (d->finished)
            break;
    }
    
    // still have the mutex locked. unlatch it.
    pthread_mutex_unlock(&d->input_lock);
    return NULL;
}

int main()
{
    pthread_t producer_thread;
    pthread_t consumer_thread;
    
    pthread_data_t td = {0};
    pthread_mutex_init(&td.input_lock, NULL);
    pthread_cond_init(&td.input_cond, NULL);
    
    pthread_create(&producer_thread, NULL, produce_bytes, &td);
    pthread_create(&consumer_thread, NULL, consume_bytes, &td);
    
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);
    
    return EXIT_SUCCESS;
}
