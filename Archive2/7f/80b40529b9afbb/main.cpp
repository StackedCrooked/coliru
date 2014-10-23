template <>
std::string to_string <gui_ntf_t>(const gui_ntf_t& ntf)
{
    std::stringstream ss;
    ss  << "time_point(" << time_point(ntf)                            << "), "
    << "location("   << x(location(ntf))<< "," << y(location(ntf)) << "), "
    << "msg(\""      << msg(ntf)                                   << "\")";
    
    return ss.str();
}

template <typename T>
std::string to_string(const T& data)
{
    std::stringstream ss;
    ss << data;
    return ss.str();
}