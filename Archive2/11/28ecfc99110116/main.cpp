// I've had to comment out the task scheduler and provide a dummy definition for device_id_t,
// for exposition purposes.
typedef int device_id_t;

#include <iostream>
#include <map>
#include <boost/bimap.hpp>
#include <boost/bimap/set_of.hpp>
#include <boost/bimap/multiset_of.hpp>
#include <boost/lexical_cast.hpp>
using boost::lexical_cast;


/**
 * Defines a type representing a cross between a std::multimap<K,V> and a boost::bimap<K,V>.
 * Allows multiple values per key *and* lookup by both key and value, with the caveat that
 * the values must be unique (which is actually extremely convenient for us here). To insert
 * an element whose value already exists, first remove that item from the bimap.
 * 
 * Example:
 * 
 *   typedef bimultimap<int, int>::value_type value_type;
 *   typedef bimultimap<int, int>::left_map   left_map;
 *   typedef bimultimap<int, int>::right_map  right_map;
 *   bimultimap<int, int> bmm;
 * 
 *   // Insertion
 *   bmm.insert(value_type(1, 51));
 *   bmm.insert(value_type(1, 52));
 *   bmm.insert(value_type(2, 53));
 * 
 *   // Replacement
 *   bmm.right.erase(51);
 *   bmm.insert(value_type(3, 51));
 * 
 *   // Search for values by key (result is iterator to the start of elements with matching key)
 *   left_map::const_iterator it = bmm.left.find(1);
 *   {
 *       left_map::const_iterator it = bmm.left.find(1);
 *   	assert(it != bmm.left.end());
 *   	std::cout << it->second << '\n';  // 52
 *   }
 *   
 *   // Search for key by value (result is unique value)
 *   {
 *   	right_map::const_iterator it = bmm.right.find(52);
 *   	assert(it != bmm.right.end());
 *   	std::cout << it->second << '\n';  // 1
 *   }
 */
template <typename K, typename V>
struct bimultimap : boost::bimap<boost::bimaps::multiset_of<K>, boost::bimaps::set_of<V> > {};


/**
 * Periodically runs %ExecutionCallback on any scheduled device, after applying throttling logic.
 * 
 * A call to %tick() may result in one or more calls to %ExecutionCallback()(...).
 * It is expected that a call to %notify() is later made for each of those executions.
 * This mechanism relies on that to know when actions have completed.
 * 
 * Used to maintain periodic pings and state polls of devices without blowing up
 * application load at scale.
 * 
 * Requires the 'task-scheduler' component to exist in the Pigeon registry.
 * 
 * @param	Manager	The type of the owning component. It must have a 
 * @param	ExecutionCallback	A functor wrapping action execution. Should be stateless to allow inlining.
 * @param	DelayCallback	A functor returning preferred delay in seconds between actions.
 */
template <typename Manager, typename ExecutionCallback, typename DelayCallback>
struct AdaptiveScheduler
{
	static const unsigned int TICK_PERIOD  = 1;   /**< number of seconds between invocations of %tick() when idling */
	static const unsigned int THROTTLE     = 25;  /**< maximum size of each batch of action executions, in number of devices */
	
	
	AdaptiveScheduler(Manager* mgr)
		: mgr(mgr)
		//, ts(pigeon::registry::require<pigeon::task_scheduler>("task-scheduler"))
		//, tick_task()
	{
		tick();
	}
	
	~AdaptiveScheduler()
	{
		//ts.cancelScheduledTask(tick_task);
	}
	
	/**
	 * Adds the device with the given ID to the scheduling mechanism.
	 * 
	 * The proscribed action shall first be executed on this device as soon as possible.
	 * 
	 * If the device is already in the scheduling mechanism, its next action execution
	 * is brought forward.
	 */
	void addDevice(const device_id_t& device_id)
	{
		unscheduleAction(device_id);
		scheduleActionIn(device_id, 0);
	}
	
	/**
	 * Removes the device with the given ID from the scheduling mechanism.
	 */
	void removeDevice(const device_id_t& device_id)
	{
		unscheduleAction(device_id);
	}
	
	/**
	 * Must be invoked whenever an action has been completed (successfully or otherwise)
	 * on the device with the given ID.
	 * 
	 * Automatically invokes %tick() if no actions are left being executed.
	 * 
	 * Throws if %device_id has not previously been added to the scheduler with %addDevice.
	 */
	void notify(const device_id_t& device_id)
	{
		// (could be const_iterator in C++11)
		std::map<device_id_t, time_t>::iterator it = executing.find(device_id);
		if (it == executing.end())
			throw std::runtime_error("Could not find device " + lexical_cast<std::string>(device_id) + " in active-actions list");
		
		const time_t& ideal_time = it->second;
		const time_t next_time = ideal_time + getPreferredDelay(device_id);
		
		scheduleActionAt(device_id, next_time);
		executing.erase(it);
		
		if (executing.empty()) {
			//tick_task = ts.addScheduledTask(pigeon::scheduled_task(
			//	pigeon::rel_time(0),
			//	boost::bind(&AdaptiveScheduler::tick, this)
			//));
		}
	}
	
	
protected:
	
