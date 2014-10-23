#include <functional>
#include <regex>
#include <memory>
#include <algorithm>
#include <tuple>
#include <utility>
#include <iostream>
#include <string>
#include <sstream>
#include <ctime>

#include <exception>
#ifdef   AND
#include <android/log.h>
#include <stdio.h>
#include <jni.h>

void mylog(std::string str)
{
    __android_log_print(ANDROID_LOG_DEBUG, "cocos2d-x debug info",  str.c_str());
}
#endif

//=============================================================================
// DB query :  typedef and util function
typedef  std::string             db_field_t;
typedef  std::vector<db_field_t> db_row_t;
typedef  std::vector<db_row_t>   db_rows_t;

std::size_t field_count(const db_row_t&  row)   { return row.size();}
std::size_t row_count  (const db_rows_t& rows)  { return rows.size();}

template <int n>
db_field_t field(const db_row_t& row)
{
    return row[n];
}

//=============================================================================
// Sample type for gui notify message

// locatoin_t := <x,y>
typedef std::tuple<int, int> location_t;
int x(const location_t& p) { return std::get<0>(p); };
int y(const location_t& p) { return std::get<1>(p); };

// gui_ntf_t :=<time_point, location, msg>,
typedef std::tuple<std::time_t, location_t, std::string> gui_ntf_t;
time_t      time_point (const gui_ntf_t& row) { return std::get<0>(row); };
location_t  location   (const gui_ntf_t& row) { return std::get<1>(row); };
std::string msg        (const gui_ntf_t& row) { return std::get<2>(row); };

// for logging or debugging
std::string to_string(const gui_ntf_t& ntf)
{
    std::stringstream ss;
    ss  << "time_point(" << time_point(ntf)                            << "), "
    << "location("   << x(location(ntf))<< "," << y(location(ntf)) << "), "
    << "msg(\""      << msg(ntf)                                   << "\")";
    return ss.str();
}

//=============================================================================
// test 01
namespace test_01
{
    
    // Sample functions for DB emulate 01.
    db_rows_t make_sample_01()
    {
        static const std::string table[5][3] = {
            {"2014-10-22 17:10:43", "<58,99>", "hello"  },
            {"2014-10-22 17:20:43", "<32,41>", "python"  },
            {"2014-10-22 17:25:43", "<1,,22>", "java", },
            {"2014-10-22 17;26:43", "<25,65>", "caharp",},
            {"2014-10-22 17:27:43", "<23,87>", "c++",   },
        };
        
        std::function<db_row_t(const std::string[3])> convert =
        [](const std::string strs[3]) -> db_row_t
        {
            db_row_t row;
            std::copy(&strs[0], &strs[3], std::back_inserter(row));
            return row;
        };
        
        db_rows_t rows;
        std::transform(begin(table), end(table), std::back_inserter(rows), convert);
        return rows;
    }
    
    db_rows_t db_select_emulate_01()
    {
        return  make_sample_01();
    }
    
    // "2014-10-22 17:20:43"
    std::time_t to_time_point(int year, int month, int day,
                              int hour, int minute, int second)
    {
        std::tm t = {second, minute, hour, 0, month-1, year-1900, 0, 0, 0};
        return  std::mktime(&t);
    }
    
    // "2014-10-22 17:20:43"
    std::time_t to_time_point(const std::string& cell)
    {
        int year, month, day, hour, minuite, second;
        
        std::sscanf(cell.c_str(), "%d-%d-%d %d:%d:%d",
                    &year, &month, &day, &hour, &minuite, &second);
        
        return  to_time_point(year, month, day, hour, minuite, second);
    };
    
    // "<234,567>"
    
    location_t to_location(int x, int y) { return location_t(x, y);};
    location_t to_location(const std::string& cell)
    {
        int x, y;
        std::sscanf(cell.c_str(), "<%d,%d>", &x, &y);
        return to_location(x, y);
    };
    
