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