#include <iostream>
#include <pthread.h>
#include <unistd.h>

class LockGuard {
    public:
        LockGuard(pthread_mutex_t& mutex)
          : m(mutex)
        {
            pthread_mutex_lock(&m);
        }
        
        ~LockGuard()
        {
            pthread_mutex_unlock(&m);
        }
    private:
        pthread_mutex_t& m;
};

class Access {
    public:
        Access(std::string& message)
          : msg(message) {}
        
        virtual std::string read() const
        {
            return msg;
        }
        
        virtual void write(const std::string& new_msg)
        {
            msg = new_msg;
        }
        
    protected:
        std::string& msg;
};

class LockedAccess : public Access {
    public:
        LockedAccess(std::string& message)
          : Access(message) {}
        
        std::string read() const
        {
            LockGuard lock(mutex);
            return msg;
        }
        
        void write(const std::string& new_msg)
        {
            LockGuard lock(mutex);
            msg = new_msg;
        }
        
    private:
        mutable pthread_mutex_t mutex;
};

void* print_message_function(void* ptr)
{
    Access* accessor = static_cast<Access*>(ptr);
    int i = 3;
    while (i)
    {
        printf("i is %d ... %s \n", i, accessor->read().c_str());
        i--;
        sleep(1);
    }
    return NULL;
}

int main()
{
	std::string message1 = "Apple";
    std::string message2 = "Orange";
    Access unlocked_access(message2);
    LockedAccess locked_access(message1);
    
    pthread_t thread1, thread2, thread3;
    int iret1, iret2, iret3;
    
    iret1 = pthread_create(&thread1, NULL, print_message_function, static_cast<void*>(&locked_access));
    iret2 = pthread_create(&thread2, NULL, print_message_function, static_cast<void*>(&locked_access));
    iret3 = pthread_create(&thread3, NULL, print_message_function, static_cast<void*>(&unlocked_access));
    
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    
	return 0;
}