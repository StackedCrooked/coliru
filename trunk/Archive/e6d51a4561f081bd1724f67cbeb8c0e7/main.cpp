#include <cctype>
//#include <chrono>
#include <boost/chrono.hpp>
#include <map>
#include <string>
#include <ppl.h>
#include <windows.h>
#include <wrl.h>

namespace wrl = Microsoft::WRL::Wrappers;
namespace ppl = concurrency;

//typedef std::chrono::high_resolution_clock clock_type;
//typedef std::chrono::duration<double>      real_duration;
//using   std::chrono::duration_cast;

#define ASSERT(expr) _ASSERTE(expr)
#ifdef _DEBUG
#define VERIFY(expr) ASSERT(expr)
#else
#define VERIFY(expr) (expr)
#endif

class file_view
{
    char const * m_view;
    LARGE_INTEGER m_size;
    typedef wrl::HandleT<wrl::HandleTraits::HANDLENullTraits> MapHandle;

    file_view(file_view const&);            // not implemented
    file_view& operator=(file_view const&); // not implemented
public:

    file_view(char const * name) throw() :
        m_view(),
        m_size()
    {
        ASSERT(name);

        wrl::FileHandle const file(CreateFile(name,
                                              GENERIC_READ,
                                              FILE_SHARE_READ,
                                              nullptr, // default security
                                              OPEN_EXISTING,
                                              FILE_ATTRIBUTE_NORMAL,
                                              nullptr)); // no template
        if (!file.IsValid()) return;

        VERIFY(GetFileSizeEx(file.Get(), &m_size));
        if (m_size.QuadPart == 0) return;

        MapHandle const map(CreateFileMapping(file.Get(),
                                              nullptr, // default security
                                              PAGE_READONLY,
                                              0, 0, // match file size
                                              nullptr)); // no name
        VERIFY(map.IsValid());

        m_view = static_cast<char const *>(MapViewOfFile(map.Get(),
                                                         FILE_MAP_READ,
                                                         0, 0, // offset
                                                         0)); // match file size
    }

    ~file_view() throw()
    {
        if (valid())
        {
            VERIFY(UnmapViewOfFile(m_view));
        }
    }

    bool valid() const throw() // If !valid() call GetLastError for reason
    {
        return nullptr != m_view;
    }

    char const * begin() const throw()
    {
        ASSERT(valid());
        return m_view;
    }

    char const * end() const throw()
    {
        return begin() + m_size.QuadPart;
    }
};

int main(int argc, char ** argv)
{
    auto const start_time = boost::chrono::steady_clock::now();

    typedef std::map<std::string, unsigned> word_map;
    ppl::combinable<word_map> shared;

    ppl::parallel_for_each(argv + 1, argv + argc, [&](char const * name)
    {
        file_view const file(name);
        if (!file.valid()) return;

        auto & result = shared.local();
        char const * word_first = nullptr;

        for (auto it = file.begin(); it != file.end(); ++it)
        {
            if (*it < 0 || (!std::isalnum(*it) && *it != '_'))
            {
                if (word_first)
                {
                    ++result[std::string(word_first, it)];
                }

                word_first = nullptr;
            }
            else if (!word_first)
            {
                word_first = it;
            }
        }

        if (word_first)
        {
            ++result[std::string(word_first, file.end())];
        }
    });

    word_map result;

    shared.combine_each([&] (word_map const & source)
    {
        for (auto const & w : source)
        {
            result[w.first] += w.second;
        }
    });

    //double const elapsed = duration_cast<real_duration>(end_time - start_time).count();

    for (auto const & w : result)
    {
        printf("%s: %u\n", w.first.c_str(), w.second);
    }
    printf("\nWords: %u\n", static_cast<unsigned>(result.size()));
    auto const end_time = boost::chrono::steady_clock::now();
    std::clog << "Time elapsed: " <<  boost::chrono::duration<double>(end_time - start_time) << std::endl;

}
