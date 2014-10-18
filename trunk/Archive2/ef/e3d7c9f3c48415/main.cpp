#include <iostream>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/format.hpp>

int main()
{
    using namespace boost::gregorian;

	auto const today = day_clock::local_day();
    auto const dow = date(today.year(), today.month(), 1).day_of_week();
    auto const d = gregorian_calendar::end_of_month_day(today.year(), today.month());

	for (auto sw = 0, i = 1; sw < d; i++) {
		if (i > dow)
			std::cout << boost::format("%2d") % ++sw;
	
        !(i % 7) || sw == d ? std::cout << '\n' : std::cout << '\t';
	}
}
