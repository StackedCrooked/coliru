#include <map>

enum class template_line = {first,second,third};

struct tag {
    typedef std::map<template_line, unsigned> template_line_to_val_map;
    typedef template_line template_id;
    template_line_to_val_map get_printing_template(template_id const && profile_id, tag_t const & tag_) const
}

tag::template_line_to_val_map tag::get_printing_template(template_id const && profile_id, tag_t const & tag_) const
{
    template_line_to_val_map m;
    m[template_line::fifth] = 2;
    std::map<tag::template_id,unsigned> s;
    std::pair<template_line,unsigned> p;
    p.first = template_line::second, p.second = 3;
    s.[tag::template_id::second]=2;
    return m;
}

int main() {}
