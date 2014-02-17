//
// Written in 2014 by Martinho Fernandes <martinho.fernandes@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>

// This file was automatically generated on 2014-02-17T12:37:59.413289Z
// Do not edit it directly

#ifndef NONIUS_SINGLE_INCLUDE_HPP
#define NONIUS_SINGLE_INCLUDE_HPP

// Nonius - C++ benchmarking tool
//
// Written in 2014 by Martinho Fernandes <martinho.fernandes@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>

// Executable building kit

#define NONIUS_MAIN_HPP

// #included from: nonius.h++
// Nonius - C++ benchmarking tool
//
// Written in 2014 by Martinho Fernandes <martinho.fernandes@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>

// Main header

#ifndef NONIUS_HPP
#define NONIUS_HPP

// #included from: clock.h++
// Nonius - C++ benchmarking tool
//
// Written in 2014 by Martinho Fernandes <martinho.fernandes@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>

// Clocks

#define NONIUS_CLOCK_HPP

#ifdef _MSC_VER // MSVC <chrono> is borken and had little to no testing done before shipping
#include <boost/chrono.hpp>
#else
#include <chrono>
#include <ratio>
#endif

namespace nonius {
#ifdef _MSC_VER // MSVC <chrono> is borken and had little to no testing done before shipping
    namespace chrono = boost::chrono;
    template <unsigned Num, unsigned Den = 1>
    using ratio = boost::ratio<Num, Den>;
#else
    namespace chrono = std::chrono;
    template <unsigned Num, unsigned Den = 1>
    using ratio = std::ratio<Num, Den>;
#endif
    using milli = ratio<1,       1000>;
    using micro = ratio<1,    1000000>;
    using nano  = ratio<1, 1000000000>;

    template <typename Clock>
    using Duration = typename Clock::duration;
    template <typename Clock>
    using FloatDuration = chrono::duration<double, typename Clock::period>;

    template <typename Clock>
    using TimePoint = typename Clock::time_point;

    using default_clock = chrono::high_resolution_clock;

    template <typename Clock>
    struct now {
        TimePoint<Clock> operator()() const {
            return Clock::now();
        }
    };

    using fp_seconds = chrono::duration<double, ratio<1>>;
} // namespace nonius

// #included from: benchmark.h++
// Nonius - C++ benchmarking tool
//
// Written in 2014 by Martinho Fernandes <martinho.fernandes@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>

// Benchmark

#define NONIUS_BENCHMARK_HPP

// #included from: configuration.h++
// Nonius - C++ benchmarking tool
//
// Written in 2014 by Martinho Fernandes <martinho.fernandes@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>

// Run configuration

#define NONIUS_CONFIGURATION_HPP

#include <string>

namespace nonius {
    struct configuration {
    public:
        int samples = 100;
        double confidence_interval = 0.95;
        int resamples = 100000;
        std::string output_file;
        std::string reporter;
        bool list_benchmarks = false;
        bool list_reporters = false;
        bool no_analysis = false;
        bool verbose = false;
        bool summary = false;
        bool help = false;
    };
} // namespace nonius

// #included from: environment.h++
// Nonius - C++ benchmarking tool
//
// Written in 2014 by Martinho Fernandes <martinho.fernandes@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>

// Environment information

#define NONIUS_ENVIRONMENT_HPP

// #included from: outlier_classification.h++
// Nonius - C++ benchmarking tool
//
// Written in 2014 by Martinho Fernandes <martinho.fernandes@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>

// Outlier information

#define NONIUS_OUTLIERS_HPP

namespace nonius {
    struct outlier_classification {
        int samples_seen = 0;
        int low_severe = 0;     // more than 3 times IQR below Q1
        int low_mild = 0;       // 1.5 to 3 times IQR below Q1
        int high_mild = 0;      // 1.5 to 3 times IQR above Q3
        int high_severe = 0;    // more than 3 times IQR above Q3

        int total() const {
            return low_severe + low_mild + high_mild + high_severe;
        }
    };
} // namespace nonius

namespace nonius {
    template <typename Duration>
    struct environment_estimate {
        Duration mean;
        outlier_classification outliers;

        template <typename Duration2>
        operator environment_estimate<Duration2>() const {
            return { mean, outliers };
        }
    };
    template <typename Clock = default_clock>
    struct environment {
        environment_estimate<FloatDuration<Clock>> clock_resolution;
        environment_estimate<FloatDuration<Clock>> clock_cost;
        //estimate function_cost;
    };
} // namespace nonius

// #included from: execution_plan.h++
// Nonius - C++ benchmarking tool
//
// Written in 2014 by Martinho Fernandes <martinho.fernandes@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>

// Execution plan

#define NONIUS_EXECUTION_PLAN_HPP

namespace nonius {
    template <typename Duration>
    struct execution_plan {
        int iterations_per_sample;
        Duration estimated_duration;

        template <typename Duration2>
        operator execution_plan<Duration2>() const {
            return { iterations_per_sample, estimated_duration };
        }
    };
} // namespace nonius

// #included from: chronometer.h++
// Nonius - C++ benchmarking tool
//
// Written in 2014 by Martinho Fernandes <martinho.fernandes@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>

// User-facing chronometer

#define NONIUS_CHRONOMETER_HPP

// #included from: detail/complete_invoke.h++
// Nonius - C++ benchmarking tool
//
// Written in 2014 by Martinho Fernandes <martinho.fernandes@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>

// Invoke with a special case for void

#define NONIUS_DETAIL_COMPLETE_INVOKE_HPP

#include <type_traits>
#include <utility>

namespace nonius {
    namespace detail {
        template <typename T>
        struct complete_type { using type = T; };
        template <>
        struct complete_type<void> { struct type {}; };

        template <typename T>
        using CompleteType = typename complete_type<T>::type;

        template <typename Result>
        struct complete_invoker {
            template <typename Fun, typename... Args>
            static Result invoke(Fun&& fun, Args&&... args) {
                return std::forward<Fun>(fun)(std::forward<Args>(args)...);
            }
        };
        template <>
        struct complete_invoker<void> {
            template <typename Fun, typename... Args>
            static CompleteType<void> invoke(Fun&& fun, Args&&... args) {
                std::forward<Fun>(fun)(std::forward<Args>(args)...);
                return {};
            }
        };
        template <typename Sig>
        using ResultOf = typename std::result_of<Sig>::type;

        // invoke and not return void :(
        template <typename Fun, typename... Args>
        CompleteType<ResultOf<Fun(Args...)>> complete_invoke(Fun&& fun, Args&&... args) {
            return complete_invoker<ResultOf<Fun(Args...)>>::invoke(std::forward<Fun>(fun), std::forward<Args>(args)...);
        }

        template <typename> struct always_true : std::true_type {};
        struct is_callable_tester {
            template <typename Fun, typename... Args>
            always_true<decltype(std::declval<Fun>()(std::declval<Args>()...))> static test(int);
            template <typename...>
            std::false_type static test(...);
        };
        template <typename T>
        struct is_callable;
        template <typename Fun, typename... Args>
        struct is_callable<Fun(Args...)> : decltype(is_callable_tester::test<Fun, Args...>(0)) {};
    } // namespace detail
} // namespace nonius

