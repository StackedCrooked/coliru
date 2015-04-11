
#include <chrono>
#include <cstdlib>
#include <functional>
#include <memory>
#include <thread>
#include <tuple>
#include <vector>

template<typename... Args>
    	class CallbackBase{
		public:
			virtual void Call(std::tuple<Args...> arg_tuple) = 0;
			virtual bool On() = 0;
			virtual void Off() = 0;
		};

		template<typename ClassName, typename... Args>
		class CallbackDerived : public CallbackBase<Args...>{
		private:
			std::function<bool(ClassName*, std::tuple<Args...>)> func_;
			std::weak_ptr<ClassName> w_ptr_;
			std::shared_ptr<ClassName> s_ptr_;
			bool on_;
		public:
			CallbackDerived(
				void(ClassName::*func)(std::tuple<Args...>),
				std::shared_ptr<ClassName> s_ptr
				)
				:
				w_ptr_{ s_ptr },
				on_{ false }
			{
				func_ = [=](ClassName* raw_ptr, std::tuple<Args&&...> arg_tuple)
				{
					(raw_ptr->*func)(arg_tuple);
				};
			}

			// virtual funcs
			void Call(std::tuple<Args...> arg_tuple){
				if (!on_){
					On();
				}
				func_(s_ptr_.get(), arg_tuple);
			};
			bool On(){
				on_ = true;
				// try cast to bool
				return (s_ptr_ = w_ptr_.lock()) ? true : false;
			}
			void Off(){
				on_ = false;
				s_ptr_.reset();
			}

		};

template<typename... Args>
    	class EventHandler_2{
		public:
			using Pointer = std::shared_ptr < EventHandler_2 >;
			using Callback = std::function < bool(std::tuple<Args...>) >;
			using Event = std::tuple < Args... >;
		private:
			std::vector<CallbackBase<Args...>*> callbacks_;
			std::vector<Event> events_;
		private:
			EventHandler_2(){

			}
		public:
			static Pointer Create(){ return Pointer{ new EventHandler_2{} }; }
			template<typename ClassName>
			void AddCallback(void(ClassName::*func)(std::tuple<Args...>), std::shared_ptr<ClassName> s_ptr){
                // Problem line below!!!
				auto callback = new CallbackDerived < ClassName, Args... > {func, s_ptr};
				callbacks_.push_back(callback);
			}
			void AddEvent(std::tuple<Args...> args){
				events_.push_back(args);
			}
			void AddEvent(Args... args){
				events_.push_back(std::make_tuple<Args...>(args...));
			}
			// TriggerSingleEvent ?
			void Trigger(){
				auto num_events = events_.size();
				auto num_callbacks = callbacks_.size();
				Event event_tuple;
				for (auto event_index = 0u; event_index < num_events; ++event_index){
					event_tuple = events_[event_index];
					for (auto callback_index = 0u; callback_index < num_callbacks; ++callback_index){
						callbacks_[callback_index]->Call(event_tuple);
					}
				}
				for (auto callback_index = 0u; callback_index < num_callbacks; ++callback_index){
					callbacks_[callback_index]->Off();
				}
			}
		};

class A{

public:
    unsigned i = 0u;

	void inc(std::tuple<> t){ ++i; }

};

int main(){
	auto ev = EventHandler_2<>::Create();

	auto p_a = std::make_shared<A>(A{});

	// seed rand
	srand(std::chrono::system_clock::now().time_since_epoch().count());

	auto start_time = std::chrono::steady_clock::now();
	auto end_time = start_time;

	ev->AddCallback(&A::inc, p_a);

	for (auto i = 0u; i < 100000; ++i){
		ev->AddEvent();
		if (!(rand() % 100)) ev->Trigger();
	}
	ev->Trigger();

	end_time = std::chrono::steady_clock::now();

	printf("time took: %u\n", end_time - start_time);


	system("pause");
	return 0;
}
