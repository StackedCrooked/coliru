

#include <cstdint>
#include <vector>
#include <memory>
#include <iostream>
#include <mutex>
#include <thread>
#include <iostream>
#include <string>
#include <condition_variable>
#include <queue>
#include <chrono>
#include <iomanip>
#include <random>
#include <cmath>

/**
 * @brief Message interface
 */
class IMessage
{
public:
  virtual void Command(void) = 0;

  virtual ~IMessage(void) {}

};

/**
 * @brief Message for the active object queue to send a string to console
 */
class ConsoleMessage : public IMessage
{
public:
  ConsoleMessage(std::string ai_message)
    : m_message(ai_message)
  {

  }

  virtual void Command(void)
  {
    std::cout << m_message << std::endl;
  }
private:
  std::string m_message;
};

/**
 * @brief Guard message to signal end of active object
 */
class DoneMessage : public IMessage
{
public:
  DoneMessage(void){}
  virtual void Command(void) {}

};

/**
 * @brief A Thread Safe class using monitor object
 */
class TSQueue final
{
public:
  TSQueue() = default;
  TSQueue(const TSQueue&) = delete;
  TSQueue& operator=(const TSQueue&) = delete;
  /**
   * @brief Thread safe Put
   * @param[in] ai_message
   */
  void Put(IMessage* ai_message)
  {
    std::lock_guard<std::mutex> guard(m_monitor);
    PutImpl(ai_message);
    m_notEmpty.notify_one();
  }

  /**
   * @brief Thread safe Get
   * @return a message from the queue
   *
   * @note IF the queue is empty this method will block
   * on a condition variable until a new message arrives.
   */
  IMessage* Get(void)
  {
    std::lock_guard<std::mutex> guard(m_monitor);

    while(m_messageQueue.empty())
    {
      std::unique_lock<std::mutex> lock(m_monitor,std::adopt_lock);
      m_notEmpty.wait(lock);
    }
    return GetImpl();
  }

private:

  /// non-synch methods
  void PutImpl(IMessage* ai_message)
  {
    m_messageQueue.push(ai_message);
  }

  IMessage* GetImpl(void)
  {
    IMessage* m = m_messageQueue.front();
    m_messageQueue.pop();
    return m;
  }

  std::condition_variable m_notEmpty;
  std::mutex m_monitor;
  std::queue<IMessage*> m_messageQueue;
};

/**
 * @brief This class avoid problems with multiple threads sending logs.
 * @note It is an active object and a Singleton
 */
class SimpleThreadSafeLogger final
{
public:
  static SimpleThreadSafeLogger& GetInstance(void)
  {
    if (nullptr == s_instance)
    {
      s_instanceMutex.lock();
      if (nullptr == s_instance)
      {
        s_instance = new SimpleThreadSafeLogger();
        MarkForLaterDestruction(SimpleThreadSafeLogger::Destroy);
      }
      s_instanceMutex.unlock();
    }

    return *s_instance;
  }

  ~SimpleThreadSafeLogger(void);

  //void operator<< (const std::ostream& ai_data);
  void operator<< (const std::string& ai_data);

  void output(const std::string& ai_data);

private:
  SimpleThreadSafeLogger(void);
  SimpleThreadSafeLogger(const SimpleThreadSafeLogger&) = delete;
  SimpleThreadSafeLogger& operator=(const SimpleThreadSafeLogger&) = delete;

  typedef void (*DestroyHandler)(void);

  static void MarkForLaterDestruction(DestroyHandler handler);

  static void Destroy(void);

  static SimpleThreadSafeLogger* s_instance;
  static std::mutex s_instanceMutex;

  // working thread method
  void Scheduler(void);

  TSQueue m_messageQ;
  std::thread* m_workerThread;
  IMessage* m_doneMessage;
};




class Chopstick final
{
public:
  enum class State
  {
    PickedUp,
    PutDown
    };
  Chopstick(const uint32_t& ai_id);
  ~Chopstick(void);

  State GetStatus(void) const
  {
    return m_currentStatus;
  }
  void SetStatus(const State& ai_status)
  {
    m_currentStatus = ai_status;
  }
protected:
private:
  State m_currentStatus;
  const uint32_t m_id;
};