    // "hello"
    std::string to_msg(const std::string& cell)
    {
        return cell;
    }
    
    template<typename Logger, typename LineSeperator>
    void main(Logger& logger, LineSeperator& endl)
    {
        // ["<3,0>", "1413899956", "hello"]
        auto to_ntf_log = [&](const db_row_t& dbrow) -> gui_ntf_t
        {
            return gui_ntf_t( to_time_point(field<0>(dbrow)),
                             to_location  (field<1>(dbrow)),
                             to_msg       (field<2>(dbrow)));
        };
        
        const auto db_rows =  db_select_emulate_01();
        std::vector<gui_ntf_t> gui_ntfs;
        
        std::transform(begin(db_rows), end(db_rows), std::back_inserter(gui_ntfs),
                       to_ntf_log);
        
        logger << "---------------------------------" << endl;
        logger << "test 01"                           << endl;
        logger << "print ntfs"  << endl << endl;
        
        auto logging = [&](const gui_ntf_t& ntf){ logger << to_string(ntf) << endl; };
        
        std::for_each(begin(gui_ntfs), end(gui_ntfs), logging);
        
        logger << endl;
    }
    
} // end of  namespace test_01
//------------------------------------------------------------------------------


//=============================================================================
// maybe Util for error/uninitialize state check

static const auto kUnInitString = std::make_shared<std::string>("uninitialized");

struct nothing_t
{
    nothing_t(const std::string& s) : s_(s) {}
    std::string s_;
};

nothing_t nothing(const std::string& errmsg = *kUnInitString )
{
    return nothing_t(errmsg);
};

template <typename T>
struct maybe_t : public std::pair<T, std::shared_ptr<std::string>>
{
    typedef typename std::pair<T, std::shared_ptr<std::string>> basetype_t;
    
    // constructor with uninitialized value
    maybe_t() : basetype_t(T(), kUnInitString) {};
    
    // coverting constructor
    maybe_t(const T& val) : basetype_t(val, nullptr) {};
    
    maybe_t(T&& val) : basetype_t(std::move(val), nullptr) {};
    
    // copy constructor
    maybe_t(const maybe_t<T>& other) :basetype_t(other) {};
    
    // implicit conversion  function. in haskell just.
    operator T() const { return value(); };
    
    // explicit get
    T value() const { return basetype_t::first; };
    
    // test
    bool valid()   const { return basetype_t::second == nullptr;}
    bool invalid() const { return !valid();}
    
    // pudae : nothing_t 예제
    maybe_t(const nothing_t& e) :
    basetype_t(T(), std::make_shared<std::string>(e.s_)) {}
    
    std::string error() const
    {
        auto p = basetype_t::second;
        return  p != nullptr ? *p : "";
    }
};

//=============================================================================
// Sample functions for DB emulate 01.
maybe_t<db_rows_t> make_sample_02()
{
    return test_01::make_sample_01();
}

std::shared_ptr<db_rows_t> db_select_emulate_02()
{
    auto result = make_sample_02();
    if (result.invalid())
    return nullptr;
    
    return std::make_shared<db_rows_t>(result);
}

//=============================================================================
// test 02

namespace test_02
{
    
    int to_int(std::smatch& m, int i) { return std::atoi(m[i].str().c_str()); }
    
    // "2014-10-22 17:20:43"
    maybe_t<std::time_t> to_time_point(const std::string& cell)
    {
        try
        {
            const std::regex pattern("\\s*(\\d+)-(\\d+)-(\\d+)\\s+(\\d+):(\\d+):(\\d+)\\s*");
            std::smatch m;
            if (!std::regex_match(cell, m, pattern))
            return nothing("invalid date_time pattern");
            
            auto toi = [&](int i) { return  to_int(m, i);};
            return test_01::to_time_point(toi(1), toi(2), toi(3), toi(4), toi(5), toi(6));
        }
        catch (std::exception& e)
        {
            return nothing(e.what());
        }
    }
    
