#include <boost/preprocessor/stringize.hpp>
#include <cassert>
#include <cstdlib>
#include <fcntl.h>
#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <sys/ptrace.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/user.h>
#include <sys/wait.h>
#include <unistd.h>


#define CHECK(cond, pid) if (!(cond)) { throw std::runtime_error(Translate(pid) + ": " + BOOST_PP_STRINGIZE(cond)); }
#define TRACE(msg) std::cerr << "TRACE: " << (msg) << std::endl;


std::string Translate(long id);

user_regs_struct GetRegisters(pid_t child);


struct Counters : std::map<long, long>
{

    ~Counters()
    {
        std::set<std::pair<long, long>, std::greater< std::pair<long, long> > > messages;
        for (auto & pair : *this)
        {
            messages.insert(std::make_pair(pair.second, pair.first));
        }

        for (auto & pair : messages)
        {
            std::cout << pair.first << "\t" << Translate(pair.second) << std::endl;
        }
    }
};


void HandleSyscall(pid_t child)
{
    auto regs = GetRegisters(child);

    std::cerr << Translate(regs.orig_rax) << std::endl;
    switch (regs.orig_rax)
    {
        case SYS_fork:
        {
            static int i = 0;
            std::cerr << "FORK " << i << std::endl;
            CHECK(++i <= 5, regs.orig_rax);
            break;
        }
        case SYS_creat:
        {
            static int i = 0;
            CHECK(++i <= 10, regs.orig_rax);
            break;
        }
        case SYS_execve:
        {
            static int i = 0;
            CHECK(++i <= 5, regs.orig_rax);
            break;
        }
        case SYS_socket:
        case SYS_sendto:
        {
            throw std::runtime_error("System call is not allowed: " + Translate(regs.orig_rax));
        }
        default:
        {
            break;
        }
    };

    static Counters fCounters;
    fCounters[regs.orig_rax]++;
}


void RunParent(pid_t child)
{
    while (true)
    {
        pid_t status;
        wait(&status);
        if (WIFEXITED(status))
        {
            std::cerr << "CHILD EXIT CODE: " << WEXITSTATUS(status) << std::endl;
            return;
        }

        static bool first_execve = true;
        if (first_execve)
        {
            auto regs = GetRegisters(child);
            assert(regs.orig_rax == SYS_execve);
            if (regs.orig_rax == SYS_execve)
            {
                ptrace(PTRACE_SYSCALL, child, NULL, NULL);
                first_execve = false;
                continue;
            }
        }

        static auto inside_syscall = false;
        inside_syscall = !inside_syscall;
        if (inside_syscall)
        {
            HandleSyscall(child);
        }
        ptrace(PTRACE_SYSCALL, child, NULL, NULL);
    }
}


void run(int argc, char ** argv)
{
    pid_t child = fork();

    if (child == 0)
    {
        if (argc < 2)
        {
            throw std::runtime_error("Usage:" + std::string(argv[0]) +  " Program\n");
        }

        ptrace(PTRACE_TRACEME, 0, NULL, NULL);
        execl(argv[1], argv[1], NULL);
    }
    else
    {
        RunParent(child);
        TRACE("Parent exited gracefully.");
    }
}


int main(int argc, char ** argv)
{
    try
    {
        run(argc, argv);
    }
    catch (const std::exception & exc)
    {
        std::cerr << exc.what();
    }
}