namespace nonius {
    namespace detail {
        struct chronometer_concept {
            virtual void start() = 0;
            virtual void finish() = 0;
            virtual ~chronometer_concept() = default;
        };
        template <typename Clock>
        struct chronometer_model final : public chronometer_concept {
            void start() override { started = Clock::now(); }
            void finish() override { finished = Clock::now(); }

            TimePoint<Clock> started;
            TimePoint<Clock> finished;
        };
    } // namespace detail

    struct chronometer {
    public:
        template <typename Fun>
        void measure(Fun&& fun) { measure(std::forward<Fun>(fun), detail::is_callable<Fun(int)>()); }

        int runs() const { return k; }

        chronometer(detail::chronometer_concept& meter, int k)
        : impl(&meter), k(k) {}

    private:
        template <typename Fun>
        void measure(Fun&& fun, std::false_type) {
            measure([&fun](int) { fun(); });
        }
        template <typename Fun>
        void measure(Fun&& fun, std::true_type) {
            impl->start();
            for(int i = 0; i < k; ++i) fun(i);
            impl->finish();
        }

        detail::chronometer_concept* impl;
        int k;
    };
} // namespace nonius

// #included from: detail/measure.h++
// Nonius - C++ benchmarking tool
//
// Written in 2014 by Martinho Fernandes <martinho.fernandes@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>

// Measure

#define NONIUS_DETAIL_MEASURE_HPP

// #included from: detail/timing.h++
// Nonius - C++ benchmarking tool
//
// Written in 2014 by Martinho Fernandes <martinho.fernandes@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>

// Timing

#define NONIUS_DETAIL_TIMING_HPP

#include <tuple>
#include <type_traits>

namespace nonius {
    template <typename Duration, typename Result>
    struct timing {
        Duration elapsed;
        Result result;
        int iterations;
    };
    template <typename Clock, typename Sig>
    using TimingOf = timing<Duration<Clock>, detail::CompleteType<detail::ResultOf<Sig>>>;
} // namespace nonius

#include <utility>

namespace nonius {
    namespace detail {
        template <typename Clock = default_clock, typename Fun, typename... Args>
        TimingOf<Clock, Fun(Args...)> measure(Fun&& fun, Args&&... args) {
            auto start = Clock::now();
            auto&& r = detail::complete_invoke(fun, std::forward<Args>(args)...);
            auto end = Clock::now();
            auto delta = end - start;
            return { delta, std::forward<decltype(r)>(r), 1 };
        }
    } // namespace detail
} // namespace nonius

// #included from: detail/benchmark_function.h++
// Nonius - C++ benchmarking tool
//
// Written in 2014 by Martinho Fernandes <martinho.fernandes@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>

// Dumb std::function implementation for consistent call overhead

#define NONIUS_DETAIL_BENCHMARK_FUNCTION_HPP

#include <type_traits>
#include <utility>
#include <memory>

namespace nonius {
    namespace detail {
        template <typename T>
        using Decay = typename std::decay<T>::type;
        template <typename T, typename U>
        struct is_related
        : std::is_same<Decay<T>, Decay<U>> {};

        struct benchmark_function {
        private:
            struct concept {
                virtual void call(chronometer meter) const = 0;
                virtual ~concept() = default;
            };
            template <typename Fun>
            struct model : public concept {
                model(Fun&& fun) : fun(std::move(fun)) {}
                model(Fun const& fun) : fun(fun) {}

                void call(chronometer meter) const override {
                    call(meter, is_callable<Fun(chronometer)>());
                }
                void call(chronometer meter, std::true_type) const {
                    fun(meter);
                }
                void call(chronometer meter, std::false_type) const {
                    meter.measure(fun);
                }

                Fun fun;
            };
        public:
            template <typename Fun,
                      typename std::enable_if<!is_related<Fun, benchmark_function>::value, int>::type = 0>
            benchmark_function(Fun&& fun)
            : f(new model<typename std::decay<Fun>::type>(std::forward<Fun>(fun))) {}

            benchmark_function(benchmark_function&& that)
            : f(std::move(that.f)) {}

            void operator()(chronometer meter) const { f->call(meter); }
        private:
            std::unique_ptr<concept> f;
        };
    } // namespace detail
} // namespace nonius

// #included from: detail/repeat.h++
// Nonius - C++ benchmarking tool
//
// Written in 2014 by Martinho Fernandes <martinho.fernandes@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>

// repeat algorithm

#define NONIUS_DETAIL_REPEAT_HPP

#include <type_traits>
#include <utility>

namespace nonius {
    namespace detail {
        template <typename Fun>
        struct repeater {
            void operator()(int k) const {
                for(int i = 0; i < k; ++i) {
                    fun();
                }
            }
            Fun fun;
        };
        template <typename Fun>
        repeater<typename std::decay<Fun>::type> repeat(Fun&& fun) {
            return { std::forward<Fun>(fun) };
        }
    } // namespace detail
} // namespace nonius

// #included from: detail/run_for_at_least.h++
// Nonius - C++ benchmarking tool
//
// Written in 2014 by Martinho Fernandes <martinho.fernandes@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>

// Run a function for a minimum amount of time

#define NONIUS_RUN_FOR_AT_LEAST_HPP

// #included from: timeout_error.h++
// Nonius - C++ benchmarking tool
//
// Written in 2014 by Martinho Fernandes <martinho.fernandes@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>

// Exception to be thrown when a process takes too long to run

#define NONIUS_TIMEOUT_ERROR_HPP

// #included from: detail/noexcept.h++
// Nonius - C++ benchmarking tool
//
// Written in 2014 by Martinho Fernandes <martinho.fernandes@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>

// Cross-compiler noexcept support

#define NONIUS_DETAIL_NOEXCEPT_HPP

#ifdef _MSC_VER
#define NONIUS_NOEXCEPT throw()
#else
#define NONIUS_NOEXCEPT noexcept
#endif // _MSC_VER

#include <sstream>
#include <string>
#include <exception>

namespace nonius {
    struct timeout_error : virtual std::exception {
    public:
        timeout_error(int seed, int iters) {
            std::ostringstream ss;
            ss << "took too long to run; seed: " << seed << ", iters: " << iters;
            message = ss.str();
        }

        char const* what() const NONIUS_NOEXCEPT override {
            return message.c_str();
        }

    private:
        std::string message;
    };
} // namespace nonius

#include <utility>

namespace nonius {
    namespace detail {
        template <typename Clock = default_clock, typename Fun>
        TimingOf<Clock, Fun(int)> run_for_at_least(Duration<Clock> how_long, int seed, Fun&& fun) {
            auto iters = seed;
            auto start = Clock::now();
            while(true) {
                auto now = Clock::now();
                if(now - start > how_long * 10) {
                    throw timeout_error(seed, iters);
                }
                auto r = detail::measure<Clock>(fun, iters);
                if(r.elapsed >= how_long) {
                    return { r.elapsed, std::move(r.result), iters };
                }
                iters *= 2;
            }
        }
    } // namespace detail
} // namespace nonius

#include <algorithm>
#include <functional>
#include <string>
#include <vector>
#include <cmath>

