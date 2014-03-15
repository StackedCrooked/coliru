#include <iostream>
#include <list>
#include <queue>
#include <memory>
#include <mutex>
#include <condition_variable>
#include <type_traits>
#include <assert.h>
#include <thread>
using namespace std;

//Очередь межпоточного взаимодействия для нового стандарта старше С++11. Примеры использования внизу.
//Вообще то что TUnboundedQueue - Unbounded - это плохо.
//Как-нибудь напишу TBoundedQueue. TUnboundedQueue могут приводить к исчерпанию памяти. Пока пользуйся этим.


struct TUnboundedQueueAbstractException : std::exception
{};

struct TUnboundedQueueTimeoutException : TUnboundedQueueAbstractException
{};

struct TUnboundedQueueClosedException : TUnboundedQueueAbstractException
{};

template<class TData>
class TUnboundedQueueForNonThrowMovable
{
    static_assert(::std::is_nothrow_move_constructible<TData>::value, "TData must be nonthrow movable type.");
    static_assert(!::std::is_array<TData>::value, "TData must not be c-array.");

public:
    typedef TData value_type;

private:
    typedef ::std::deque<TData> TQueue;
    typedef ::std::unique_lock<::std::mutex> TLock;
    TQueue _queue;
    mutable ::std::mutex _lockQueue;
    ::std::condition_variable _pushToQueue;
    bool _closed;

    TUnboundedQueueForNonThrowMovable(const TUnboundedQueueForNonThrowMovable&) = delete;
    TUnboundedQueueForNonThrowMovable(TUnboundedQueueForNonThrowMovable&&) = delete;
    TUnboundedQueueForNonThrowMovable& operator=(const TUnboundedQueueForNonThrowMovable&) = delete;
    TUnboundedQueueForNonThrowMovable& operator=(TUnboundedQueueForNonThrowMovable&&) = delete;
public:
    TUnboundedQueueForNonThrowMovable(void):_closed(false){}

    void close(void)    //Посылает всем ждущим на wait_and_pop исключение TUnboundedQueueClosedException.
    {					//Метод не ждет пока все слушатели очереди перестанут качать свои права на очередь и вызывать wait_and_pop. За этим следи сам.
        TLock lockerQueue(this->_lockQueue);
        this->_closed = true;
        this->_pushToQueue.notify_all();
    }

    void push_front(TData data)
    {
        TLock lockerQueue(this->_lockQueue);
        assert(!this->_closed);
        if(this->_closed)
            return;
        this->_queue.push_front(std::move(data));
        this->_pushToQueue.notify_one();
    }

    void push_back(TData data)
    {
        TLock lockerQueue(this->_lockQueue);
        assert(!this->_closed);
        if(this->_closed)
            return;
        this->_queue.push_back(std::move(data));
        this->_pushToQueue.notify_one();
    }

    bool emptyUnstable(void) const//Not recommended to use.
    {
        TLock lockerQueue(this->_lockQueue);
        return this->_queue.empty();
    }

    size_t sizeUnstable(void) const//Not recommended to use.
    {
        TLock lockerQueue(this->_lockQueue);
        return this->_queue.size();
    }

    void clear(void)//Not recommended to use.
    {
        TLock lockerQueue(this->_lockQueue);
        this->_queue.clear();
    }

    TData wait_and_pop(void)//throw(TUnboundedQueueClosedException)
    {
        return this->wait_and_pop_internal(
            [this](TLock& lockerQueue)
            {
                this->_pushToQueue.wait(lockerQueue, [this](){return this->testPushAndThrowIfClossed();});
            });
    }

    template< class Rep, class Period>
    TData wait_and_pop(const std::chrono::duration<Rep, Period> WaitDuration) //throw(TUnboundedQueueTimeoutException, TUnboundedQueueClosedException)
    {
        return this->wait_and_pop_internal(
            [this, WaitDuration](TLock& lockerQueue)
            {
                if(!this->_pushToQueue.wait_for(lockerQueue, WaitDuration, [this](){return this->testPushAndThrowIfClossed();}))
                    throw TUnboundedQueueTimeoutException();
            });
    }
	
    TData pop(void) //throw(TUnboundedQueueTimeoutException, TUnboundedQueueClosedException)
    {
        return this->wait_and_pop_internal(
            [this](TLock& lockerQueue)
            {
                if(!this->testPushAndThrowIfClossed())
                    throw TUnboundedQueueTimeoutException();
            });
    }

    TData waitCentiTimeoutPop(const unsigned int WaitTime) //throw(TUnboundedQueueTimeoutException, TUnboundedQueueClosedException)
    {
        return this->wait_and_pop<int ,  std::centi>(std::chrono::duration<int ,  std::centi> (WaitTime));
    }

private:
    template<class TWaitFunctor>
    TData wait_and_pop_internal(TWaitFunctor WaitFunctor)
    {
        TLock lockerQueue(this->_lockQueue);
        WaitFunctor(lockerQueue);
        const struct TExceptionSafety {
            TQueue& _queue;
            ::std::condition_variable& _pushToQueue;
            ~TExceptionSafety(){
                if(!this->_queue.empty())
                    this->_pushToQueue.notify_one();
            }
        } exceptionSafety = {_queue, _pushToQueue};//Use BOOST_SCOPE_EXIT, Luke!
        assert(!this->_queue.empty());
        TData result = std::move(this->_queue.front());
        this->_queue.pop_front();
        return result;
    }

    bool testPushAndThrowIfClossed(void) const
    {
        if(this->_closed)
            throw TUnboundedQueueClosedException();
        return !this->_queue.empty();
    }
};

template<class TData>
using TUnboundedQueueForUniquePtr = TUnboundedQueueForNonThrowMovable<std::unique_ptr<TData> >;
template<class TData>
using TUnboundedQueueForSharedPtr = TUnboundedQueueForNonThrowMovable<std::shared_ptr<const TData> >;
template<class TData>
using TUnboundedQueue = TUnboundedQueueForUniquePtr<TData>;//Советую пользоваться вот этим.

void get_some(TUnboundedQueue<int>& a){
	cout<<"get_some_enter"<<endl;
	auto c = a.wait_and_pop();
	assert(*c==5);
	cout<<"get_some_exit"<<endl;
}

int main(){
	TUnboundedQueue<int> a;
	unique_ptr<int> b(new int(5));
	cout<<"make_thread"<<endl;
	thread t(get_some, ref(a));
	cout<<"thread_maked"<<endl;
	chrono::milliseconds dura(200);
    this_thread::sleep_for(dura);
    cout<<"push_back_enter"<<endl;
	a.push_back(std::move(b));
	cout<<"push_back_exit"<<endl;
	t.join();
	cout<<"thread_joined"<<endl;
	return 0;
}