#include <iostream>
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/program_options.hpp>

enum class LogSeverityLevel : std::int8_t { E_LOG_TRACE = 0,
                                            E_LOG_DEBUG,
                                            E_LOG_INFO,
                                            E_LOG_WARN,
                                            E_LOG_ERROR};

void validate(boost::any& v,
          const std::vector<std::string>& values,
          LogSeverityLevel*, int)
{
    namespace po = boost::program_options;
    // Make sure no previous assignment to 'a' was made.
    po::validators::check_first_occurrence(v);
    // Extract the first string from 'values'. If there is more than
    // one string, it's an error, and exception will be thrown.
    const std::string& s = po::validators::get_single_string(values);

    const std::string& s_capitalized = boost::to_upper_copy(s);

    if (s_capitalized== "ERROR") {
        v = boost::any(LogSeverityLevel::E_LOG_ERROR);
    } else if (s_capitalized == "WARN") {
        v = boost::any(LogSeverityLevel::E_LOG_WARN);
    } else if (s_capitalized == "INFO") {
        v = boost::any(LogSeverityLevel::E_LOG_INFO);
    } else if (s_capitalized == "DEBUG") {
        v = boost::any(LogSeverityLevel::E_LOG_DEBUG);
    } else if (s_capitalized == "TRACE") {
        v = boost::any(LogSeverityLevel::E_LOG_TRACE);
    } else {
        throw po::validation_error(po::validation_error::invalid_option_value);
    }
}

int main(int ac, char* av[])
{
  namespace po = boost::program_options;
  po::options_description desc;
  desc.add_options()
    ("help,h", "print this help")
    ("version,v", "show application version")
    ("log-level", po::value<LogSeverityLevel>()->default_value(LogSeverityLevel::E_LOG_DEBUG, "DEBUG"), "set log level")
    ;

  po::variables_map vm;
  store(po::command_line_parser(ac, av).options(desc).run(), vm);
  std::cout << desc << std::endl
            << (int) vm["log-level"].as<LogSeverityLevel>() << std::endl;
}