const char * linux_syscallnames_64[] =
{
    "read", "write", "open", "close", "stat", "fstat", "lstat", "poll",
    "lseek", "mmap", "mprotect", "munmap", "brk", "rt_sigaction",
    "rt_sigprocmask", "rt_sigreturn", "ioctl", "pread64", "pwrite64", "readv",
    "writev", "access", "pipe", "select", "sched_yield", "mremap", "msync",
    "mincore", "madvise", "shmget", "shmat", "shmctl", "dup", "dup2", "pause",
    "nanosleep", "getitimer", "alarm", "setitimer", "getpid", "sendfile",
    "socket", "connect", "accept", "sendto", "recvfrom", "sendmsg", "recvmsg",
    "shutdown", "bind", "listen", "getsockname", "getpeername", "socketpair",
    "setsockopt", "getsockopt", "clone", "fork", "vfork", "execve", "exit",
    "wait4", "kill", "uname", "semget", "semop", "semctl", "shmdt", "msgget",
    "msgsnd", "msgrcv", "msgctl", "fcntl", "flock", "fsync", "fdatasync",
    "truncate", "ftruncate", "getdents", "getcwd", "chdir", "fchdir", "rename",
    "mkdir", "rmdir", "creat", "link", "unlink", "symlink", "readlink",
    "chmod", "fchmod", "chown", "fchown", "lchown", "umask", "gettimeofday",
    "getrlimit", "getrusage", "sysinfo", "times", "ptrace", "getuid", "syslog",
    "getgid", "setuid", "setgid", "geteuid", "getegid", "setpgid", "getppid",
    "getpgrp", "setsid", "setreuid", "setregid", "getgroups", "setgroups",
    "setresuid", "getresuid", "setresgid", "getresgid", "getpgid", "setfsuid",
    "setfsgid", "getsid", "capget", "capset", "rt_sigpending",
    "rt_sigtimedwait", "rt_sigqueueinfo", "rt_sigsuspend", "sigaltstack",
    "utime", "mknod", "uselib", "personality", "ustat", "statfs", "fstatfs",
    "sysfs", "getpriority", "setpriority", "sched_setparam", "sched_getparam",
    "sched_setscheduler", "sched_getscheduler", "sched_get_priority_max",
    "sched_get_priority_min", "sched_rr_get_interval", "mlock", "munlock",
    "mlockall", "munlockall", "vhangup", "modify_ldt", "pivot_root", "_sysctl",
    "prctl", "arch_prctl", "adjtimex", "setrlimit", "chroot", "sync", "acct",
    "settimeofday", "mount", "umount2", "swapon", "swapoff", "reboot",
    "sethostname", "setdomainname", "iopl", "ioperm", "create_module",
    "init_module", "delete_module", "get_kernel_syms", "query_module",
    "quotactl", "nfsservctl", "getpmsg", "putpmsg", "afs_syscall", "tuxcall",
    "security", "gettid", "readahead", "setxattr", "lsetxattr", "fsetxattr",
    "getxattr", "lgetxattr", "fgetxattr", "listxattr", "llistxattr",
    "flistxattr", "removexattr", "lremovexattr", "fremovexattr", "tkill",
    "time", "futex", "sched_setaffinity", "sched_getaffinity",
    "set_thread_area", "io_setup", "io_destroy", "io_getevents", "io_submit",
    "io_cancel", "get_thread_area", "lookup_dcookie", "epoll_create",
    "epoll_ctl_old", "epoll_wait_old", "remap_file_pages", "getdents64",
    "set_tid_address", "restart_syscall", "semtimedop", "fadvise64",
    "timer_create", "timer_settime", "timer_gettime", "timer_getoverrun",
    "timer_delete", "clock_settime", "clock_gettime", "clock_getres",
    "clock_nanosleep", "exit_group", "epoll_wait", "epoll_ctl", "tgkill",
    "utimes", "vserver", "mbind", "set_mempolicy", "get_mempolicy", "mq_open",
    "mq_unlink", "mq_timedsend", "mq_timedreceive", "mq_notify",
    "mq_getsetattr", "kexec_load", "waitid", "add_key", "request_key",
    "keyctl", "ioprio_set", "ioprio_get", "inotify_init", "inotify_add_watch",
    "inotify_rm_watch", "migrate_pages", "openat", "mkdirat", "mknodat",
    "fchownat", "futimesat", "newfstatat", "unlinkat", "renameat", "linkat",
    "symlinkat", "readlinkat", "fchmodat", "faccessat", "pselect6", "ppoll",
    "unshare", "set_robust_list", "get_robust_list", "splice", "tee",
    "sync_file_range", "vmsplice", "move_pages", "utimensat", "ORE_getcpu",
    "epoll_pwait", "signalfd", "timerfd_create", "eventfd", "fallocate",
    "timerfd_settime", "timerfd_gettime", "paccept", "signalfd4", "eventfd2",
    "epoll_create1", "dup3", "pipe2", "inotify_init1",
    NULL
};


enum
{
    num_linux_syscallnames_64 = sizeof(linux_syscallnames_64) / sizeof(linux_syscallnames_64[0])
};


std::string Translate(long id)
{
    if (id >= num_linux_syscallnames_64)
    {
        return "EXCEED_" + std::to_string(id);
    }

    return linux_syscallnames_64[id];
}


user_regs_struct GetRegisters(pid_t child)
{
    user_regs_struct regs = user_regs_struct();
    auto result = ptrace(PTRACE_GETREGS, child, NULL, &regs);
    if (result != 0)
    {
        throw std::runtime_error("PTRACE_GETREGS failed");
    }
    return regs;
}