class ChopstickController
{
public:
  ChopstickController(const uint32_t& ai_numChopSticks);
  ~ChopstickController(void);

  void PickUp(const uint32_t& ai_id);
  void PutDown(const uint32_t& ai_id);

private:
  ChopstickController(const ChopstickController&) = delete;
  ChopstickController& operator=(const ChopstickController&) = delete;


  std::mutex m_monitor;
  std::vector<Chopstick*> m_chopsticks;
  uint32_t m_numChopSticks;
  std::vector<std::condition_variable*> m_cond;
};




class Philosopher final
{
public:
  Philosopher(const std::string& ai_name
              ,const uint32_t& ai_id
              , ChopstickController& ai_controller);
  ~Philosopher(void);

  void StartDinner(void);
  void WaitUntilFinishDinner(void);

private:
  Philosopher(const Philosopher& ai_rhs) = delete;
  Philosopher& operator=(const Philosopher& ai_rhs) = delete;

  void Dinner(void);

  std::string m_name;
  uint32_t m_id;
  std::thread* m_dinnerThread;
  ChopstickController& m_controller;

  void Eat(void);
  void Think(void);
  
};


class PhilosophersDinner
{
public:
  PhilosophersDinner(const std::uint32_t ai_numberOfDinningPhilosophers);
  ~PhilosophersDinner(void);

  /**
   * @brief Dinner
   *
   * @note This method blocks the current thread until dinner is over.
   */
  void Dinner(void);

private:
  typedef std::unique_ptr<Philosopher> PhilosopherPtr;
  ChopstickController m_controller;
  std::vector<PhilosopherPtr> m_philosophers;

  

};

//----------------------------------------------------------------------------
SimpleThreadSafeLogger* SimpleThreadSafeLogger::s_instance = nullptr;
std::mutex SimpleThreadSafeLogger::s_instanceMutex;

SimpleThreadSafeLogger::SimpleThreadSafeLogger(void)
  : m_workerThread(nullptr)
  , m_doneMessage(new DoneMessage())
{
  // std::cout << "*******************************************************" << std::endl;
  // std::cout << "SimpleThreadSafeLogger ctor" << std::endl;
  // std::cout << "*******************************************************" << std::endl;

  m_workerThread = new std::thread(&SimpleThreadSafeLogger::Scheduler,this);

}

SimpleThreadSafeLogger::~SimpleThreadSafeLogger(void)
{
  //std::cout << "SimpleThreadSafeLogger Dtor" << std::endl;

  if ( (nullptr != m_workerThread) &&
       (m_workerThread->joinable())
     )
  {
    m_messageQ.Put(m_doneMessage);
    m_workerThread->join();
  }

  delete m_doneMessage;
  m_doneMessage = nullptr;

  delete m_workerThread;
  m_workerThread = nullptr;
}

void SimpleThreadSafeLogger::output( const std::string &ai_data)
{
  ConsoleMessage* cm (new ConsoleMessage(ai_data));
  m_messageQ.Put(cm);
}
void SimpleThreadSafeLogger::operator <<(const std::string &ai_data)
{
#ifdef DEBUG_LOG
  ConsoleMessage* cm (new ConsoleMessage(ai_data));
  m_messageQ.Put(cm);
#endif
}

void SimpleThreadSafeLogger::MarkForLaterDestruction(SimpleThreadSafeLogger::DestroyHandler handler)
{
  std::atexit(handler);
}

void SimpleThreadSafeLogger::Destroy(void)
{
  if (nullptr != s_instance)
  {
    s_instanceMutex.lock();
    if (nullptr != s_instance)
    {
      delete s_instance;
      s_instance = nullptr;
    }
    s_instanceMutex.unlock();
  }
}

void SimpleThreadSafeLogger::Scheduler(void)
{
  IMessage* m(nullptr);
  while(  (m = m_messageQ.Get()) != m_doneMessage)
  {
    m->Command();
    delete m;
  }
}






