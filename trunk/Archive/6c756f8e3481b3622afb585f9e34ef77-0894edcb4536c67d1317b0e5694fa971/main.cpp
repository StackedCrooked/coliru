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
        const pid_t pid;
        const std::string comm;
        const char state;
        const pid_t ppid;
        const pid_t pgrp;
        const pid_t session;
        const int tty_nr;
        const pid_t tpgid;
        const unsigned int flags;
        const unsigned long minflt;
        const unsigned long cminflt;
        const unsigned long majflt;
        const unsigned long cmajflt;
        const unsigned long utime;
        const unsigned long stime;
        const long cutime;
        const long cstime;
        const long priority;
        const long nice;
        const long num_threads;
        const long itrealvalue;
        const unsigned long long starttime;
        const unsigned long vsize;
        const long rss;
        const unsigned long rsslim;
        const unsigned long startcode;
        const unsigned long endcode;
        const unsigned long startstack;
        const unsigned long kstkeip;
        const unsigned long signal;
        const unsigned long blocked;
        const unsigned long sigcatch;
        const unsigned long wchan;
        const unsigned long nswap;
        const unsigned long cnswap;

        friend std::ostream& operator<<(std::ostream& os, const ProcessStatus& ps)
        {
            return os << 
                  "pid: "         << ps.pid         << ", " << 
                  "comm: "        << ps.comm        << ", " << 
                  "state: "       << ps.state       << ", " << 
                  "ppid: "        << ps.ppid        << ", " << 
                  "pgrp: "        << ps.pgrp        << ", " << 
                  "session: "     << ps.session     << ", " << 
                  "tty_nr: "      << ps.tty_nr      << ", " << 
                  "tpgid: "       << ps.tpgid       << ", " << 
                  "flags: "       << ps.flags       << ", " << 
                  "minflt: "      << ps.minflt      << ", " << 
                  "cminflt: "     << ps.cminflt     << ", " << 
                  "majflt: "      << ps.majflt      << ", " << 
                  "cmajflt: "     << ps.cmajflt     << ", " << 
                  "utime: "       << ps.utime       << ", " << 
                  "stime: "       << ps.stime       << ", " << 
                  "cutime: "      << ps.cutime      << ", " << 
                  "cstime: "      << ps.cstime      << ", " << 
                  "priority: "    << ps.priority    << ", " << 
                  "nice: "        << ps.nice        << ", " << 
                  "num_threads: " << ps.num_threads << ", " << 
                  "itrealvalue: " << ps.itrealvalue << ", " << 
                  "starttime: "   << ps.starttime   << ", " << 
                  "vsize: "       << ps.vsize       << ", " << 
                  "rss: "         << ps.rss         << ", " << 
                  "rsslim: "      << ps.rsslim      << ", " << 
                  "startcode: "   << ps.startcode   << ", " << 
                  "endcode: "     << ps.endcode     << ", " << 
                  "startstack: "  << ps.startstack  << ", " << 
                  "kstkeip: "     << ps.kstkeip     << ", " << 
                  "signal: "      << ps.signal      << ", " << 
                  "blocked: "     << ps.blocked     << ", " << 
                  "sigcatch: "    << ps.sigcatch    << ", " << 
                  "wchan: "       << ps.wchan       << ", " << 
                  "nswap: "       << ps.nswap       << ", " << 
                  "cnswap: "      << ps.cnswap;
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
            return None();
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

        std::string comm;
        char state;
        pid_t ppid;
        pid_t pgrp;
        pid_t session;
        int tty_nr;
        pid_t tpgid;
        unsigned int flags;
        unsigned long minflt;
        unsigned long cminflt;
        unsigned long majflt;
        unsigned long cmajflt;
        unsigned long utime;
        unsigned long stime;
        long cutime;
        long cstime;
        long priority;
        long nice;
        long num_threads;
        long itrealvalue;
        unsigned long long starttime;
        unsigned long vsize;
        long rss;
        unsigned long rsslim;
        unsigned long startcode;
        unsigned long endcode;
        unsigned long startstack;
        unsigned long kstkeip;
        unsigned long signal;
        unsigned long blocked;
        unsigned long sigcatch;
        unsigned long wchan;
        unsigned long nswap;
        unsigned long cnswap;

        // NOTE: The following are unused for now.
        // int exit_signal;
        // int processor;
        // unsigned int rt_priority;
        // unsigned int policy;
        // unsigned long long delayacct_blkio_ticks;
        // unsigned long guest_time;
        // unsigned int cguest_time;

        std::string _; // For ignoring fields.

        // Parse all fields from stat.
        file >> _ >> comm >> state >> ppid >> pgrp >> session >> tty_nr
            >> tpgid >> flags >> minflt >> cminflt >> majflt >> cmajflt
            >> utime >> stime >> cutime >> cstime >> priority >> nice
            >> num_threads >> itrealvalue >> starttime >> vsize >> rss
            >> rsslim >> startcode >> endcode >> startstack >> kstkeip
            >> signal >> blocked >> sigcatch >> wchan >> nswap >> cnswap;

        // Check for any read/parse errors.
        if (file.fail() && !file.eof()) {
            file.close();
            return Error("Failed to read/parse '" + path + "'");
        }

        file.close();

        return ProcessStatus{ pid, std::move(comm), state, ppid, pgrp, session, tty_nr,
                tpgid, flags, minflt, cminflt, majflt, cmajflt,
                utime, stime, cutime, cstime, priority, nice,
                num_threads, itrealvalue, starttime, vsize, rss,
                rsslim, startcode, endcode, startstack, kstkeip,
                signal, blocked, sigcatch, wchan, nswap, cnswap };
    }


} // namespace proc {

int main()
{
    std::cout << proc::status(getpid());
}