namespace nonius {
    namespace detail {
        const auto warmup_iterations = 10000;
        const auto warmup_time = chrono::milliseconds(100);
        const auto minimum_ticks = 1000;
    } // namespace detail

    struct benchmark {
        benchmark(std::string name, detail::benchmark_function fun)
        : name(std::move(name)), fun(std::move(fun)) {}

        benchmark(benchmark&& that)
        : name(std::move(that.name)), fun(std::move(that.fun)) {}

        void operator()(chronometer meter) const {
            fun(meter);
        }

        template <typename Clock>
        execution_plan<FloatDuration<Clock>> prepare(configuration cfg, environment<FloatDuration<Clock>> env) const {
            auto min_time = env.clock_resolution.mean * detail::minimum_ticks;
            auto run_time = std::min(min_time, decltype(min_time)(detail::warmup_time));
            auto&& test = detail::run_for_at_least<Clock>(chrono::duration_cast<Duration<Clock>>(run_time), 1, [this](int k) {
                detail::chronometer_model<Clock> model;
                (*this)(chronometer(model, k));
            });
            int new_iters = static_cast<int>(std::ceil(min_time * test.iterations / test.elapsed));
            return { new_iters, test.elapsed / test.iterations * new_iters * cfg.samples };
        }

        template <typename Clock>
        std::vector<FloatDuration<Clock>> run(configuration cfg, environment<FloatDuration<Clock>> env, execution_plan<FloatDuration<Clock>> plan) const {
            // warmup a bit
            detail::run_for_at_least<Clock>(chrono::duration_cast<Duration<Clock>>(detail::warmup_time), detail::warmup_iterations, detail::repeat(now<Clock>{}));

            std::vector<FloatDuration<Clock>> times;
            times.reserve(cfg.samples);
            std::generate_n(std::back_inserter(times), cfg.samples, [this, env, plan]{
                    detail::chronometer_model<Clock> model;
                    (*this)(chronometer(model, plan.iterations_per_sample));
                    auto elapsed = model.finished - model.started;
                    return ((elapsed - env.clock_cost.mean) / plan.iterations_per_sample);
            });
            return times;
        }

        std::string name;
        detail::benchmark_function fun;
    };

    inline std::vector<benchmark>& benchmark_registry() {
        static std::vector<benchmark> registry;
        return registry;
    }

    struct benchmark_registrar {
        template <typename Fun>
        benchmark_registrar(std::string name, Fun&& registrant) {
            benchmark_registry().emplace_back(std::move(name), std::forward<Fun>(registrant));
        }
    };
} // namespace nonius

#define NONIUS_BENCHMARK(name, ...) \
    namespace { static ::nonius::benchmark_registrar NONIUS_DETAIL_UNIQUE_NAME(benchmark_registrar) (name, __VA_ARGS__); }

// #included from: go.h++
// Nonius - C++ benchmarking tool
//
// Written in 2014 by Martinho Fernandes <martinho.fernandes@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>

// Runner entry point

#define NONIUS_GO_HPP

// #included from: reporter.h++
// Nonius - C++ benchmarking tool
//
// Written in 2014 by Martinho Fernandes <martinho.fernandes@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>

// Reporter interface

#define NONIUS_REPORTER_HPP

// #included from: sample_analysis.h++
// Nonius - C++ benchmarking tool
//
// Written in 2014 by Martinho Fernandes <martinho.fernandes@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>

// Benchmark results

#define NONIUS_BENCHMARK_RESULTS_HPP

// #included from: estimate.h++
// Nonius - C++ benchmarking tool
//
// Written in 2014 by Martinho Fernandes <martinho.fernandes@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>

// Statistics estimates

#define NONIUS_ESTIMATE_HPP

namespace nonius {
    template <typename Duration>
    struct estimate {
        Duration point;
        Duration lower_bound;
        Duration upper_bound;
        double confidence_interval;

        template <typename Duration2>
        operator estimate<Duration2>() const {
            return { point, lower_bound, upper_bound, confidence_interval };
        }
    };
} // namespace nonius

#include <algorithm>
#include <vector>
#include <string>
#include <iterator>

namespace nonius {
    template <typename Duration>
    struct sample_analysis {
        std::vector<Duration> samples;
        estimate<Duration> mean;
        estimate<Duration> standard_deviation;
        outlier_classification outliers;
        double outlier_variance;

        template <typename Duration2>
        operator sample_analysis<Duration2>() const {
            std::vector<Duration2> samples2;
            samples2.reserve(samples.size());
            std::transform(samples.begin(), samples.end(), std::back_inserter(samples2), [](Duration d) { return Duration2(d); });
            return {
                std::move(samples2),
                mean,
                standard_deviation,
                outliers,
                outlier_variance,
            };
        }
    };
} // namespace nonius

#include <boost/variant.hpp>

#include <vector>
#include <string>
#include <ostream>
#include <fstream>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <exception>

namespace nonius {
    struct reporter {
    public:
        virtual ~reporter() = default;

        void configure(configuration& cfg) {
            if(cfg.output_file.empty()) {
                os = &std::cout;
            } else {
                os = std::unique_ptr<std::ostream>(new std::ofstream(cfg.output_file));
            }
            do_configure(cfg);
        }

        void warmup_start() {
            do_warmup_start();
        }
        void warmup_end(int iterations) {
            do_warmup_end(iterations);
        }
        void estimate_clock_resolution_start() {
            do_estimate_clock_resolution_start();
        }
        void estimate_clock_resolution_complete(environment_estimate<fp_seconds> estimate) {
            do_estimate_clock_resolution_complete(estimate);
        }

        void estimate_clock_cost_start() {
            do_estimate_clock_cost_start();
        }
        void estimate_clock_cost_complete(environment_estimate<fp_seconds> estimate) {
            do_estimate_clock_cost_complete(estimate);
        }

        void suite_start() {
            do_suite_start();
        }
        void benchmark_start(std::string const& name) {
            do_benchmark_start(name);
        }

        void measurement_start(execution_plan<fp_seconds> plan) {
            do_measurement_start(plan);
        }
        void measurement_complete(std::vector<fp_seconds> const& samples) {
            do_measurement_complete(samples);
        }

        void analysis_start() {
            do_analysis_start();
        }
        void analysis_complete(sample_analysis<fp_seconds> const& analysis) {
            do_analysis_complete(analysis);
        }

        void benchmark_failure(std::exception_ptr error) {
            do_benchmark_failure(error);
        }
        void benchmark_complete() {
            do_benchmark_complete();
        }
        void suite_complete() {
            do_suite_complete();
        }

        virtual std::string description() = 0;

    private:
        virtual void do_configure(configuration& /*cfg*/) {}

        virtual void do_warmup_start() {}
        virtual void do_warmup_end(int /*iterations*/) {}

        virtual void do_estimate_clock_resolution_start() {}
        virtual void do_estimate_clock_resolution_complete(environment_estimate<fp_seconds> /*estimate*/) {}

        virtual void do_estimate_clock_cost_start() {}
        virtual void do_estimate_clock_cost_complete(environment_estimate<fp_seconds> /*estimate*/) {}