Chopstick::Chopstick(const uint32_t &ai_id)
  : m_currentStatus(State::PutDown)
  , m_id(ai_id)
{
  SimpleThreadSafeLogger::GetInstance() << " Chopstick created" + std::to_string(m_id);
}

Chopstick::~Chopstick(void)
{
  SimpleThreadSafeLogger::GetInstance() << " Chopstick destroyed" + std::to_string(m_id);
  SimpleThreadSafeLogger::GetInstance() <<"End of Chopstick destroyed"  + std::to_string(m_id);
}

// void Chopstick::PickUp(void)
// {
//   SimpleThreadSafeLogger::GetInstance() << "Chopstick Pickup" + std::to_string(m_id) ;
//  // std::lock_guard<std::mutex> guard(m_monitorMutex);
//   std::unique_lock<std::mutex> lock(m_monitorMutex);

//   SimpleThreadSafeLogger::GetInstance() << "Chopstick Pickup inside block" + std::to_string(m_id);

//   while (state_PickedUp == m_currentStatus)
//   {
//     SimpleThreadSafeLogger::GetInstance() << "Chopstick Pickup is PickedUp" + std::to_string(m_id);
//     //std::unique_lock<std::mutex> lock(m_monitorMutex,std::adopt_lock);
//     SimpleThreadSafeLogger::GetInstance() << "Chopstick Pickup another lock?" + std::to_string(m_id);
//     m_isFree.wait(lock);
//     SimpleThreadSafeLogger::GetInstance() << "Chopstick Pickup awake" + std::to_string(m_id);
//   }
//   SimpleThreadSafeLogger::GetInstance() << "Chopstick Pickup impl" + std::to_string(m_id);
//   PickUp_impl();
//    SimpleThreadSafeLogger::GetInstance() << "Chopstick Pickup impl end of " + std::to_string(m_id);
// }


// void Chopstick::PutDown(void)
// {
//    SimpleThreadSafeLogger::GetInstance() << "Chopstick PutDown" + std::to_string(m_id);
//   std::lock_guard<std::mutex> guard(m_monitorMutex);
//   SimpleThreadSafeLogger::GetInstance() << "Chopstick PutDown inside block" + std::to_string(m_id);
//   SimpleThreadSafeLogger::GetInstance() << "Chopstick PutDown impl" + std::to_string(m_id);
//   PutDown_impl();
//   SimpleThreadSafeLogger::GetInstance() << "Chopstick PutDown impl" + std::to_string(m_id);
//   SimpleThreadSafeLogger::GetInstance() << "Chopstick PutDown notifying " + std::to_string(m_id);
//   m_isFree.notify_one();
//   SimpleThreadSafeLogger::GetInstance() << "Chopstick PutDown notified " + std::to_string(m_id);
// }

// std::string Chopstick::to_string() const
// {
//   return "Chopstick " + std::to_string(m_id);
// }

// inline void Chopstick::PickUp_impl(void)
// {
//   //can pickit up
//   m_currentStatus = state_PickedUp;
// }

// inline void Chopstick::PutDown_impl(void)
// {
//   m_currentStatus = state_PutDown;
// }







Philosopher::Philosopher(const std::string &ai_name, const uint32_t& ai_id, ChopstickController& ai_controller)
  :m_name(ai_name)
  ,m_id(ai_id)
  ,m_dinnerThread(nullptr)
  ,m_controller(ai_controller)
{
  SimpleThreadSafeLogger::GetInstance() << "Philosophers Ctor:" + m_name + std::to_string(m_id);
}

Philosopher::~Philosopher(void)
{
  SimpleThreadSafeLogger::GetInstance() << "Philosophers Dtor:" + m_name;
  if (nullptr != m_dinnerThread && m_dinnerThread->joinable())
    m_dinnerThread->join();
  delete m_dinnerThread;
  m_dinnerThread = nullptr;
  SimpleThreadSafeLogger::GetInstance() << "End of Philosophers Dtor:" + m_name;
}

void Philosopher::StartDinner(void)
{
  SimpleThreadSafeLogger::GetInstance() << m_name + "StartDinner ";
  m_dinnerThread = new std::thread(&Philosopher::Dinner,this);
  SimpleThreadSafeLogger::GetInstance() << m_name + "StartDinner end of ";
}

