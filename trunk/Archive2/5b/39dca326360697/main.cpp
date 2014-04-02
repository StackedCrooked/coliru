#include <boost/locale.hpp>
#include <iostream>

int main()
{
    using namespace boost::locale;
    generator gen;

    std::locale english = gen("en_US.UTF-8");
    std::locale french  = gen("fr_FR.UTF-8");
    std::cout.imbue(english); // this one doesn't matter
    std::locale::global(french);

    {
        std::locale::global(english);
        assert(1 == period::first_day_of_week(date_time()));

        std::locale::global(french);
        assert(2 == period::first_day_of_week(date_time()));
    }

    {
        assert(1 == period::first_day_of_week(date_time(english)));
        assert(2 == period::first_day_of_week(date_time(french)));
    }

    {
        date_time_period_set dtps;
        dtps.add(period::friday());
        dtps.add(period::week_of_year(4));
        // no effect
        dtps.add(period::first_day_of_week(1));

        assert(2 == period::first_day_of_week(date_time(dtps)));
    }

    {
        date_time dt;
        // no effect:
        dt.set(period::first_day_of_week(), 1);
        assert(2 == period::first_day_of_week(dt));
    }

    {
        // associated locale gets copied:
        date_time edt(english), fdt(french);
        assert(1 == period::first_day_of_week(edt));
        edt = date_time(french);
        assert(2 == period::first_day_of_week(edt));
        fdt = date_time(english);
        assert(1 == period::first_day_of_week(fdt));
    }

    std::cout << "All tests passed\n";
}