        virtual void do_suite_start() {}
        virtual void do_benchmark_start(std::string const& /*name*/) {}

        virtual void do_measurement_start(execution_plan<fp_seconds> /*plan*/) {}
        virtual void do_measurement_complete(std::vector<fp_seconds> const& /*samples*/) {}

        virtual void do_analysis_start() {} // TODO make generic?
        virtual void do_analysis_complete(sample_analysis<fp_seconds> const& /*analysis*/) {}

        virtual void do_benchmark_failure(std::exception_ptr /*error*/) {}
        virtual void do_benchmark_complete() {}
        virtual void do_suite_complete() {}

    private:
        struct stream_visitor : boost::static_visitor<std::ostream&> {
            std::ostream& operator()(std::ostream* os) const { return *os; }
            std::ostream& operator()(std::unique_ptr<std::ostream>& os) const { return *os; }
        };

    protected:
        std::ostream& error_stream() {
            return std::cerr;
        }
        std::ostream& stream() {
            return boost::apply_visitor(stream_visitor(), os);
        }

    private:
        boost::variant<std::ostream*, std::unique_ptr<std::ostream>> os;
    };

    inline std::unordered_map<std::string, std::unique_ptr<reporter>>& reporter_registry() {
        static std::unordered_map<std::string, std::unique_ptr<reporter>> registry;
        return registry;
    }

    struct reporter_registrar {
        reporter_registrar(std::string name, reporter* registrant) {
            reporter_registry().emplace(std::move(name), std::unique_ptr<reporter>(registrant));
        }
    };
} // namespace nonius

#define NONIUS_DETAIL_UNIQUE_NAME_LINE2(name, line) NONIUS_ ## name ## _ ## line
#define NONIUS_DETAIL_UNIQUE_NAME_LINE(name, line) NONIUS_DETAIL_UNIQUE_NAME_LINE2(name, line)
#define NONIUS_DETAIL_UNIQUE_NAME(name) NONIUS_DETAIL_UNIQUE_NAME_LINE(name, __LINE__)

#define NONIUS_REPORTER(name, ...) \
    namespace { static ::nonius::reporter_registrar NONIUS_DETAIL_UNIQUE_NAME(reporter_registrar) (name, new __VA_ARGS__()); } \
    static_assert(true, "")

// #included from: reporters/standard_reporter.h++
// Nonius - C++ benchmarking tool
//
// Written in 2014 by Martinho Fernandes <martinho.fernandes@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>

// Standard reporter

#define NONIUS_REPORTERS_STANDARD_REPORTER_HPP

#include <ratio>
#include <ios>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <memory>

namespace nonius {
    struct standard_reporter : reporter {
    private:
        std::string description() override {
            return "the standard reporter";
        }

        void do_configure(configuration& cfg) override {
            n_samples = cfg.samples;
            verbose = cfg.verbose;
            summary = cfg.summary;
            n_resamples = cfg.resamples;
        }

        void do_warmup_start() override {
            if(verbose) stream() << "warming up\n";
        }
        void do_estimate_clock_resolution_start() override {
            if(verbose) stream() << "estimating clock resolution...\n";
        }
        void do_estimate_clock_resolution_complete(environment_estimate<fp_seconds> estimate) override {
            if(!summary) {
                if(!verbose) stream() << "clock resolution: ";
                print_environment_estimate(estimate, estimate.outliers.samples_seen + 2);
            }
        }

        void do_estimate_clock_cost_start() override {
            if(verbose) stream() << "estimating cost of a clock call...\n";
        }
        void do_estimate_clock_cost_complete(environment_estimate<fp_seconds> estimate) override {
            if(verbose) print_environment_estimate(estimate, estimate.outliers.samples_seen);
        }

        void do_benchmark_start(std::string const& name) override {
            stream() << '\n';
            if(!summary) stream() << "benchmarking ";
            stream() << name << "\n";
            current = name;
        }

        void do_measurement_start(execution_plan<fp_seconds> plan) override {
            stream() << std::setprecision(7);
            stream().unsetf(std::ios::floatfield);
            if(!summary) stream() << "collecting " << n_samples << " samples, " << plan.iterations_per_sample << " iterations each, in estimated " << pretty_duration(plan.estimated_duration) << "\n";
        }
        void do_analysis_start() override {
            if(verbose) stream() << "bootstrapping with " << n_resamples << " resamples\n";
        }
        void do_benchmark_failure(std::exception_ptr) override {
            error_stream() << current << " failed to run successfully\n";
            stream() << "benchmark aborted\n";
        }
        void do_analysis_complete(sample_analysis<fp_seconds> const& analysis) override {
            print_statistic_estimate("mean", analysis.mean);
            print_statistic_estimate("std dev", analysis.standard_deviation);
            if(!summary) print_outliers(analysis.outliers);
            if(verbose) stream() << "variance introduced by outliers: " << percentage(analysis.outlier_variance) << "\n";
            const char* effect;
            if(analysis.outlier_variance < 0.01) {
                effect = "unaffected";
            } else if(analysis.outlier_variance < 0.1) {
                effect = "slightly inflated";
            } else if(analysis.outlier_variance < 0.5) {
                effect = "moderately inflated";
            } else {
                effect = "severely inflated";
            }
            stream() << "variance is " << effect << " by outliers\n";
        }

        static std::string pretty_duration(fp_seconds secs) {
            using fp_millis = chrono::duration<double, milli>;
            using fp_micros = chrono::duration<double, micro>;
            using fp_nanos = chrono::duration<double, nano>;

            std::ostringstream ss;
            ss << std::setprecision(ss.precision());
            if(secs.count() >= 2.) {
                ss << secs.count() << " s";
            } else if(secs.count() >= .002) {
                ss << fp_millis(secs).count() << " ms";
            } else if(secs.count() >= .000002) {
#ifdef _MSC_VER
                ss << fp_micros(secs).count() << " us";
#else
                ss << fp_micros(secs).count() << u8" μs";
#endif
            } else {
                ss << fp_nanos(secs).count() << " ns";
            }
            return ss.str();
        }
        static std::string percentage(double d) {
            std::ostringstream ss;
            ss << std::setprecision(3);
            if(d != 0 && d < 1e-5) {
                ss << std::fixed;
                ss << 0.0001 << "%";
            } else {
                ss.unsetf(std::ios::floatfield);
                ss << (100. * d) << "%";
            }
            return ss.str();
        }
        static std::string percentage_ratio(double part, double whole) {
            return percentage(part / whole);
        }
        void print_environment_estimate(environment_estimate<fp_seconds> e, int iterations) {
            stream() << std::setprecision(7);
            stream().unsetf(std::ios::floatfield);
            stream() << "mean is " << pretty_duration(e.mean) << " (" << iterations << " iterations)\n";
            if(verbose) print_outliers(e.outliers);
        }
        void print_outlier_count(const char* description, int count, int total) {
            if(count > 0) stream() << "  " << count << " (" << percentage_ratio(count, total) << ") " << description << "\n";
        }
        void print_outliers(outlier_classification o) {
            stream() << "found " << o.total() << " outliers among " << o.samples_seen << " samples (" << percentage_ratio(o.total(), o.samples_seen) << ")\n";
            if(verbose) {
                print_outlier_count("low severe", o.low_severe, o.samples_seen);
                print_outlier_count("low mild", o.low_mild, o.samples_seen);
                print_outlier_count("high mild", o.high_mild, o.samples_seen);
                print_outlier_count("high severe", o.high_severe, o.samples_seen);
            }
        }
        void print_statistic_estimate(const char* name, estimate<fp_seconds> estimate) {
            stream() << std::setprecision(7);
            stream().unsetf(std::ios::floatfield);
            stream() << name << ": " << pretty_duration(estimate.point);
            if(!summary) {
                stream() << ", lb " << pretty_duration(estimate.lower_bound)
                         << ", ub " << pretty_duration(estimate.upper_bound)
                         << ", ci " << std::setprecision(3) << estimate.confidence_interval;
            }
            stream() << "\n";
        }