void Philosopher::WaitUntilFinishDinner(void)
{
  SimpleThreadSafeLogger::GetInstance() << m_name + "WaitUntilFinishDinner ";
  if(nullptr != m_dinnerThread)
  {
    SimpleThreadSafeLogger::GetInstance() << m_name + "WaitUntilFinishDinner waiting ...";
    m_dinnerThread->join();
  }
  else
  {
    SimpleThreadSafeLogger::GetInstance() << m_name + "WaitUntilFinishDinner::thread is null ";
  }
  SimpleThreadSafeLogger::GetInstance() << m_name + "WaitUntilFinishDinner end of";
}

void Philosopher::Think(void)
{
  std::random_device rd;

  std::default_random_engine e(rd());
  std::uniform_int_distribution<int> distro(1,3);
  int data = distro(e);
  SimpleThreadSafeLogger::GetInstance() << m_name + "  thinking for " + std::to_string(data);
  std::chrono::milliseconds thinktime(data*1000);
  std::this_thread::sleep_for(thinktime);
  SimpleThreadSafeLogger::GetInstance() << m_name + "  awake thinking";
}

void Philosopher::Eat(void)
{
  std::random_device rd;

  std::default_random_engine engine(rd());
  std::uniform_int_distribution<int> distro(1,2);
  int data = distro(engine);
  SimpleThreadSafeLogger::GetInstance() << m_name + "  eating for " + std::to_string(data);
  SimpleThreadSafeLogger::GetInstance().output("Philosopher "+ std::to_string (m_id)+" eats.");
  std::chrono::milliseconds eatingtime(data*1000);
  std::this_thread::sleep_for(eatingtime);
  SimpleThreadSafeLogger::GetInstance() << m_name + "  awake eating";
}

void Philosopher::Dinner(void)
{
  SimpleThreadSafeLogger::GetInstance() << m_name + "Enter dinner" ;

  for (int idx(0); idx < 5; ++idx)
  {
    SimpleThreadSafeLogger::GetInstance() << m_name + " idx: " + std::to_string(idx);
    Think();
    m_controller.PickUp(m_id);
    Eat();
    m_controller.PutDown(m_id);
  }

  SimpleThreadSafeLogger::GetInstance() << m_name + "Exit dinner"  ;


}






PhilosophersDinner::PhilosophersDinner(const std::uint32_t ai_numberOfDinningPhilosophers)
  : m_controller(ai_numberOfDinningPhilosophers)
{
  SimpleThreadSafeLogger::GetInstance() << "Entering Philosophers dinner ctor";
  

  const std::string base_name("ph");
  for (std::uint32_t idx(0); idx < ai_numberOfDinningPhilosophers; ++idx)
  {
    SimpleThreadSafeLogger::GetInstance() << "idx:" + std::to_string(idx);
    //emplace_back -> Construct in place => no copy, no move
    /// @see http://en.cppreference.com/w/cpp/container/vector/emplace_back

    m_philosophers.emplace_back(new Philosopher( base_name + std::to_string(idx),idx,m_controller));
  }
}

PhilosophersDinner::~PhilosophersDinner(void)
{
  SimpleThreadSafeLogger::GetInstance() << "PhilosophersDinner Dtor";
  
}

void PhilosophersDinner::Dinner(void)
{
  SimpleThreadSafeLogger::GetInstance() << "Entering PhilosophersDinner::Dinner";

  SimpleThreadSafeLogger::GetInstance().output("Dinner is starting!");
  for (auto iter= m_philosophers.begin(); iter != m_philosophers.end(); ++iter)
  {
    SimpleThreadSafeLogger::GetInstance() << "calling";
    (*iter)->StartDinner();
  }

  SimpleThreadSafeLogger::GetInstance() << "Philosophers Dinner::Dinner Started";

  for (auto iter= m_philosophers.begin(); iter != m_philosophers.end(); ++iter)
  {
    (*iter)->WaitUntilFinishDinner();
  }

}




