#define Assert(cond) if ((!cond)) { \
        __builtin_trap(); \
    }

#define pthread_rwlock_wrlock(L) \
    std::cout << __FILE__ << ":" << __LINE__ << ": pthread_rwlock_wrlock" << std::flush; \
    Assert(L.__data.__nr_readers != 4294967294); \
    std::cout << "." << std::flush; \
    pthread_rwlock_wrlock(L); \
    std::cout << "." << std::flush; \
    Assert(L.__data.__nr_readers != 4294967294); \
    std::cout << "." << std::endl;


#define pthread_rwlock_unlock(L) \
    std::cout << __FILE__ << ":" << __LINE__ << ": unlock" << std::flush; \
    Assert(L.__data.__nr_readers != 4294967294); \
    std::cout << "." << std::flush; \
    pthread_rwlock_unlock(L); \
    std::cout << "." << std::flush; \
    Assert(L.__data.__nr_readers != 4294967294); \
    std::cout << "." << std::endl;
