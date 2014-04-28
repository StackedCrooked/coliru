#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <string>
#include <iterator>
#include <cassert>
#include <boost/utility/string_ref.hpp> // optimization only

// i'm lazy and don't want to keep remembering to pass the sort predicate
struct timestamped_line {
    std::string text;
    timestamped_line(std::string text = "") : text(std::move(text)) { }
    operator std::string const&() const { return text; }

    template <typename T1, typename T2> friend bool operator<(T1 const& a, T2 const& b) { 
        return lessthan(a,b); 
    }

  private:
    static bool lessthan(std::string const& a, std::string const& b) {
        assert(a.length()>=5 && b.length()>=5);

        return boost::string_ref(a).substr(a.length()-5)
            <  boost::string_ref(b).substr(b.length()-5);
    }
};

void split_into_sorted_parts(std::vector<std::string> const& fnames, std::vector<std::string>& file_parts, size_t const batch_size = 10000)
{
    std::vector<timestamped_line> buffer;
    buffer.reserve(batch_size);

    auto process = [&] {
        // sort a part
        std::sort(buffer.begin(), buffer.end());
        // save to temporary file
        std::string const tmpfilename = "merge_sort_tmpfile" + std::to_string(file_parts.size()) + ".tmp";
        std::ofstream ofs(tmpfilename);
        std::copy(buffer.begin(), buffer.end(), std::ostream_iterator<std::string>(ofs, "\n"));
        file_parts.push_back(tmpfilename);
        // reset the buffer
        buffer.clear();
    };

    std::string line;
    for (auto& fname : fnames)
    {
        std::ifstream infile(fname);
        assert(infile);

        while (std::getline(infile, line))
        {
            buffer.push_back(std::move(line));

            if (buffer.size() >= batch_size)
                process();
        }
    }

    if (!buffer.empty())
        process(); // optimize to keep inmemory?
}

template <typename OutIt>
    OutIt merge_file_parts(std::vector<std::string>& file_parts, OutIt out)
{
    // track current line with each input stream
    struct state {
        std::ifstream stream;
        timestamped_line line;

        state(std::string const& fname) : stream(fname) { }
        bool advance() { return std::getline(stream, line.text); }
        bool operator<(state const& o) const { return line < o.line; }
    };

    std::list<state> streams;
    for(auto& fname : file_parts)
        streams.emplace_back(fname);

    // initialize stream states
    for(auto stream = streams.begin(); stream != streams.end();) {
        if (stream->advance()) ++stream;
        else stream = streams.erase(stream);
    }

    while (!streams.empty())
    {
        // select lowest value
        auto select = min_element(streams.begin(), streams.end());
        *out ++ = select->line;

        // increment corresponding stream
        if (!select->advance())
            streams.erase(select);
    }
    return out;
}

int main()
{
    std::vector<timestamped_line> trade, nbbo;

    std::vector<std::string> file_parts;
    split_into_sorted_parts({ "trade.txt", "nbbo.txt" }, file_parts, 10000);
    merge_file_parts(file_parts, std::ostream_iterator<std::string>(std::cout, "\n"));
}