ChopstickController::ChopstickController(const uint32_t& ai_numChopSticks)
  : m_numChopSticks(ai_numChopSticks)
{
  SimpleThreadSafeLogger::GetInstance() << "ChopstickController Dtor";
  for (std::uint32_t idx(0); idx < m_numChopSticks; ++idx)
  {
    m_chopsticks.emplace_back(new Chopstick(idx));
  }
  for (std::uint32_t idx(0); idx < m_numChopSticks; ++idx)
  {
    m_cond.emplace_back(new std::condition_variable());
  }
  
}
ChopstickController::~ChopstickController(void)
{
  SimpleThreadSafeLogger::GetInstance() << "ChopstickController Dtor";
  for(Chopstick* ch: m_chopsticks)
  {
    delete ch;
  }
  for(std::condition_variable* cond: m_cond)
  {
    delete cond;
  }
  
}

void ChopstickController::PickUp(const uint32_t& ai_id)
{
  SimpleThreadSafeLogger::GetInstance() << "ChopstickController::pickup " + std::to_string (ai_id);
  
  
  std::unique_lock<std::mutex> lock(m_monitor);
  const uint32_t left(ai_id%m_numChopSticks);
  const uint32_t right((ai_id+1)%m_numChopSticks);
  
  SimpleThreadSafeLogger::GetInstance() << "ChopstickController::pickup "+ std::to_string (ai_id) + " waiting for left " + std::to_string (left);

  
  while(Chopstick::State::PickedUp == m_chopsticks[left]->GetStatus())
  {
    m_cond[left]->wait(lock);
  }
  SimpleThreadSafeLogger::GetInstance() << "ChopstickController::pickup "+ std::to_string (ai_id)+" getting left " + std::to_string (left );
  SimpleThreadSafeLogger::GetInstance().output("Philosopher "+ std::to_string (ai_id)+" picks up left(" + std::to_string (left ) + ") chopstick");
  
  m_chopsticks[left]->SetStatus(Chopstick::State::PickedUp);
  
  SimpleThreadSafeLogger::GetInstance() << "ChopstickController::pickup "+ std::to_string (ai_id)+" waiting for right " + std::to_string (right );
  while(Chopstick::State::PickedUp == m_chopsticks[right]->GetStatus())
  {
    m_cond[right]->wait(lock);
  }
  
  SimpleThreadSafeLogger::GetInstance() << "ChopstickController::pickup "+ std::to_string (ai_id)+" getting right " + std::to_string (right );
  SimpleThreadSafeLogger::GetInstance().output("Philosopher "+ std::to_string (ai_id)+" picks up right(" + std::to_string (right ) + ") chopstick");
  m_chopsticks[right]->SetStatus(Chopstick::State::PickedUp);
}

void ChopstickController::PutDown(const uint32_t& ai_id)
{
  SimpleThreadSafeLogger::GetInstance() << "ChopstickController::putdown " + std::to_string (ai_id);
  std::lock_guard<std::mutex> guard(m_monitor);

  const uint32_t left(ai_id%m_numChopSticks);
  const uint32_t right((ai_id+1)%m_numChopSticks);
  
  SimpleThreadSafeLogger::GetInstance() << "ChopstickController::putdown "+ std::to_string (ai_id)+" left " + std::to_string (left );
  SimpleThreadSafeLogger::GetInstance().output("Philosopher "+ std::to_string (ai_id)+" puts down left("+ std::to_string (left )+") chopstick");
  m_chopsticks[left]->SetStatus(Chopstick::State::PutDown);
  m_cond[left]->notify_one();
  SimpleThreadSafeLogger::GetInstance() << "ChopstickController::putdown "+ std::to_string (ai_id)+"right " + std::to_string (right );
  SimpleThreadSafeLogger::GetInstance().output("Philosopher "+ std::to_string (ai_id)+" puts down right("+ std::to_string (right )+") chopstick");
  m_chopsticks[right]->SetStatus(Chopstick::State::PutDown);
  m_cond[right]->notify_one();
}


int main(void)
{
  SimpleThreadSafeLogger::GetInstance() << "Entering program";
  PhilosophersDinner dinner(5);
  dinner.Dinner();
  return 0;
}