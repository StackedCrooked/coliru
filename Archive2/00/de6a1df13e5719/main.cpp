#include <map>
#include <cmath>
#include <memory>
#include <vector>
#include <string>
#include <chrono>
#include <sstream>
#include <cstddef>
#include <ostream>
#include <utility>
#include <fstream>
#include <numeric>
#include <iostream>
#include <algorithm>
#include <type_traits>

namespace bmk
{

    using std::map; 
	using std::vector; 
	using std::string;
	using std::size_t; 
	using std::ostream; 
	using std::is_same; 
	using std::forward; 
	using std::ofstream; 
	using std::enable_if; 
	using std::unique_ptr; 
	using std::result_of_t; 
	using std::make_unique; 
	using std::initializer_list; 
	using std::remove_reference; 
	using std::integral_constant;
	using std::chrono::time_point; 
	using std::chrono::duration_cast; 

	/// folly function to avoid optimizing code away 
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
	template<typename T> string time_type()                            { return "unknown";      }
	template<          > string time_type<std::chrono::nanoseconds >() { return "nanoseconds";  }
	template<          > string time_type<std::chrono::microseconds>() { return "microseconds"; }
	template<          > string time_type<std::chrono::milliseconds>() { return "milliseconds"; }
	template<          > string time_type<std::chrono::seconds     >() { return "seconds";      }
	template<          > string time_type<std::chrono::minutes     >() { return "minutes";      }
	template<          > string time_type<std::chrono::hours       >() { return "hours";        }

	template<class TimeT=std::chrono::milliseconds, class ClockT=std::chrono::steady_clock>
	class timeout
	{
		TimeT _total{ 0 };
		decltype(ClockT::now()) _start;
	public:
		void tic()
		{
			_start = ClockT::now();
		}
		void toc()
		{
			_total += duration_cast<TimeT>(ClockT::now() - _start);
		}
		TimeT duration() const
		{
			return _total;
		}
	};

	template<class TimeT = std::chrono::milliseconds, class ClockT = std::chrono::steady_clock>
	using timeout_ptr = unique_ptr < timeout < TimeT, ClockT > > ; 

	namespace detail
	{
		/**
		* @ class experiment_impl
		* @ brief implementation details of an experiment
		*/
		template<class TimeT, class FactorT>
		struct experiment_impl
		{
			string                      _fctName; 
			map<FactorT, vector<TimeT>> _timings;
		
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

		template<class TimeT, class ClockT>
		struct measure
		{
			template<class F>
			inline static auto duration(F callable)
				-> typename enable_if < !is_same <
				decltype(callable()), timeout_ptr<TimeT, ClockT>>::value, TimeT > ::type
			{
				auto start = ClockT::now();
				callable();
				return duration_cast<TimeT>(ClockT::now() - start);
			}

			template<class F>
			inline static auto duration(F callable)
				-> typename enable_if < is_same < 
				decltype(callable()), timeout_ptr<TimeT, ClockT> >::value, TimeT > ::type
			{
				auto start = ClockT::now();
				auto tOut  = callable();
				return (duration_cast<TimeT>(ClockT::now() - start)) - tOut->duration();
			}

			template<class F, typename FactorT>
			inline static auto duration(F callable, FactorT&& factor)
				-> typename enable_if < !is_same < 
				decltype(callable(forward<FactorT>(factor))), timeout_ptr<TimeT, ClockT>
				>::value, TimeT >::type
			{
				auto start = ClockT::now();
				callable(forward<FactorT>(factor));
				return duration_cast<TimeT>(ClockT::now() - start);
			}

			template<class F, typename FactorT>
			inline static auto duration(F callable, FactorT&& factor)
				-> typename enable_if < is_same < 
				decltype(callable(forward<FactorT>(factor))), timeout_ptr<TimeT, ClockT>
				>::value, TimeT >::type
			{
				auto start = ClockT::now();
				auto tOut  = callable(forward<FactorT>(factor));
				return (duration_cast<TimeT>(ClockT::now() - start)) - tOut->duration();
			}
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
					experiment_impl<TimeT, FactorT>::_timings[i] = measure<TimeT, ClockT>
						::duration(callable);
				}
			}

			template<class F>
			experiment_model(
				size_t nSample, F callable, 
				string const& factorName, initializer_list<FactorT>&& factors)
				: experiment_impl<TimeT, FactorT>(factorName)
			{
				for (auto&& factor : factors)
				{
					experiment_impl<TimeT, FactorT>::_timings[factor].reserve(nSample);
					for (size_t i = 0; i < nSample; i++)
					{
						experiment_impl<TimeT, FactorT>::_timings[factor].push_back(
							measure<TimeT, ClockT>::duration(callable, factor));
					}
				}
			}