        int n_samples = 0;
        int n_resamples = 0;
        bool verbose = false;
        bool summary = false;

        std::string current;
    };

    NONIUS_REPORTER("", standard_reporter);
    NONIUS_REPORTER("standard", standard_reporter);
} // namespace nonius

// #included from: detail/estimate_clock.h++
// Nonius - C++ benchmarking tool
//
// Written in 2014 by Martinho Fernandes <martinho.fernandes@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>

// Environment measurement

#define NONIUS_DETAIL_ENVIRONMENT_HPP

// #included from: detail/stats.h++
// Nonius - C++ benchmarking tool
//
// Written in 2014 by Martinho Fernandes <martinho.fernandes@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>

// Statistical analysis tools

#define NONIUS_DETAIL_ANALYSIS_HPP

#include <boost/math/distributions/normal.hpp>

#include <algorithm>
#include <functional>
#include <iterator>
#include <vector>
#include <array>
#include <random>
#include <numeric>
#include <tuple>
#include <cmath>
#include <utility>
#include <future>
#include <cstddef>

namespace nonius {
    namespace detail {
        using sample = std::vector<double>;

        template <typename Iterator>
        double weighted_average_quantile(int k, int q, Iterator first, Iterator last) {
            int count = last - first;
            double idx = (count - 1) * k /(double) q;
            int j = (int)idx;
            double g = idx - j;
            std::nth_element(first, first+j, last);
            auto xj = first[j];
            if(g == 0) return xj;

            auto xj1 = *std::min_element(first+(j+1), last);
            return xj + g * (xj1 - xj);
        }

        template <typename Iterator>
        outlier_classification classify_outliers(Iterator first, Iterator last) {
            std::vector<double> copy(first, last);

            auto q1 = weighted_average_quantile(1, 4, copy.begin(), copy.end());
            auto q3 = weighted_average_quantile(3, 4, copy.begin(), copy.end());
            auto iqr = q3 - q1;
            auto los = q1 - (iqr * 3.);
            auto lom = q1 - (iqr * 1.5);
            auto him = q3 + (iqr * 1.5);
            auto his = q3 + (iqr * 3.);

            outlier_classification o;
            for(; first != last; ++first) {
                auto&& t = *first;
                if(t < los) ++o.low_severe;
                else if(t < lom) ++o.low_mild;
                else if(t > his) ++o.high_severe;
                else if(t > him) ++o.high_mild;
                ++o.samples_seen;
            }
            return o;
        }

        template <typename Iterator>
        double mean(Iterator first, Iterator last) {
            int count = last - first;
            double sum = std::accumulate(first, last, 0.);
            return sum / count;
        }

        template <typename Iterator>
        double standard_deviation(Iterator first, Iterator last) {
            auto m = mean(first, last);
            double variance = std::accumulate(first, last, 0., [m](double a, double b) {
                        double diff = b - m;
                        return a + diff*diff;
                    }) / (last - first);
            return std::sqrt(variance);
        }

        template <typename URng, typename Iterator, typename Estimator>
        sample resample(URng& rng, int resamples, Iterator first, Iterator last, Estimator& estimator) {
            int n = last - first;
            std::uniform_int_distribution<int> dist(0, n-1);

            sample out;
            out.reserve(resamples);
            std::generate_n(std::back_inserter(out), resamples, [n, first, &estimator, &dist, &rng] {
                std::vector<double> resampled;
                resampled.reserve(n);
                std::generate_n(std::back_inserter(resampled), n, [first, &dist, &rng] { return first[dist(rng)]; });
                return estimator(resampled.begin(), resampled.end());
            });
            std::sort(out.begin(), out.end());
            return out;
        }

        template <typename Estimator, typename Iterator>
        sample jackknife(Estimator&& estimator, Iterator first, Iterator last) {
            int n = last - first;
            auto second = std::next(first);
            sample results;
            results.reserve(n);

            for(auto it = first; it != last; ++it) {
                std::iter_swap(it, first);
                results.push_back(estimator(second, last));
            }

            return results;
        }

        template <typename Iterator, typename Estimator>
        estimate<double> bootstrap(double confidence_level, Iterator first, Iterator last, sample const& resample, Estimator&& estimator) {
            namespace bm = boost::math;

            int n_samples = last - first;

            double point = estimator(first, last);
            sample jack = jackknife(estimator, first, last);
            double jack_mean = mean(jack.begin(), jack.end());
            double sum_squares, sum_cubes;
            std::tie(sum_squares, sum_cubes) = std::accumulate(jack.begin(), jack.end(), std::make_pair(0., 0.), [jack_mean](std::pair<double, double> sqcb, double x) -> std::pair<double, double> {
                        auto d = jack_mean - x;
                        auto d2 = d * d;
                        auto d3 = d2 * d;
                        return { sqcb.first + d2, sqcb.second + d3 };
                    });

            double accel = sum_cubes / (6 * std::pow(sum_squares, 1.5));
            int n = resample.size();
            double prob_n = std::count_if(resample.begin(), resample.end(), [point](double x) { return x < point; }) /(double) n;
            double bias = bm::quantile(bm::normal{}, prob_n);
            double z1 = bm::quantile(bm::normal{}, (1. - confidence_level) / 2.);

            auto cumn = [n](double x) -> int { return std::lround(bm::cdf(bm::normal{}, x) * n); };
            auto a = [bias, accel](double b) { return bias + b / (1. - accel * b); };
            double b1 = bias + z1;
            double b2 = bias - z1;
            double a1 = a(b1);
            double a2 = a(b2);
            int lo = std::max(cumn(a1), 0);
            int hi = std::min(cumn(a2), n - 1);

            if(n_samples == 1) return { point, point, point, confidence_level };
            else return { point, resample[lo], resample[hi], confidence_level };
        }

        inline double outlier_variance(estimate<double> mean, estimate<double> stddev, int n) {
            double sb = stddev.point;
            double mn = mean.point / n;
            double mg_min = mn / 2.;
            double sg = std::min(mg_min / 4., sb / std::sqrt(n));
            double sg2 = sg * sg;
            double sb2 = sb * sb;

            auto c_max = [n, mn, sb2, sg2](double x) -> double {
                double k = mn - x;
                double d = k * k;
                double nd = n * d;
                double k0 = -n * nd;
                double k1 = sb2 - n * sg2 + nd;
                double det = k1 * k1 - 4 * sg2 * k0;
                return (int)(-2. * k0 / (k1 + std::sqrt(det)));
            };

            auto var_out = [n, sb2, sg2](double c) {
                double nc = n - c;
                return (nc / n) * (sb2 - nc * sg2);
            };

            return std::min(var_out(1), var_out(std::min(c_max(0.), c_max(mg_min)))) / sb2;
        }

