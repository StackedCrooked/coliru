
//////////////////////////////////////
typedef std::function<void(int)> runnable_obj;

class CWSSThread
{
public:

    CWSSThread()
        :m_bThreadSign(true),m_TaskArray()
        ,m_Thread(&CWSSThread::threadMainFunction, this)
        ,m_Run(NULL)
    {}

    ~CWSSThread()
    {
        m_bThreadSign = false;
        m_ConditionVariable.notify_one();
        m_Thread.join();
    }

    void appendRunnableTask(runnable_obj run)
    {
        std::unique_lock<std::mutex> locker(m_ThreadMutex);
        m_TaskArray.push(run);
        m_ConditionVariable.notify_one();
    }

    size_t getTaskCount()
    {
        std::unique_lock<std::mutex> locker(m_ThreadMutex);
        return m_TaskArray.size();
    }

    bool isEmpty()
    {
        std::unique_lock<std::mutex> locker(m_ThreadMutex);
        return m_TaskArray.empty();
    }

    void Wait()
    {
        m_Thread.join();
    }

    void Stop()
    {
       m_bThreadSign = false;
       m_Run(eRUN_MODES::STOP);//StopRunnable
    }

private:

    std::condition_variable m_ConditionVariable;
    std::queue<runnable_obj>    m_TaskArray;
    runnable_obj                m_Run;

    enum eRUN_MODES {RUN=1, START, STOP};

    std::mutex                  m_ThreadMutex;
    std::thread                 m_Thread;
    bool                        m_bThreadSign;

    void threadMainFunction();
};



void CWSSThread::threadMainFunction()
{
    while (m_bThreadSign)
    {
        std::unique_lock<std::mutex> locker(m_ThreadMutex);
        // Ожидаем уведомления, и убедимся что это не ложное пробуждение
        // Поток должен проснуться если очередь не пустая либо он выключен
        m_ConditionVariable.wait(locker, [&](){ return !m_TaskArray.empty() || !m_bThreadSign; });
        while(!m_TaskArray.empty())
        {
            if(!m_bThreadSign)
            {
                while(!m_TaskArray.empty())
                {
                    runnable_obj run = m_TaskArray.front();//get task from array
                    m_TaskArray.pop();
                    run(eRUN_MODES::STOP);
                }
                return;
            }

            m_Run = m_TaskArray.front();//get task from array
            m_TaskArray.pop();

            locker.unlock();//unlock before task call
            m_Run(eRUN_MODES::RUN);
            locker.lock(); // lock before fqueue.empty()
        }
    }
}

typedef std::shared_ptr<CWSSThread> wss_thread_ptr;

template<class _T>
struct AData
{
    AData():ready(false){}
    bool ready;
    _T data;
};



/////////////////////////////////
class CWSSThreadPool
{
private:
    CWSSThreadPool(size_t a_iThreadsCount = 1)
    {
        m_iThreadsCount = a_iThreadsCount;
        if (a_iThreadsCount==0)
            m_iThreadsCount=1;

        for (size_t i=0; i<m_iThreadsCount; i++)
        {
            wss_thread_ptr pThread(new CWSSThread);
            m_ThreadsArray.push_back(pThread);
        }
    }
    ~CWSSThreadPool() {}

public:
    static void startThreadPool(int a_iThreadsCount = 1)
    {
        CWSSThreadPool::getInstance(a_iThreadsCount);
    }

    static void stopThreadPool()
    {
        CWSSThreadPool::getInstance().stopAll();
        CWSSThreadPool::getInstance().waitAll();
    }

    static CWSSThreadPool& getInstance(int a_iThreadsCount = 0)
    {
        static CWSSThreadPool pool(a_iThreadsCount);
        return pool;
    }


    template<class _R, class _RUN, class... _ARGS>
    static std::shared_ptr<AData<_R> > launchRunnableObject(_RUN* _run, _ARGS... _args)
    {
     //   std::function<_R()> bind_run = std::bind(&_RUN::run(), *_run, _args...);

        std::shared_ptr<AData<_R> > pData(new AData<_R>());
        runnable_obj run_lambda = [=](int a_iMode)
        {
            if(a_iMode == CWSSThread::eRUN_MODES::RUN)
            {
                pData->data = _run->run(_args...);
                // bind_run();
            }
            else if(a_iMode == CWSSThread::eRUN_MODES::STOP)
            {
                _run->StopRunnable();
            }
            else if(a_iMode == CWSSThread::eRUN_MODES::START)
            {
                _run->StartRunnable();
            }

            pData->ready = true;
        };
        getInstance().getFreeThread()->appendRunnableTask(run_lambda);
        return pData;
    }

    wss_thread_ptr getFreeThread();

    void stopAll()
    {
        for (auto &it : m_ThreadsArray)
        {
            return it->Stop();
        }
    }

    void waitAll()
    {
        for (auto &it : m_ThreadsArray)
        {
            return it->Wait();
        }
    }

private://fields
    std::vector<wss_thread_ptr> m_ThreadsArray;
    int m_iThreadsCount;

};


wss_thread_ptr CWSSThreadPool::getFreeThread()
{
    wss_thread_ptr pThread;
    size_t minTasks = UINT32_MAX;
    for (auto &it : m_ThreadsArray)
    {
        if (it->isEmpty())
        {
            return it;
        }
        else if (minTasks > it->getTaskCount())
        {
            minTasks = it->getTaskCount();
            pThread = it;
        }
    }
    return pThread;
}


class IWSSRunnable
{
public:
    IWSSRunnable(){}
    virtual ~IWSSRunnable(){}
    virtual int run() = 0;
    virtual void StartRunnable() = 0;
    virtual void StopRunnable() = 0;
};


template<typename T>
class CWSSRunnable:public IWSSRunnable
{
    typedef int (T::*StartFunction)();
    int threadID;
    T* m_pProcessor;
    StartFunction Start;

public:

    CWSSRunnable(T* a_Processor, StartFunction a_StartF):m_pProcessor(a_Processor), Start(a_StartF)
    {
        threadID = 1;
    }

    virtual ~CWSSRunnable(){;}

    int run()
    {
        return (m_pProcessor->*Start)();
    }

    void StartRunnable()
    {

    }

    void StopRunnable()
    {

    }

private:

};


int CBaseObject::Start()
{        

    m_pThreadMain = new CWSSRunnable<CBaseProcessor>(GetProcessor(), &CBaseProcessor::MainWork);
    m_pThreadSG = new CWSSRunnable<CBaseHandlerMsg>(GetMSGHandler(), &CBaseHandlerMsg::AnalizeMessagesSG);
    m_pThreadMCC = new CWSSRunnable<CBaseHandlerMsg>(GetMSGHandler(), &CBaseHandlerMsg::AnalizeMessagesMCC);
    
    GetProcessor()->SetFlagMainWork();
    GetMSGHandler()->SetFlagSG();
    GetMSGHandler()->SetFlagMCC();

    CWSSThreadPool::launchRunnableObject<int, CWSSRunnable<CBaseProcessor>>(m_pThreadMain);
    CWSSThreadPool::launchRunnableObject<int, CWSSRunnable<CBaseHandlerMsg>>(m_pThreadSG);
    CWSSThreadPool::launchRunnableObject<int, CWSSRunnable<CBaseHandlerMsg>>(m_pThreadMCC);

    SetObjectState(PWRON);
    return 0;
}