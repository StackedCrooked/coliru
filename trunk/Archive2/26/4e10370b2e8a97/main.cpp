#include <queue>
#include <pthread.h>

class concurrent_queue
{

private:

    std::queue<unsigned char*> _queue_;
    pthread_mutex_t push_mutex;
    pthread_mutex_t pop_mutex;
    pthread_cond_t cond;

public:

    concurrent_queue()
    {
        pthread_mutex_init(&push_mutex, NULL);
        pthread_mutex_init(&pop_mutex, NULL);
        pthread_cond_init(&cond, NULL);
    }

    void push(unsigned char* data)
    {
        pthread_mutex_lock(&push_mutex);

        _queue_.push(data);

        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&push_mutex);
    }

    void pop(unsigned char** popped_data)
    {
        pthread_mutex_lock(&pop_mutex);

        while (_queue_.empty() == true)
        {
            pthread_cond_wait(&cond, &pop_mutex);
        }

        *popped_data = _queue_.front();
        _queue_.pop();

        pthread_mutex_unlock(&pop_mutex);
    }
};
void *consumer_thread(void *arguments)
{
    concurrent_queue *cq = static_cast<concurrent_queue*>(arguments);

    while (true)
    {
        unsigned char* data = NULL;

        cq->pop(&data);

        if (data != NULL)
        {
            // Eureka! Received from the other thread!!!
            // Delete it so memory keeps free.
            // NOTE: In the real scenario for which I need
            // this class, the data received are bitmap pixels
            // and at this point it would be processed

            delete[] data;
        }
    }

    return 0;
}
int main()
{
    concurrent_queue cq;

    // Create the consumer
    pthread_t consumer;
    pthread_create(&consumer, NULL, consumer_thread, &cq);

    // Start producing
    while(true)
    {
        // Push data. 
        // Expected behaviour: memory should never run out, as the
        // consumer should receive the data and delete it.
        // NOTE: test_data in the real purpose scenario for which I 
        // need this class would hold bitmap pixels, so it's meant to 
        // hold binary data and not a string

        unsigned char* test_data = new unsigned char [8192];
        cq.push(test_data);
    }

    return 0;
}

