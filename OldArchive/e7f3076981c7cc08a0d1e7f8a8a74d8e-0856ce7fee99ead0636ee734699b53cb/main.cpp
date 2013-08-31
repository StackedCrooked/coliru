#include <iostream>
#include <string>
#include <boost/thread.hpp>
#include <boost/chrono.hpp>
#include <boost/date_time.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <boost/atomic.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <list>

using namespace std;
using namespace boost;
using namespace boost::interprocess;


class TaskManager
{
public:
    TaskManager();
    virtual ~TaskManager();
    void start();

private:
    boost::thread_group m_threadGroup;

};

enum JobState {
    JS_NEW          = 0,
    JS_PAUSED       = 1,
    JS_CANCELLED    = 2,
    JS_DONE         = 3,
    JS_CHECKING     = 4,
    JS_WARCHIVE     = 5,
    JS_CHECKINGWA   = 6,
    JS_FILENOTFOUND = 7
};

struct JobData {
    string    jobId;
    JobState  jobState;
    string    in;
    string    out;
    string    arc;
    uint64_t  retryCount;
    uint64_t  maxRetryCount;
    uint64_t  lastExecTime;
    uint64_t  retryTimeout;

    JobData() :
        jobId(uuids::to_string(uuids::random_generator()())),
        jobState(JS_NEW),
        in(""),
        out(""),
        arc(""),
        retryCount(0),
        maxRetryCount(5),
        lastExecTime(1),
        retryTimeout(10000)
    {}

    JobData(const JobData &jd) :
        jobId(jd.jobId),
        jobState(jd.jobState),
        in(jd.in),
        out(jd.out),
        arc(jd.arc),
        retryCount(jd.retryCount),
        maxRetryCount(jd.maxRetryCount),
        lastExecTime(jd.lastExecTime),
        retryTimeout(jd.retryTimeout)
    {}

    JobData& operator=(const JobData &jd)
    {
        if (this == &jd)
            return *this;
        jobId         = jd.jobId;
        jobState      = jd.jobState;
        in            = jd.in;
        out           = jd.out;
        arc           = jd.arc;
        retryCount    = jd.retryCount;
        maxRetryCount = jd.maxRetryCount;
        lastExecTime  = jd.lastExecTime;
        retryTimeout  = jd.retryTimeout;
        return *this;
    }

    bool operator==(const JobData &second) const
    {
        return (jobId == string("empty") || second.jobId == string("empty")) ? false : jobId == second.jobId;
    }
};

class ThreadedList
{
public:
    ThreadedList();
    ~ThreadedList();
    JobData getJob();
    bool addJob(const JobData job);
    bool addJob(const string job); //
    void updateJob(const JobData job);
    list<string> data() const { return m_jobLst; }

private:
    list<JobData>  m_jobList;
    list<string>   m_jobLst; //
    boost::mutex   m_mutex;

};

ThreadedList::ThreadedList()
{
}

ThreadedList::~ThreadedList()
{
}

JobData ThreadedList::getJob()
{
    scoped_lock<boost::mutex> locker(m_mutex);
    for (JobData jb : m_jobList) {
        if ((jb.jobState == JS_NEW) ||
                        (((jb.jobState == JS_PAUSED) || (jb.jobState == JS_WARCHIVE))
                         && ((jb.lastExecTime + jb.retryTimeout) < 0 /** @todo FIXME current time m_sec from epoch*/))) {
             jb.jobState = (jb.jobState == JS_WARCHIVE) ? JS_CHECKINGWA : JS_CHECKING;
             return jb;
        }
    }
    JobData job;
    job.jobId = string("empty");
    return job;
}

bool ThreadedList::addJob(const JobData job)
{
    scoped_lock<boost::mutex> locker(m_mutex);
/*    if (job.in.(string(".partial")))
        return false;*/ /** @todo TODO .partial endsWith*/
    for (JobData jb : m_jobList) {
        if (jb.in == job.in)
            return false;
    }
    m_jobList.push_back(job);
    return true;
}

bool ThreadedList::addJob(const string job)
{
    scoped_lock<boost::mutex> locker(m_mutex);
    m_jobLst.push_back(job);
}

void ThreadedList::updateJob(const JobData job)
{
    scoped_lock<boost::mutex> locker(m_mutex);
    for (JobData jb : m_jobList) {
        if (jb.jobId == job.jobId) {
            jb.lastExecTime = job.lastExecTime;
            jb.retryCount = job.retryCount;
            jb.jobState = job.jobState;
            return;
        }
    }
}

class TaskExecuter
{
public:
    TaskExecuter(const int tid);
    virtual ~TaskExecuter();
    void operator()();
    void setList(ThreadedList *lst);

private:
    JobData       m_job;
    int           m_id;
    ThreadedList* m_jobList;

    void proceedJob();
    bool copyToArchive();

};

TaskExecuter::TaskExecuter(const int tid) : m_id(tid)
{
}

TaskExecuter::~TaskExecuter()
{
}

void TaskExecuter::operator()()
{
    string strt;
    {
        stringstream ss;
        ss << string("Started_") << m_id;
        ss >> strt;
    }
    using namespace posix_time;
    for (int i = 0; i < 5; ++i) {
        string str = strt + " " + (to_simple_string(microsec_clock::local_time()) + "\n\r");;
        this_thread::sleep_for(chrono::duration<int, milli>(250));
        m_jobList->addJob(str);
    }
}

void TaskExecuter::setList(ThreadedList* lst)
{
    m_jobList = lst;
}

void TaskExecuter::proceedJob()
{
}

bool TaskExecuter::copyToArchive()
{
    return true;
}

TaskManager::TaskManager()
{
}

TaskManager::~TaskManager()
{
    m_threadGroup.interrupt_all();
}

void TaskManager::start()
{
    ThreadedList lst;
    for (int i = 0; i < 5; ++i) {
        TaskExecuter tex(i);
        tex.setList(&lst);
        m_threadGroup.create_thread(tex);
    }

    chrono::duration<uint32_t, milli> d(1000);
    for (int i = 0; i < 5; i++) {
        cout << "std called\n\r";
        this_thread::sleep_for(d);
    }

    for (auto str : lst.data()) {
        cout << str;
    }
}

int main()
{
    TaskManager manager;
    manager.start();
    return 0;
}