			template<class F, class It>
			experiment_model(size_t nSample, F callable, string const& factorName, It beg, It fin)
				: experiment_impl<
					TimeT, typename remove_reference<decltype(*beg)>::type>(factorName)
			{
				while (beg != fin)
				{
					experiment_impl<TimeT, FactorT>::_timings[*beg].reserve(nSample);
					for (size_t i = 0; i < nSample; i++)
					{
						experiment_impl<TimeT, FactorT>::_timings[*beg].push_back(
							measure<TimeT, ClockT>::duration(callable, *beg));
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
	} // ~ namespace detail

	/**
	* @ class benchmark
	* @ brief organizes the execution and serialization of timing experiments
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
				nSample, callable, factorName, forward<initializer_list<FactorT>&&>(factors));
		}

		template<class F, class It>
		void run(
			string const& name, size_t nSample, 
			F callable, string const& factorName, It beg, It fin)
		{
			_data[name] = make_unique<detail::experiment_model<TimeT, ClockT, 
				typename remove_reference<decltype(*beg)>::type>>(
				nSample, callable, factorName, beg, fin);
		}

		// utilities ----------------------------------------------------
		void print(const char* benchmarkName, ostream& os) const
		{
			for (auto const& Pair : _data)
			{
				os << "{ 'benchmark_name' : '" << benchmarkName << "'";
				os << ", 'experiment_name' : '" << Pair.first << "'";
				os << ", 'time_type' : '" << time_type<TimeT>() << "'";
				Pair.second->print(os);
				os << " } \n";
			}
		}

		void serialize(
			const char* benchmarkName, const char *filename,
			std::ios_base::openmode mode = ofstream::out) const
		{
			ofstream os;
			os.open(filename, mode);
			for (auto const& Pair : _data)
			{
				os << "{ 'benchmark_name' : '" << benchmarkName << "'";
				os << ", 'experiment_name' : '" << Pair.first << "'";
				os << ", 'time_type' : '" << time_type<TimeT>() << "'";
				Pair.second->print(os);
				os << " } \n";
			}
			os.close(); 
		}
	};

} // ~ namespace bmk

namespace memu
{

    using std::size_t; 
	using std::string; 
	using std::ostream; 
	using std::stringstream; 

	constexpr size_t byte     = 1;
	constexpr size_t kilobyte = 1024;
	constexpr size_t megabyte = 1048576L;
	constexpr size_t gigabyte = 1073741824L;

	class memory_unit
	{
		size_t _nBytes; 
	public:
		memory_unit() = default; 
		memory_unit(size_t nBytes)
			: _nBytes(nBytes)
		{ }

		operator size_t() const
		{
			return _nBytes; 
		}
		friend ostream& operator<<(ostream& os, memory_unit const& mu)
		{
			if (kilobyte > mu)
			{
				os << "'" << (size_t)mu << "B'";
			}
			else if (megabyte > mu)
			{
				os << "'" << (mu / (double)kilobyte) << "kB'"; 
			}
			else if (gigabyte > mu)
			{
				os << "'" << (mu / (double)megabyte) << "MB'";
			}
			else
			{
				os << "'" << (mu / (double)gigabyte) << "GB'";
			}
			return os; 
		}
		string to_string() const
		{
			stringstream ss; 
			if (kilobyte > _nBytes)
			{
				ss << _nBytes << "B";
			}
			else if (megabyte > _nBytes)
			{
				ss << (_nBytes / (double)kilobyte) << "kB";
			}
			else if (gigabyte > _nBytes)
			{
				ss << (_nBytes / (double)megabyte) << "MB";
			}
			else
			{
    			ss << (_nBytes / (double)gigabyte) << "GB";
			}
			return ss.str(); 
		}
	};

} // ~ namespace memu



#define MEASURE_CACHE_LINE 1
#define MEASURE_CACHE_SIZE 1
#define MEASURE_CACHE_EFCT 1

using std::size_t; 
using std::vector; 
using std::lower_bound; 
using memu::memory_unit; 

int main()
{
#if MEASURE_CACHE_LINE
    bmk::benchmark<> bm1;
	vector<int> pool(64 * 1024 * 1024); 
	bm1.run("Update every Kth integer", 1, [&](int stride) 
	{
		for (size_t i(0), ie(pool.size()); i < ie; i += stride) { pool[i] += 1; }
	}, "K", { 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024 });
	bm1.print("Impact of cache lines", std::cout);
#endif // MEASURE_CACHE_LINE

#if MEASURE_CACHE_SIZE
	vector<memory_unit> nBytes(21);
	for (size_t i(0), ie(nBytes.size()); i < ie; ++i) nBytes[i] = pow(2, 10+i);

	bmk::benchmark<> bm2;
	bm2.run("Loop over N cache lines", 1, [&](memory_unit const& arrayBytes) 
	{
		bmk::timeout_ptr<> to = std::make_unique < bmk::timeout<> >();
		size_t arrLength      = arrayBytes / sizeof(int);
		size_t lengthMod      = arrLength - 1;

		to->tic(); int *arr = new int[arrLength]; to->toc();
		for (int i = 0; i < 67108864; i++) { arr[(i * 16) & lengthMod]++; }
		to->tic(); delete[] arr; to->toc();

		return to;
	}, "array size", nBytes.begin(), nBytes.end());

	bm2.print("L1 & L2 cache sizes", std::cout);
#endif // MEASURE_CACHE_SIZE

#if MEASURE_CACHE_EFCT
	bmk::benchmark<> bm3; 

	vector<memory_unit> steps(11);
	for (size_t i(1), ie(12); i < ie; ++i) steps[i - 1] = pow(2, i * 2);

	for (size_t i = 14; i < 24; i++)
	{ 
		memory_unit mu{ (size_t)pow(2, i) };
		vector<int> ar(mu / sizeof(int));

		bm3.run(mu.to_string(), 1, [&](memory_unit const& strideSize)
		{
			size_t pos  = 0; 
			size_t arsz = ar.size(); 
			size_t step = strideSize / sizeof(int); 

			for (int i = 0; i < 64*1024*1024; i++) 
			{ 
				++ar[pos];
				pos += step; 
				if (pos >= arsz) pos = 0; 
			}
		}, "stride size", steps.begin(), lower_bound(steps.begin(), steps.end(), mu));
	}
	bm3.print("cache effects", std::cout);
#endif // MEASURE_CACHE_EFCT

	return 0;
}