	/**
	 * Executes any due actions for known devices whose time has come, up to a maximum of
	 * %THROTTLE.
	 * 
	 * Automatically schedules a retry after a second if no actions are being executed
	 * (including any spawned by previous calls to %tick() by the time the function returns).
	 */
	void tick()
	{
		bimultimap<time_t, device_id_t>::left_map::iterator
			it     = schedule.left.begin(),
			cutoff = getDueEndIterator();
		
		// Execute as many queued polls as we have slots for
		assert(executing.size() <= THROTTLE);
		for (unsigned int n = 0; (n < THROTTLE - executing.size()) && (it != cutoff); ++n) {
			
			const time_t&      ideal_time = it->first;
			const device_id_t& device_id  = it->second;
			
			assert(executing.find(device_id) == executing.end());
			executing.insert(std::make_pair(device_id, ideal_time));
			runAction(device_id);
			
			
			// Remove queued poll -- a new one will be added back into the queue
			// on success or failure of this operation
			it = schedule.left.erase(it);
		}
		
		if (executing.empty()) {
			//tick_task = ts.addScheduledTask(pigeon::scheduled_task(
			//	pigeon::rel_time(TICK_PERIOD),
			//	boost::bind(&AdaptiveScheduler::tick, this)
			//));
		}
	}
	
	/**
	 * Marks the device with the given ID for actioning in %seconds_in_future seconds' time.
	 * Replaces any existing schedule for this device.
	 */
	void scheduleActionIn(const device_id_t& device_id, const time_t seconds_in_future)
	{
		timespec mt;
		clock_gettime(CLOCK_MONOTONIC, &mt);
		
		scheduleActionAt(device_id, mt.tv_sec+seconds_in_future);
	}
	
	/**
	 * Marks the device with the given ID for actioning when the monotonic system clock reaches
	 * %seconds seconds. Replaces any existing poll schedule for this device.
	 */
	void scheduleActionAt(const device_id_t& device_id, const time_t seconds)
	{
		typedef bimultimap<time_t, device_id_t>::value_type value_type;
		schedule.insert(value_type(seconds, device_id));
	}
	
	/**
	 * Unmarks the device with the given ID for actioning.
	 */
	void unscheduleAction(const device_id_t& device_id)
	{
		schedule.right.erase(device_id);
	}
	
	/**
	 * Executes the action for the given device.
	 */
	void runAction(const device_id_t& device_id)
	{
		ExecutionCallback()(mgr, device_id);
	}
	
	time_t getPreferredDelay(const device_id_t& device_id)
	{
		return DelayCallback()(mgr, device_id);
	}
	
	/**
	 * Returns %cutoff, an iterator into %schedule, such that `(schedule.begin(), %cutoff]`
	 * is a range describing queued actions whose time has come to be executed (modulo
	 * throttling).
	 */
	bimultimap<time_t, device_id_t>::left_map::iterator getDueEndIterator()
	{
		timespec mt;
		clock_gettime(CLOCK_MONOTONIC, &mt);
		
        return schedule.left.lower_bound(mt.tv_sec+1);
	}
	
	
private:
	
	Manager* const mgr;
	//pigeon::task_scheduler& ts;
	//pigeon::scheduled_task::id_t tick_task;
    friend class TestManager; // instead of a task scheduler, our Manager invokes %tick() a couple times for demo purposes
	
	std::map<device_id_t, time_t> executing;
	
	/**
	 * Using a bimultimap rather than a std::multimap allows us to do reverse
	 * lookup (i.e. lookup by device ID) quickly: inserting ([re]scheduling) in
	 * logarithmic time, and erase (unscheduling) in amortised O(1) time.
	 */
	bimultimap<time_t, device_id_t> schedule;
};

#define DECLARE_ADAPTIVE_SCHEDULER_EXECUTION_CALLBACK(mgr, name) \
	struct name { void operator()(mgr*, const device_id_t&); };

#define DECLARE_ADAPTIVE_SCHEDULER_DELAY_CALLBACK(mgr, name) \
	struct name { time_t operator()(mgr*, const device_id_t&); };



// Example usage

struct TestManager
{
    TestManager()
        : fooScheduler(this)
        , barScheduler(this)
    {
        fooScheduler.addDevice(42);
        barScheduler.addDevice(75);
        
        fooScheduler.tick();
        barScheduler.tick();
    }
    
    void doFoo(const device_id_t& device_id) {
        std::cout << "doFoo " << device_id << std::endl;
        fooScheduler.notify(device_id);
    }
    
    void doBar(const device_id_t& device_id) {
        std::cout << "doBar " << device_id << std::endl;
        barScheduler.notify(device_id);
    }
    
private:
    
    struct FooCallback {
        void operator()(TestManager* mgr, const device_id_t& device_id) {
            mgr->doFoo(device_id);
        }
    };
    
    struct FooDelay {
        time_t operator()(TestManager*, const device_id_t&) {
            // Doesn't in this example, but could depend on some value in
            // Manager, possibly dependant on the value of the second argument,
            // and possibly changing over time.
            return 10;
        }
    };
    
    struct BarCallback {
        void operator()(TestManager* mgr, const device_id_t& device_id) {
            mgr->doBar(device_id);
        }
    };
    
    struct BarDelay {
        time_t operator()(TestManager*, const device_id_t&) {
            return 1;
        }
    };
    
    
    AdaptiveScheduler<TestManager, FooCallback, FooDelay> fooScheduler;
    AdaptiveScheduler<TestManager, BarCallback, BarDelay> barScheduler;
};

int main()
{
    TestManager mgr;
    // Stuff here that keeps it alive and invokes tasks and things.
    // In reality there's an event loop and message dispatch and lovely
    // things like that.
}
