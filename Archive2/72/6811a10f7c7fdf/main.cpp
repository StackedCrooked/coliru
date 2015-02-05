#include <iostream>
#include <string>
#include <vector>

#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/iterator/filter_iterator.hpp>
#include <boost/range/iterator_range.hpp> //pre-include for sub_range.hpp
#include <boost/range/sub_range.hpp>

class some_class
{
public:
    std::string field;
    
    //field is the only member relevant to the example
    //these other members are just here to explain
    //th eneed for the StringFromClass function below
    int index;
    std::pair<double, double> some_var;
    
    //so algorithms can treat some_class as if it were a simple std::pair
    double& first;
    double& second;
    
    some_class()
     : field("s"),
       index(0),
       some_var(0.0, 0.0),
       first(some_var.first),
       second(some_var.second)
    {
    }
    
    /*
    other members
    */
};

const std::string GetFieldName(const some_class& sc)
{
    return sc.field;
}

const std::string StringFromSomeClass(const some_class& sc)
{
    return std::string (sc.field + "|" + 
                         std::to_string(sc.index) + "|" + 
                         std::to_string(sc.some_var.first) + "|" + 
                         std::to_string(sc.some_var.second));
}

const bool FieldInRange(const some_class& sc, 
                        std::vector<std::string>::const_iterator fields_begin,
                        std::vector<std::string>::const_iterator fields_end)
{
    return std::find(fields_begin,
                     fields_end,
                     sc.field) != fields_end;
}

inline const bool FieldNotInRange(const some_class& sc,
                                  std::vector<std::string>::const_iterator fields_begin,
                                  std::vector<std::string>::const_iterator fields_end)
{
    return !FieldInRange(sc, fields_begin, fields_end);
}

const bool FieldNotInRangeFilter(const some_class& sc,
                                 std::vector<std::string>::const_iterator fields_begin,
                                 std::vector<std::string>::const_iterator fields_end,
                                 const int accuracy_filter)
{
    if (static_cast<int>(sc.some_var.first * accuracy_filter) == static_cast<int>(sc.some_var.second * accuracy_filter))
        return false;
        
        
    /*
        HERE
        
        right here, when my debugger should be stepping
        into FieldNotInRange, it instead steps into
        GetFieldName, which does not make sense to me
        on any level. when I tried commenting out GetFieldName
        then it stepped into StringFromSomeClass instead.
        
        when it steps into either function, the some_class that is passed
        in is uninitialized, so there is an access violation when the function
        tries to access the values
        
        interestingly, coliru segfaults somewhere in here--I am wondering
        if it is doing the same thing
        
        
    */
    return FieldNotInRange(sc, fields_begin, fields_end);
}

class some_row_concept_class
{
public:
    std::vector<some_class> row_values;
};

template<typename PairType_>
inline const bool pair_match(const PairType_& pair_)
{
    return pair_.first == pair_.second;
}

const bool IgnoreFields(const some_row_concept_class& srcc,
                        const boost::sub_range<std::vector<std::string> >& fields_to_ignore,
                        const int float_accuracy)
{
    typedef const bool (filter_signature)(const some_class&);
    typedef boost::function<filter_signature> fil_func_sig;
    
    fil_func_sig filter_func(boost::bind(&FieldNotInRangeFilter,
                                         _1,
                                         fields_to_ignore.begin(),
                                         fields_to_ignore.end(),
                                         float_accuracy));
    
    typedef boost::filter_iterator<fil_func_sig,
                                   std::vector<some_class>::const_iterator> filter_iterator_;
    
    return std::find_if(filter_iterator_(filter_func,
                                         srcc.row_values.begin()),
                        filter_iterator_(),
                        &pair_match<some_class>) != filter_iterator_();
}

class stream_wrapper
{
    //I originally wrote this class to avoid
    //boost::bind-ing the output_stream to the functions below
    //so it is an artifact of that
    
private:
    std::ostream& os;
public:
    inline explicit stream_wrapper(std::ostream& os_) : os(os_) {};
    
    void output_header(const some_row_concept_class& fill_from)
    {
        std::transform(fill_from.row_values.begin(),
                       fill_from.row_values.end(),
                       std::ostream_iterator<std::string>(os, " "),
                       &GetFieldName);
    }
    
    void output_row(const some_row_concept_class& fill_from)
    {
        std::transform(fill_from.row_values.begin(),
                       fill_from.row_values.end(),
                       std::ostream_iterator<std::string>(os, "\n"),
                       &StringFromSomeClass);
    }
};

template<typename InputRange_>
const std::vector<some_row_concept_class> OutputFilteredRowsT(const InputRange_& range,
                                                             std::ostream& output_stream)
{
    if (range.begin() != range.end())
    {
        stream_wrapper sw(output_stream);
        sw.output_header(*range.begin());
        output_stream << std::endl;
        std::for_each(range.begin(),
                      range.end(),
                      [&](const some_row_concept_class& srcc) { sw.output_header(srcc); });
        //in XE6 I can end this std::for_each with 
        //            &sw.output_row);
        //and everything is fine, but that is not actually compliant, so I use a
        //lambda in coliru for the same effect
                      
        output_stream << std::endl;
    }
    
    return std::vector<some_row_concept_class>(range.begin(), range.end());
}

const std::vector<some_row_concept_class> OutputFilteredRows(const boost::sub_range<std::vector<some_row_concept_class> >& rows,
                                                             std::ostream& output_stream,
                                                             const boost::sub_range<std::vector<std::string> >& fields_to_ignore,
                                                             const int accuracy_filter)
{
    typedef const bool (filter_signature)(const some_row_concept_class&);
    typedef boost::function<filter_signature> fil_func_sig;
    
    fil_func_sig filter_func(boost::bind(&IgnoreFields,
                                         _1,
                                         fields_to_ignore,
                                         accuracy_filter));
    
    typedef boost::filter_iterator<fil_func_sig,
                                   boost::sub_range<std::vector<some_row_concept_class> >::const_iterator> filter_iterator_;
    typedef boost::iterator_range<filter_iterator_> filtered_range;
    
    return OutputFilteredRowsT(filtered_range(filter_iterator_(filter_func,
                                                               rows.begin()),
                                              filter_iterator_()),
                               output_stream);
}

int main()
{
    //populate some junk values
    some_row_concept_class dummy_row;
    
    dummy_row.row_values.push_back(some_class());
    dummy_row.row_values.push_back(some_class());
    dummy_row.row_values.push_back(some_class());
    
    std::vector<some_row_concept_class> my_rows;
    my_rows.push_back(dummy_row);
    my_rows.push_back(dummy_row);
    my_rows.push_back(dummy_row);
    
    std::vector<std::string> ignored_fields;
    
    ignored_fields.push_back("some_field");
    ignored_fields.push_back("some_other_field");
    
    OutputFilteredRows(boost::sub_range<std::vector<some_row_concept_class> >(my_rows),
                       std::cout,
                       boost::sub_range<std::vector<std::string> >(ignored_fields),
                       10);
}
