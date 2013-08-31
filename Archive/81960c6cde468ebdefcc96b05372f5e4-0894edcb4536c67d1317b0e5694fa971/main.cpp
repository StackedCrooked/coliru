#include <sys/types.h> // For pid_t.
#include <fstream>
#include <string>

// mock up
#include <boost/variant.hpp>
namespace {
    struct None {};
    struct Error { std::string s; Error(std::string s): s(s){} };
    
    std::ostream& operator<<(std::ostream& os, None const&) {
        return os << "None";
    }

    std::ostream& operator<<(std::ostream& os, Error const& e) {
        return os << "Error {" << e.s << "}";
    }

    template <typename T>
        using Result = boost::variant<None, Error, T>;
}
// end mockup

namespace proc {

    // Snapshot of a process (modeled after /proc/[pid]/stat).
    // For more information, see:
    // http://www.kernel.org/doc/Documentation/filesystems/proc.txt
    struct ProcessStatus
    {
        pid_t pid;
        std::string comm;
        char state;
        pid_t ppid, pgrp, session;
        int tty_nr;
        pid_t tpgid;
        unsigned int flags;
        unsigned long minflt, cminflt, majflt, cmajflt;
        unsigned long utime, stime;
        long cutime, cstime, priority, nice, num_threads, itrealvalue;
        unsigned long long starttime;
        unsigned long vsize;
        long rss;
        unsigned long rsslim, startcode, endcode, startstack, kstkeip, signal, blocked, sigcatch, wchan, nswap, cnswap;

        friend std::ostream& operator<<(std::ostream& os, proc::ProcessStatus const& ps) {
            return os << 
                "pid: "         << ps.pid         << "\n" << 
                "comm: "        << ps.comm        << "\n" << 
                "state: "       << ps.state       << "\n" << 
                "ppid: "        << ps.ppid        << "\n" << 
                "pgrp: "        << ps.pgrp        << "\n" << 
                "session: "     << ps.session     << "\n" << 
                "tty_nr: "      << ps.tty_nr      << "\n" << 
                "tpgid: "       << ps.tpgid       << "\n" << 
                "flags: "       << ps.flags       << "\n" << 
                "minflt: "      << ps.minflt      << "\n" << 
                "cminflt: "     << ps.cminflt     << "\n" << 
                "majflt: "      << ps.majflt      << "\n" << 
                "cmajflt: "     << ps.cmajflt     << "\n" << 
                "utime: "       << ps.utime       << "\n" << 
                "stime: "       << ps.stime       << "\n" << 
                "cutime: "      << ps.cutime      << "\n" << 
                "cstime: "      << ps.cstime      << "\n" << 
                "priority: "    << ps.priority    << "\n" << 
                "nice: "        << ps.nice        << "\n" << 
                "num_threads: " << ps.num_threads << "\n" << 
                "itrealvalue: " << ps.itrealvalue << "\n" << 
                "starttime: "   << ps.starttime   << "\n" << 
                "vsize: "       << ps.vsize       << "\n" << 
                "rss: "         << ps.rss         << "\n" << 
                "rsslim: "      << ps.rsslim      << "\n" << 
                "startcode: "   << ps.startcode   << "\n" << 
                "endcode: "     << ps.endcode     << "\n" << 
                "startstack: "  << ps.startstack  << "\n" << 
                "kstkeip: "     << ps.kstkeip     << "\n" << 
                "signal: "      << ps.signal      << "\n" << 
                "blocked: "     << ps.blocked     << "\n" << 
                "sigcatch: "    << ps.sigcatch    << "\n" << 
                "wchan: "       << ps.wchan       << "\n" << 
                "nswap: "       << ps.nswap       << "\n" << 
                "cnswap: "      << ps.cnswap      << "\n";
        }
    };

    // Returns the process statistics from /proc/[pid]/stat.
    // The return value is None if the process does not exist.
    inline Result<ProcessStatus> status(pid_t pid)
    {
        std::string path = "/proc/" + std::to_string(pid) + "/stat";

        std::ifstream file(path.c_str());

        if (!file.is_open()) {
#if 1
            return Error("Failed to open '" + path + "'");
#else // FIXME reenable
            // Need to check if file exists AFTER we open it to guarantee
            // process hasn't terminated (or if it has, we at least have a
            // file which the kernel _should_ respect until a close).
            if (!os::exists(path)) {
                return None();
            }
            return Error("Failed to open '" + path + "'");
#endif
        }

        std::string _; // For ignoring fields.

        // Parse all fields from stat.
        ProcessStatus ps;
        if (file >> _ >> ps.comm >> ps.state >> ps.ppid >> ps.pgrp >> ps.session >> ps.tty_nr
            >> ps.tpgid >> ps.flags >> ps.minflt >> ps.cminflt >> ps.majflt >> ps.cmajflt
            >> ps.utime >> ps.stime >> ps.cutime >> ps.cstime >> ps.priority >> ps.nice
            >> ps.num_threads >> ps.itrealvalue >> ps.starttime >> ps.vsize >> ps.rss
            >> ps.rsslim >> ps.startcode >> ps.endcode >> ps.startstack >> ps.kstkeip
            >> ps.signal >> ps.blocked >> ps.sigcatch >> ps.wchan >> ps.nswap >> ps.cnswap)
        {
            return ps;
        } else
        {
            return Error("Failed to read/parse '" + path + "'");
        }
    }


} // namespace proc {

int main()
{
    std::cout << proc::status(getpid());
}