        struct bootstrap_analysis {
            estimate<double> mean;
            estimate<double> standard_deviation;
            double outlier_variance;
        };

        template <typename Iterator>
        bootstrap_analysis analyse_samples(double confidence_level, int n_resamples, Iterator first, Iterator last) {
            static std::random_device entropy;
            static std::mt19937 rng;

            int n = last - first;

            auto mean = &detail::mean<Iterator>;
            auto stddev = &detail::standard_deviation<Iterator>;

            auto estimate = [=](double(*f)(Iterator, Iterator)) {
                auto seed = entropy();
                return std::async(std::launch::async, [=]{
                    std::mt19937 rng(seed);
                    auto resampled = resample(rng, n_resamples, first, last, f);
                    return bootstrap(confidence_level, first, last, resampled, f);
                });
            };

            auto mean_future = estimate(mean);
            auto stddev_future = estimate(stddev);

            auto mean_estimate = mean_future.get();
            auto stddev_estimate = stddev_future.get();

            double outlier_variance = detail::outlier_variance(mean_estimate, stddev_estimate, n);

            return { mean_estimate, stddev_estimate, outlier_variance };
        }
    } // namespace detail
} // namespace nonius

#include <algorithm>
#include <iterator>
#include <tuple>
#include <vector>
#include <cmath>

namespace nonius {
    namespace detail {
        template <typename Clock>
        std::vector<double> resolution(int k) {
            std::vector<TimePoint<Clock>> times;
            times.reserve(k+1);
            std::generate_n(std::back_inserter(times), k+1, now<Clock>{});

            std::vector<double> deltas;
            deltas.reserve(k);
            std::transform(std::next(times.begin()), times.end(), times.begin(),
                              std::back_inserter(deltas),
                              [](TimePoint<Clock> a, TimePoint<Clock> b) { return static_cast<double>((a - b).count()); });

            return deltas;
        }

        const auto warmup_seed = 10000;
        const auto clock_resolution_estimation_time = chrono::milliseconds(500);
        const auto clock_cost_estimation_time_limit = chrono::seconds(1);
        const auto clock_cost_estimation_tick_limit = 100000;
        const auto clock_cost_estimation_time = chrono::milliseconds(10);
        const auto clock_cost_estimation_iterations = 10000;

        template <typename Clock>
        int warmup() {
            return run_for_at_least<Clock>(chrono::duration_cast<Duration<Clock>>(warmup_time), warmup_seed, &resolution<Clock>)
                    .iterations;
        }
        template <typename Clock>
        environment_estimate<FloatDuration<Clock>> estimate_clock_resolution(int iterations) {
            auto r = run_for_at_least<Clock>(chrono::duration_cast<Duration<Clock>>(clock_resolution_estimation_time), iterations, &resolution<Clock>)
                    .result;
            return {
                FloatDuration<Clock>(mean(r.begin(), r.end())),
                classify_outliers(r.begin(), r.end()),
            };
        }
        template <typename Clock>
        environment_estimate<FloatDuration<Clock>> estimate_clock_cost(FloatDuration<Clock> resolution) {
            auto time_limit = std::min(resolution * clock_cost_estimation_tick_limit, FloatDuration<Clock>(clock_cost_estimation_time_limit));
            auto time_clock = [](int k) {
                return detail::measure<Clock>([k]{
                    for(int i = 0; i < k; ++i) {
                        volatile auto ignored = Clock::now();
                        (void)ignored;
                    }
                }).elapsed;
            };
            time_clock(1);
            int iters = clock_cost_estimation_iterations;
            auto&& r = run_for_at_least<Clock>(chrono::duration_cast<Duration<Clock>>(clock_cost_estimation_time), iters, time_clock);
            std::vector<double> times;
            int nsamples = static_cast<int>(std::ceil(time_limit / r.elapsed));
            times.reserve(nsamples);
            std::generate_n(std::back_inserter(times), nsamples, [time_clock, &r]{
                        return (time_clock(r.iterations) / r.iterations).count();
                    });
            return {
                FloatDuration<Clock>(mean(times.begin(), times.end())),
                classify_outliers(times.begin(), times.end()),
            };
        }
    } // namespace detail
} // namespace nonius

// #included from: detail/analyse.h++
// Nonius - C++ benchmarking tool
//
// Written in 2014 by Martinho Fernandes <martinho.fernandes@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>

// Run and analyse one benchmark

#define NONIUS_DETAIL_ANALYSE_HPP

#include <algorithm>
#include <iterator>
#include <vector>

namespace nonius {
    namespace detail {
        template <typename Duration, typename Iterator>
        sample_analysis<Duration> analyse(configuration cfg, environment<Duration>, Iterator first, Iterator last) {
            std::vector<double> samples;
            samples.reserve(last - first);
            std::transform(first, last, std::back_inserter(samples), [](Duration d) { return d.count(); });

            auto analysis = nonius::detail::analyse_samples(cfg.confidence_interval, cfg.resamples, samples.begin(), samples.end());
            auto outliers = nonius::detail::classify_outliers(samples.begin(), samples.end());

            auto wrap_estimate = [](estimate<double> e) {
                return estimate<Duration> {
                    Duration(e.point),
                    Duration(e.lower_bound),
                    Duration(e.upper_bound),
                    e.confidence_interval,
                };
            };
            std::vector<Duration> samples2;
            samples2.reserve(samples.size());
            std::transform(samples.begin(), samples.end(), std::back_inserter(samples2), [](double d) { return Duration(d); });
            return {
                std::move(samples2),
                wrap_estimate(analysis.mean),
                wrap_estimate(analysis.standard_deviation),
                outliers,
                analysis.outlier_variance,
            };
        }
    } // namespace detail
} // namespace nonius

#include <exception>
#include <utility>

namespace nonius {
    namespace detail {
        template <typename Clock>
        environment<FloatDuration<Clock>> measure_environment(reporter& rep) {
            rep.warmup_start();
            auto iters = detail::warmup<Clock>();
            rep.warmup_end(iters);

            rep.estimate_clock_resolution_start();
            auto resolution = detail::estimate_clock_resolution<Clock>(iters);
            rep.estimate_clock_resolution_complete(resolution);

            rep.estimate_clock_cost_start();
            auto cost = detail::estimate_clock_cost<Clock>(resolution.mean);
            rep.estimate_clock_cost_complete(cost);

            return { resolution, cost };
        }
    } // namespace detail

    struct benchmark_user_error : virtual std::exception {
        char const* what() const NONIUS_NOEXCEPT override {
            return "a benchmark failed to run successfully";
        }
    };

    template <typename Fun>
    detail::CompleteType<detail::ResultOf<Fun()>> user_code(reporter& rep, Fun&& fun) {
        try {
            return detail::complete_invoke(std::forward<Fun>(fun));
        } catch(...) {
            rep.benchmark_failure(std::current_exception());
            throw benchmark_user_error();
        }
    }

