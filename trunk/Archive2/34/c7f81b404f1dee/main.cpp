#include <map>
#include <memory>
#include <vector>
#include <string>
#include <chrono>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <type_traits>

namespace bmk
{ // #benchmark tools 

    using std::map; 
	using std::vector; 
	using std::string;
	using std::size_t; 
	using std::ostream; 
	using std::unique_ptr; 
	using std::make_unique; 
	using std::initializer_list; 
	using std::remove_reference; 
	using std::chrono::duration_cast; 

	// folly function to avoid optimizing code away ---------------------
#ifdef _MSC_VER
	#pragma optimize("", off)
	template <class T>
	void doNotOptimizeAway(T&& datum) 
	{
		datum = datum;
	}
	#pragma optimize("", on)
#else
	template <class T>
	void doNotOptimizeAway(T&& datum) 
	{
		asm volatile("" : "+r" (datum));
	}
#endif

	/// calculate the mean value
	template<typename C>
	auto mean(C&& data)
	{
		return std::accumulate(begin(data), end(data),
			(std::remove_reference_t<decltype(*begin(data))>)0) / data.size();
	}

	/// get the name of the chrono time type
	template<typename T> string time_type()                  { return "unknown";      }
	template<> string time_type<std::chrono::nanoseconds >() { return "nanoseconds";  }
	template<> string time_type<std::chrono::microseconds>() { return "microseconds"; }
	template<> string time_type<std::chrono::milliseconds>() { return "milliseconds"; }
	template<> string time_type<std::chrono::seconds     >() { return "seconds";      }
	template<> string time_type<std::chrono::minutes     >() { return "minutes";      }
	template<> string time_type<std::chrono::hours       >() { return "hours";        }

	namespace detail
	{
		/**
		* @ class experiment_impl
		* @ brief implementation details of an experiment
		*/
		template<class TimeT, class FactorT>
		struct experiment_impl
		{
			string                           _fctName; 
			map<FactorT, std::vector<TimeT>> _timings;
		
			experiment_impl(string const& factorName)
				: _fctName(factorName)
			{ }

			// implementation of forwarded functions --------------------
			void print(ostream& os) const
			{
				string token{ "" }; 

				os << ", 'factor_name' : '" << _fctName << "'"; 
				// print the factor list
				os << ", 'factors' : [ "; 
				for (auto&& Pair : _timings)
				{
					os << token; 
					os << Pair.first; 
					token = ", "; 
				}
				os << " ]"; 
				// print the timings
				token.clear(); 
				os << ", 'timings' : [ ";
				for (auto&& Pair : _timings)
				{
					os << token; 
					os << mean(Pair.second).count();
					token = ", ";
				}
				os << " ]";
			}

		protected:
			~experiment_impl() = default; 
		};

		template<class TimeT>
		struct experiment_impl < TimeT, void >
		{
			vector<TimeT> _timings;

			experiment_impl(size_t nSample)
				: _timings(nSample)
			{ }
			
			// implementation of forwarded functions --------------------
			void print(ostream& os) const
			{
				string token{ "" };
				// print the timings
				os << ", 'timings' : [ ";
				for (auto&& elem : _timings)
				{
					os << token;
					os << elem.count();
					token = ", ";
				}
				os << " ]";
			}

		protected:
			~experiment_impl() = default;
		};

		/**
		* @ class experiment
		* @ brief base class to serve as an experiment concept
		*/
		struct experiment
		{
			virtual ~experiment()
			{ }

			// forwarded functions --------------------------------------
			virtual void print(ostream& os) const = 0;
		};

