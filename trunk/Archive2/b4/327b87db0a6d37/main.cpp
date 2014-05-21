template <typename T>
class Singleton
{
    Singleton(){}; // so we cannot accidentally delete it via pointers
    Singleton(const Singleton&) = delete; // no copies
    Singleton& operator=(const Singleton&) = delete; // no self-assignments
    Singleton(Singleton&&) = delete; // WHY?
//    Singleton& operator=(Singleton&&) = delete; // WHY?
public:
    static T& getInstance() // singleton
    {
        static T instance; // Guaranteed to be destroyed.
                       // Instantiated on first use.
                       // Thread safe in C++11
        return instance;
    }
};

int main() {
    Singleton<int>::getInstance() = Singleton<int>::getInstance();   
}