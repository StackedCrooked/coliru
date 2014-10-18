#include <boost/process.hpp>
#include <boost/iostreams/device/file_descriptor.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/tee.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <iostream>
#include <fstream>

namespace bp = boost::process;
namespace io = boost::iostreams;
using namespace bp;
using namespace bp::initializers;

bp::pipe create_async_pipe()
{
#if defined(BOOST_WINDOWS_API)
    std::string name = "\\\\.\\pipe\\boost_process_async_io";
    HANDLE handle1 = ::CreateNamedPipeA(name.c_str(), PIPE_ACCESS_INBOUND |
        FILE_FLAG_OVERLAPPED, 0, 1, 8192, 8192, 0, NULL);
    HANDLE handle2 = ::CreateFileA(name.c_str(), GENERIC_WRITE, 0, NULL,
        OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);
    return make_pipe(handle1, handle2);
#elif defined(BOOST_POSIX_API)
    return create_pipe();
#endif
}

int main()
{
    bp::pipe p = create_async_pipe();

    {
        io::file_descriptor_sink sink(p.sink, io::close_handle);
        execute(
            run_exe("/bin/sh"),
            set_cmd_line("sh -c \"echo started; sleep 3 && date\""),
            bind_stdout(sink)
        );
    }

    io::file_descriptor_source source(p.source, io::close_handle);
    io::stream<io::file_descriptor_source> is(source);

    std::cout << "Process is running, let's wait before printing\n";

    system("sleep 1");

    std::ofstream ofile("test.log");
    io::filtering_ostream filt(io::tee(std::cout << std::unitbuf, ofile << std::unitbuf));

    std::string s;
    while (std::getline(is, s))
        filt << s << "\n";
}
