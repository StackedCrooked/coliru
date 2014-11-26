#include <chrono>
#include <cstdio>
#include <tuple>

// Returns year/month/day triple in civil calendar
// Preconditions:  z is number of days since 1970-01-01 and is in the range:
//                   [numeric_limits<Int>::min(), numeric_limits<Int>::max()-719468].
template <class Int>
constexpr std::tuple<Int, unsigned, unsigned> civil_from_days(Int z) noexcept {
    static_assert(
	  std::numeric_limits<unsigned>::digits >= 18,
	  "This algorithm has not been ported to a 16 bit unsigned integer");
	static_assert(
	  std::numeric_limits<Int>::digits >= 20,
	  "This algorithm has not been ported to a 16 bit signed integer");
	z += 719468;
	const Int era = (z >= 0 ? z : z - 146096) / 146097;
	const unsigned doe = static_cast<unsigned>(z - era * 146097); // [0, 146096]
	const unsigned yoe =
	  (doe - doe / 1460 + doe / 36524 - doe / 146096) / 365;      // [0, 399]
	const Int y = static_cast<Int>(yoe) + era * 400;
	const unsigned doy = doe - (365 * yoe + yoe / 4 - yoe / 100); // [0, 365]
	const unsigned mp = (5 * doy + 2) / 153;                      // [0, 11]
	const unsigned d = doy - (153 * mp + 2) / 5 + 1;              // [1, 31]
	const unsigned m = (mp < 10 ? mp + 3 : mp - 9);               // [1, 12]
	return std::tuple<Int, unsigned, unsigned>(y + (m <= 2), m, d);
}

template <typename Duration = std::chrono::hours>
void print_time(Duration timezone_adjustment = std::chrono::hours(0)) {
	using namespace std;
	using namespace std::chrono;
	typedef duration<int, ratio_multiply<hours::period, ratio<24>>::type> days;
	system_clock::time_point now = system_clock::now();
	system_clock::duration tp = now.time_since_epoch();

	tp += timezone_adjustment;

	days d = duration_cast<days>(tp);
	tp -= d;
	hours h = duration_cast<hours>(tp);
	tp -= h;
	minutes m = duration_cast<minutes>(tp);
	tp -= m;
	seconds s = duration_cast<seconds>(tp);
	tp -= s;

	auto date = civil_from_days(d.count()); // assumes that system_clock uses
	                                        // 1970-01-01 0:0:0 UTC as the epoch,
                                            // and does not count leap seconds.

	std::printf("[%04u-%02u-%02u %02lu:%02lu:%02llu.%03llu]\n", std::get<0>(date),
	            std::get<1>(date), std::get<2>(date), h.count(), m.count(),
	            s.count(), tp/milliseconds(1));
}

int main() {
	print_time();
	print_time(std::chrono::hours(-6));
}