    // "<234,567>"
    maybe_t<location_t> to_location(const std::string& cell)
    {
        try
        {
            const std::regex pattern("<(\\d+),(\\d+)>");
            std::smatch m;
            if (!std::regex_match(cell, m, pattern))
            return nothing("invalid location pattern");
            
            auto toi = [&](int i) { return  to_int(m, i);};
            
            return location_t(toi(1), toi(2));
        }
        catch (std::exception& e)
        {
            return nothing(e.what());
        }
    };
    
    // "hello"
    maybe_t<std::string> to_msg(const std::string& cell)
    {
        if (cell.size() == 0)
        return nothing("invalid message. empty");
        
        return  test_01::to_msg(cell);
    };
    
    template<typename Logger, typename LineSeperator>
    void main(Logger& logger, LineSeperator& endl)
    {
        // ["2014-10-22 17:20:43", "<32,41>", "hello"]
        auto to_ntf_log = [&](const db_row_t& dbrow) -> maybe_t<gui_ntf_t>
        {
            if (field_count(dbrow) < 3)
            return nothing("result set's field size is less than 3");
            
            const auto time_point  = to_time_point(field<0>(dbrow));
            const auto location    = to_location  (field<1>(dbrow));
            const auto msg         = to_msg       (field<2>(dbrow));
            
            if (location.invalid())
            return nothing("reading location field fail. " + location.error());
            if (time_point.invalid())
            return nothing("reading time_point field fail. " + time_point.error());
            if (msg.invalid())
            return nothing("reading msg field fail. " + msg.error());
            
            return gui_ntf_t(time_point.value(), location.value(),  msg.value());
        };
        
        const auto result =  db_select_emulate_02();
        if (result == nullptr)
        {
            logger << "error";
            return;
        }
        
        const auto& db_rows = *result;
        std::vector<maybe_t<gui_ntf_t>> gui_ntfs;
        std::transform(begin(db_rows), end(db_rows), std::back_inserter(gui_ntfs),
                       to_ntf_log);
        
        logger << "---------------------------------" << endl;
        logger << "test 02"                           << endl;
        logger << "print ntfs"  << endl << endl;
        
        auto logging = [&](const maybe_t<gui_ntf_t>& ntf)
        {
            logger << (ntf.valid() ? to_string(ntf) : "error!! " + ntf.error()) << endl;
        };
        
        std::for_each(begin(gui_ntfs), end(gui_ntfs), logging);
        
        logger << endl;
    } // end of main
}// end of namespace test_02



//=============================================================================
// Continuation Passing Util
template <typename T>
struct Value
{
    T val_;
    
    Value(const T& val) : val_(val)
    {
        return;
    };
    
    Value(const Value<T>& other) : val_(other.value())
    {
        return;
    }
    
    // implicit conversion  function
    operator T() const
    {
        return value();
    };
    
    // explicit get real value
    T value() const
    {
        return val_;
    }
    
    template <typename F>
    auto operator() (F f)->Value<maybe_t<decltype(f(val_).value())> >
    {
        auto r = f(val_);
        return Value<maybe_t<decltype(r.value())>>(r);
    }
};

template <int n>
Value<maybe_t<db_field_t>> field_cv(const db_row_t& row)
{
    auto cell = maybe_t<db_field_t>(field<n>(row));
    return cell;
}

//=============================================================================
// test 03
namespace test_03
{
    
    int to_int(std::smatch& m, int i) { return std::atoi(m[i].str().c_str()); }
    
    // "2014-10-22 17:20:43"
    maybe_t<std::time_t> to_time_point(const maybe_t<std::string>& cell)
    {
        if (cell.invalid())
        return nothing(cell.error());
        
        return test_02::to_time_point(cell);
    }
    