		/**
		* @ class experiment_model
		* @ brief abrastraction for a single sampling process
		*/
		template <
			class TimeT, class ClockT, class FactorT = void
		>
		struct experiment_model final
			: experiment
			, experiment_impl < TimeT, FactorT >
		{
			// construction - destruction -------------------------------
			template<class F>
			experiment_model(size_t nSample, F callable)
				: experiment_impl<TimeT, void>(nSample)
			{
				for (size_t i = 0; i < nSample; i++)
				{
					auto start = ClockT::now();
					callable();
					auto duration = duration_cast<TimeT>(ClockT::now() - start);
					experiment_impl<TimeT, FactorT>::_timings[i] = duration;
				}
			}

			template<class F>
			experiment_model(
				size_t nSample, F callable, string const& factorName, initializer_list<FactorT>&& factors)
				: experiment_impl<TimeT, FactorT>(factorName)
			{
				for (auto& factor : factors)
				{
					experiment_impl<TimeT, FactorT>::_timings[factor].reserve(nSample);
					for (size_t i = 0; i < nSample; i++)
					{
						auto start = ClockT::now();
						callable(factor);
						auto duration = duration_cast<TimeT>(ClockT::now() - start);
						experiment_impl<TimeT, FactorT>::_timings[factor].push_back(duration);
					}
				}
			}

			template<class F, class It>
			experiment_model(size_t nSample, F callable, string const& factorName, It beg, It fin)
				: experiment_impl<TimeT, typename remove_reference<decltype(*beg)>::type>(factorName)
			{
				while (beg != fin)
				{
					experiment_impl<TimeT, FactorT>::_timings[*beg].reserve(nSample);
					for (size_t i = 0; i < nSample; i++)
					{
						auto start = ClockT::now();
						callable(*beg);
						auto duration = duration_cast<TimeT>(ClockT::now() - start);
						experiment_impl<TimeT, FactorT>::_timings[*beg].push_back(duration);
					}
					++beg;
				}
			}

			// forwarded functions --------------------------------------
			void print(ostream& os) const override
			{
				experiment_impl<TimeT, FactorT>::print(os);
			}

		};
	}

	/**
	* @ class benchmark
	* @ brief 
	*/
	template <
		typename TimeT = std::chrono::milliseconds, class ClockT = std::chrono::steady_clock
	>
	class benchmark
	{
		map<string, unique_ptr<detail::experiment>> _data; 

	public:
		// construction - destruction -----------------------------------
		benchmark()                 = default; 
		benchmark(benchmark const&) = delete; 

		// run experiments ----------------------------------------------
		template<class F>
		void run(string const& name, size_t nSample, F callable)
		{
			_data[name] = make_unique< 
				detail::experiment_model<TimeT, ClockT>>(nSample, callable);
		}

		template<class FactorT, class F>
		void run(
			string const& name, size_t nSample, F callable, 
			string const& factorName, initializer_list<FactorT>&& factors)
		{
			_data[name] = make_unique<detail::experiment_model<TimeT, ClockT, FactorT>>(
				nSample, callable, factorName, std::forward<initializer_list<FactorT>&&>(factors));
		}

		template<class F, class It>
		void run(string const& name, size_t nSample, F callable, string const& factorName, It beg, It fin)
		{
			_data[name] = make_unique<detail::experiment_model<TimeT, ClockT, 
				typename remove_reference<decltype(*beg)>::type>> (nSample, callable, factorName, beg, fin);
		}

		// utilities ----------------------------------------------------
		void print(ostream& os) const
		{
			for (auto const& Pair : _data)
			{
				os << "{ 'experiment_name' : '" << Pair.first << "'"; 
				os << ", 'time_type' : '" << time_type<TimeT>() << "'";
				Pair.second->print(os);
				os << " } \n";
			}
		}

		void serialize(const char *filename) const
		{
			std::ofstream os;
			os.open(filename, std::ofstream::out | std::ofstream::app);
			for (auto const& Pair : _data)
			{
				os << "{ 'experiment_name' : '" << Pair.first << "'";
				os << ", 'time_type' : '" << time_type<TimeT>() << "'";
				Pair.second->print(os);
				os << " } \n";
			}
			os.close(); 
		}
	};

} // ~benchmark tools

void ff(int a, double b, char c)
{
    for (int i = 0; i < a; i++)
	{
		b += i; 
	}
}


int main()
{
    bmk::benchmark<> bm;

    std::vector<int> fv{ 1, 2, 3, 4, 5 };

	bm.run("FF experiment ", 10, [](int a) { ff(a, 2., 'a'); }, "fact in init", { 1, 2, 3, 4, 5 });
	bm.run("FF experiment1", 10, [](int a) { ff(a, 2., 'a'); }, "fact in vector", fv.begin(), fv.end());
	bm.run("FF experiment2", 10, []() { ff(1, 2., 'a'); });

    bm.print(std::cout); 
}
