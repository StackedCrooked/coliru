#include <mutex>
#include <atomic>

class MyMutexClass
{
    mutable std::mutex m_mutex;
    int m_value;
    
    public:
        void set(int value)
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            m_value = value;
        }

        int get() const
        {
            std::lock_guard<std::mutex> lock(m_mutex);            
            return m_value;
        }
        
        void increment()
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            ++m_value;
        }
};

class MyAtomicClass
{
    std::atomic<int> m_value;
    
    public:
        void set(int value)
        {
            m_value = value;
        }

        int get() const
        {
            return m_value;
        }
        
        void increment()
        {
            ++m_value;
        }
};