    template <typename Clock = default_clock, typename Iterator>
    void go(configuration cfg, Iterator first, Iterator last, reporter& rep) {
        rep.configure(cfg);

        auto env = detail::measure_environment<Clock>(rep);

        rep.suite_start();

        for(; first != last; ++first) {
            try {
                rep.benchmark_start(first->name);

                auto plan = user_code(rep, [&first, &cfg, &env]{ return first->template prepare<Clock>(cfg, env); });
                rep.measurement_start(plan);
                auto samples = user_code(rep, [&first, &cfg, &env, &plan]{ return first->template run<Clock>(cfg, env, plan); });
                rep.measurement_complete(std::vector<fp_seconds>(samples.begin(), samples.end()));

                if(!cfg.no_analysis) {
                    rep.analysis_start();
                    auto analysis = detail::analyse(cfg, env, samples.begin(), samples.end());
                    rep.analysis_complete(analysis);
                }

                rep.benchmark_complete();
            } catch(benchmark_user_error const&) {
                continue;
            }
        }

        rep.suite_complete();
    }
    template <typename Clock = default_clock, typename Iterator>
    void go(configuration cfg, Iterator first, Iterator last, reporter&& rep) {
        go(cfg, first, last, rep);
    }
    template <typename Clock = default_clock, typename Iterator>
    void go(configuration cfg, Iterator first, Iterator last) {
        go(cfg, first, last, *reporter_registry()[cfg.reporter]);
    }
} // namespace nonius

#endif // NONIUS_HPP

// #included from: reporters/csv_reporter.h++
// Nonius - C++ benchmarking tool
//
// Written in 2014 by Martinho Fernandes <martinho.fernandes@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>

// CSV raw data reporter

#define NONIUS_REPORTERS_CSV_REPORTER_HPP

#include <ios>
#include <iomanip>
#include <algorithm>
#include <string>
#include <iterator>
#include <limits>
#include <unordered_map>
#include <vector>

namespace nonius {
    struct csv_reporter : reporter {
    private:
        std::string description() override {
            return "outputs samples to a CSV file";
        }

        void do_configure(configuration& cfg) override {
            cfg.no_analysis = true;
            n_samples = cfg.samples;
        }

        void do_benchmark_start(std::string const& name) override {
            current = name;
        }

        void do_measurement_complete(std::vector<fp_seconds> const& samples) override {
            data[current] = samples;
        }

        void do_benchmark_failure(std::exception_ptr) override {
            error_stream() << current << " failed to run successfully\n";
        }

        void do_suite_complete() override {
            stream() << std::fixed;
            stream().precision(std::numeric_limits<double>::digits10);
            bool first = true;
            for(auto&& kv : data) {
                if(!first) stream() << ",";
                stream() << "\"" << escape(kv.first) << "\""; // TODO escape
                first = false;
            }
            stream() << "\n";
            for(int i = 0; i < n_samples; ++i) {
                first = true;
                for(auto&& kv : data) {
                    if(!first) stream() << ",";
                    stream() << kv.second[i].count();
                    first = false;
                }
                stream() << "\n";
            }
        }

    private:
        static std::string escape(std::string const& source) {
            auto first = source.begin();
            auto last = source.end();

            int quotes = std::count(first, last, '"');
            if(quotes == 0) return source;

            std::string escaped;
            escaped.reserve(source.size() + quotes);

            while(first != last) {
                auto next_quote = std::find(first, last, '"');
                std::copy(first, next_quote, std::back_inserter(escaped));
                first = next_quote;
                if(first != last) {
                    ++first;
                    escaped.push_back('"');
                    escaped.push_back('"');
                }
            }

            return escaped;
        }

        int n_samples;
        std::string current;
        std::unordered_map<std::string, std::vector<fp_seconds>> data;
    };

    NONIUS_REPORTER("csv", csv_reporter);
} // namespace nonius

// #included from: detail/argparse.h++
// Nonius - C++ benchmarking tool
//
// Written in 2014 by Martinho Fernandes <martinho.fernandes@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>

// Command-line argument parsing

#define NONIUS_ARGPARSE_HPP

// #included from: detail/mismatch.h++
// Nonius - C++ benchmarking tool
//
// Written in 2014 by Martinho Fernandes <martinho.fernandes@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>

// mismatch algorithm

#define NONIUS_DETAIL_MISMATCH_HPP

#include <utility>

namespace nonius {
    namespace detail {
        template <typename InputIt1, typename InputIt2, typename BinaryPredicate>
        std::pair<InputIt1, InputIt2> mismatch(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, BinaryPredicate p) {
            while(first1 != last1 && first2 != last2 && p(*first1, *first2)) {
                ++first1, ++first2;
            }
            return std::make_pair(first1, first2);
        }
    } // namespace detail
} // namespace nonius

#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <ostream>
#include <iomanip>
#include <tuple>
#include <functional>

namespace nonius {
    namespace detail {
        struct option {
            bool matches_short(std::string const& s) const {
                return s == ("-" + short_form);
            }
            std::tuple<bool, std::string::const_iterator> long_separator(std::string const& s) const {
                auto l = "--" + long_form;
                auto its = detail::mismatch(s.begin(), s.end(), l.begin(), l.end(), [](char a, char b) { return a == b; });
                return std::make_tuple(its.second == l.end(), its.first);
            }
            bool matches_long(std::string const& s) const {
                return std::get<0>(long_separator(s));
            }
            bool matches_long(std::string const& s, std::string& argument) const {
                bool match; std::string::const_iterator it;
                std::tie(match, it) = long_separator(s);
                if(match && it != s.end()) {
                    if(*it == '=') argument.assign(it+1, s.end());
                    else return false;
                }
                return match;
            }

            option(std::string long_form, std::string short_form, std::string description, std::string argument = std::string(), bool multiple = false)
            : long_form(std::move(long_form)), short_form(std::move(short_form)), description(std::move(description)), argument(std::move(argument)), multiple(multiple) {}

            std::string long_form;
            std::string short_form;
            std::string description;
            std::string argument;
            bool multiple;
        };

        using option_set = std::vector<option>;

        struct help_text {
            help_text(std::string name, option_set const& options) : name(std::move(name)), options(options) {}
            std::string name;
            option_set const& options;
        };

        template <typename Iterator, typename Projection>
        int get_max_width(Iterator first, Iterator last, Projection proj) {
            auto it = std::max_element(first, last, [&proj](option const& a, option const& b) { return proj(a) < proj(b); });
            return proj(*it);
        }

        inline std::ostream& operator<<(std::ostream& os, help_text h) {
            os << "Usage: " << h.name << " [OPTIONS]\n\n";

            auto lwidth = 2 + get_max_width(h.options.begin(), h.options.end(), [](option const& o) { return 2 + o.long_form.size() + 1 + o.argument.size(); });
            auto swidth = 2 + get_max_width(h.options.begin(), h.options.end(), [](option const& o) { return 1 + o.short_form.size() + 1 + o.argument.size(); });

            os << std::left;
            for(auto o : h.options) {
                auto l = "--" + o.long_form;
                auto s = "-" + o.short_form;
                if(!o.argument.empty()) {
                    l += "=" + o.argument;
                    s += " " + o.argument;
                }
                os << std::setw(lwidth) << l
                   << std::setw(swidth) << s
                   << o.description
                   << '\n';
            }
            return os;
        }