    // "<234,567>"
    maybe_t<location_t> to_location(const maybe_t<std::string>& cell)
    {
        if (cell.invalid())
        return nothing(cell.error());
        
        return test_02::to_location(cell);
    };
    
    // "hello"
    maybe_t<std::string> to_msg(const maybe_t<std::string>& cell)
    {
        if (cell.invalid())
        return nothing(cell.error());
        
        auto result = test_02::to_msg(cell);
        return result;
    };
    
    maybe_t<std::string> check_max_size(const maybe_t<std::string>& cell, std::size_t max_size)
    {
        if (cell.invalid())
        return nothing(cell.error());
        
        auto my_size = cell.value().size();
        if (max_size < my_size)
        return nothing(" my size is " + std::to_string((unsigned long long)my_size) +
                       " but max size is " + std::to_string((unsigned long long)max_size));
        return cell;
    };
    
    template<typename Logger, typename LineSeperator>
    void main(Logger& logger, LineSeperator& endl)
    {
        // ["2014-10-22 17:20:43", "<32,41>", "hello"]
        auto to_ntf_log = [&](const db_row_t& dbrow) -> maybe_t<gui_ntf_t>
        {
            
            
            if (field_count(dbrow) < 3)
            return nothing("result set's field size is less than 3");
            
            auto max_msg_length_5 =  [](const maybe_t<std::string>& cell)
            { return check_max_size(cell, std::size_t(5)); };
            
            const auto time_point   = field_cv<0>(dbrow)(to_time_point).value();
            const auto location     = field_cv<1>(dbrow)(to_location).value();
            const auto msg          = field_cv<2>(dbrow)(to_msg)(max_msg_length_5).value();
            
            if (location.invalid())
            return nothing("read location field fail. " + location.error());
            if (time_point.invalid())
            return nothing("read time_point field fail. " + time_point.error());
            if (msg.invalid())
            return nothing("read msg field fail. " + msg.error());
            
            return gui_ntf_t(time_point.value(), location.value(),  msg.value());
        };
        
        const auto result =  db_select_emulate_02();
        if (result == nullptr)
        {
            logger << "error";
            return;
        }
        
        const auto& db_rows = *result;
        
        std::vector<maybe_t<gui_ntf_t>> gui_ntfs;
        std::transform(begin(db_rows), end(db_rows), std::back_inserter(gui_ntfs),
                       to_ntf_log);
        
        auto logging = [&](const maybe_t<gui_ntf_t>& ntf)
        {
            logger << (ntf.valid() ? to_string(ntf) : "error!! " + ntf.error()) << endl;
        };
        
        logger << "---------------------------------" << endl;
        logger << "test 03"                           << endl << endl;
        logger << "print ntfs"  << endl << endl;
        std::for_each(begin(gui_ntfs), end(gui_ntfs), logging);
        logger << endl;
        
        
        
        logger << "------------------" << endl;
        logger << "print all valid ntfs"  << endl << endl;
        auto valid = [](const maybe_t<gui_ntf_t>& ntf) -> bool { return ntf.valid(); };
        auto limit =  std::partition(begin(gui_ntfs), end(gui_ntfs), valid);
        std::for_each(begin(gui_ntfs), limit, logging);
        logger << endl;
        
        logger << "------------------" << endl;
        logger << "print all invalid ntfs"  << endl << endl;
        std::for_each(limit, end(gui_ntfs), logging);
        logger << endl;
        
    }
}// end of namespace test_03

struct mystringstream : public std::stringstream
{
    void flush()    {
#ifdef   AND
        mylog(str().c_str());
#else
        std::cout << str().c_str();
#endif
    }
    
    ~mystringstream()   { flush(); }
};

int main()
{
    {
        mystringstream ss;
        test_01::main(ss, "\n");
    }
    {
        mystringstream ss;
        test_02::main(ss, "\n");
    }
    {
        mystringstream ss;
        test_03::main(ss, "\n");
    }
    return 1;
}