        using arguments = std::unordered_map<std::string, std::string>;

        struct argument_error {
            virtual ~argument_error() = default;
        };

        template <typename Iterator>
        void parse_short(option const& o, arguments& args, Iterator& first, Iterator last) {
            if(!o.argument.empty()) {
                if(++first != last) {
                    args.emplace(o.long_form, *first);
                } else {
                    throw argument_error();
                }
            } else {
                args.emplace(o.long_form, "");
            }
        }
        inline void parse_long(option const& o, arguments& args, std::string&& arg) {
            args.emplace(o.long_form, std::move(arg));
        }

        template <typename Iterator>
        arguments parse_arguments(option_set const& options, Iterator first, Iterator last) {
            arguments args;
            for(; first != last; ++first) {
                bool parsed = false;
                for(auto&& option : options) {
                    if(option.matches_short(*first)) {
                        parse_short(option, args, first, last);
                        parsed = true;
                        break;
                    } else {
                        std::string arg;
                        if(option.matches_long(*first, arg)) {
                            parse_long(option, args, std::move(arg));
                            parsed = true;
                            break;
                        }
                    }
                }
                if(!parsed) {
                    throw argument_error();
                }
            }
            return args;
        }
    } // namespace detail
} // namespace nonius

#include <vector>
#include <string>
#include <stdexcept>
#include <exception>
#include <iostream>
#include <iomanip>
#include <utility>

namespace nonius {
    namespace detail {
        template <typename T>
        struct parser;
        template <>
        struct parser<int> {
            static int parse(std::string const& s) { return std::stoi(s); }
        };
        template <>
        struct parser<double> {
            static double parse(std::string const& s) { return std::stod(s); }
        };
        template <>
        struct parser<std::string> {
            static std::string parse(std::string const& s) { return s; }
        };
        template <>
        struct parser<bool> {
            static bool parse(std::string const&) { return true; }
        };
        template <typename T, typename Predicate>
        void parse(T& variable, detail::arguments& args, std::string const& option, Predicate&& is_valid) {
            auto it = args.find(option);
            if(it != args.end()) {
                auto value = parser<T>::parse(it->second);
                if(is_valid(value)) {
                    variable = value;
                } else {
                    throw argument_error();
                }
            }
        }
        template <typename T>
        void parse(T& variable, detail::arguments& args, std::string const& option) {
            return parse(variable, args, option, [](T const&) { return true; });
        }

        detail::option_set command_line_options {
            detail::option("help", "h", "show this help message"),
            detail::option("samples", "s", "number of samples to collect (default: 100)", "SAMPLES"),
            detail::option("resamples", "rs", "number of resamples for the bootstrap (default: 100000)", "RESAMPLES"),
            detail::option("confidence-interval", "ci", "confidence interval for the bootstrap (between 0 and 1, default: 0.95)", "INTERVAL"),
            detail::option("output", "o", "output file (default: <stdout>)", "FILE"),
            detail::option("reporter", "r", "reporter to use (default: standard)", "REPORTER"),
            detail::option("no-analysis", "A", "perform only measurements; do not perform any analysis"),
            detail::option("list", "l", "list benchmarks"),
            detail::option("list-reporters", "lr", "list available reporters"),
            detail::option("verbose", "v", "show verbose output (mutually exclusive with -q)"),
            detail::option("summary", "q", "show summary output (mutually exclusive with -v)"),
        };

        template <typename Iterator>
        configuration parse_args(std::string const& name, Iterator first, Iterator last) {
            try {
                auto args = detail::parse_arguments(command_line_options, first, last);

                configuration cfg;

                auto is_positive = [](int x) { return x > 0; };
                auto is_ci = [](double x) { return x > 0 && x < 1; };
                auto is_reporter = [](std::string const x) { return reporter_registry().count(x) > 0; };

                parse(cfg.help, args, "help");
                parse(cfg.samples, args, "samples", is_positive);
                parse(cfg.resamples, args, "resamples", is_positive);
                parse(cfg.confidence_interval, args, "confidence-interval", is_ci);
                parse(cfg.output_file, args, "output");
                parse(cfg.reporter, args, "reporter", is_reporter);
                parse(cfg.no_analysis, args, "no-analysis");
                parse(cfg.list_benchmarks, args, "list");
                parse(cfg.list_reporters, args, "list-reporters");
                parse(cfg.verbose, args, "verbose");
                parse(cfg.summary, args, "summary");
                if(cfg.verbose && cfg.summary) throw argument_error();

                return cfg;
            } catch(...) {
                std::cout << help_text(name, command_line_options);
                throw argument_error();
            }
        }
    } // namespace detail

    int print_help(std::string const& name) {
        std::cout << detail::help_text(name, detail::command_line_options);
        return 0;
    }
    int list_benchmarks() {
        std::cout << "All available benchmarks:\n";
        for(auto&& b : benchmark_registry()) {
            std::cout << "  " << b.name << "\n";
        }
        std::cout << benchmark_registry().size() << " benchmarks\n\n";
        return 0;
    }
    int list_reporters() {
        using reporter_entry_ref = decltype(*reporter_registry().begin());
        auto cmp = [](reporter_entry_ref a, reporter_entry_ref b) { return a.first.size() < b.first.size(); };
        auto width = 2 + std::max_element(reporter_registry().begin(), reporter_registry().end(), cmp)->first.size();

        std::cout << "Available reporters:\n";
        std::cout << std::left;
        for(auto&& r : reporter_registry()) {
            if(!r.first.empty()) {
                std::cout << "  " << std::setw(width) << r.first << r.second->description() << "\n";
            }
        }
        std::cout << '\n';
        return 0;
    }
    int run_it(configuration cfg) {
        try {
            nonius::go(cfg, benchmark_registry().begin(), benchmark_registry().end());
        } catch(...) {
            std::cerr << "PANIC: clock is on fire\n";
            try {
                throw;
            } catch(std::exception const& e) {
                std::cerr << "  " << e.what() << "\n";
            } catch(...) {}
            return 23;
        }
        return 0;

    }

    template <typename Iterator>
    int main(std::string const& name, Iterator first, Iterator last) {
        configuration cfg;

        try {
            cfg = detail::parse_args(name, first, last);
        } catch(detail::argument_error const&) {
            return 17;
        }

        if(cfg.help) return print_help(name);
        else if(cfg.list_benchmarks) return list_benchmarks();
        else if(cfg.list_reporters) return list_reporters();
        else return run_it(cfg);
    }
    inline int main(int argc, char** argv) {
        std::string name(argv[0]);
        std::vector<std::string> args(argv+1, argv+argc);
        return main(name, args.begin(), args.end());
    }
}

int main(int argc, char** argv) {
    return nonius::main(argc, argv);
}

#endif // NONIUS_SINGLE_INCLUDE_HPP
