#include <cassert>
#include <cstdlib>
#include <fcntl.h>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <sys/ptrace.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/user.h>
#include <sys/wait.h>
#include <unistd.h>


#define ENABLE_TRACE 0
#define FOR_REAL     1


extern const char * linux_syscallnames_64[];


long get_arg0(const user_regs_struct & regs) { return regs.rdi; }
long get_arg1(const user_regs_struct & regs) { return regs.rsi; }
long get_arg2(const user_regs_struct & regs) { return regs.rdx; }
long get_arg3(const user_regs_struct & regs) { return regs.rcx; }
long get_arg4(const user_regs_struct & regs) { return regs.r8;  }
long get_arg5(const user_regs_struct & regs) { return regs.r9;  }



#define INFO(msg) std::cerr << __FILE__ << ":" << __LINE__ << ": info: " << std::string(msg) << std::endl
#define WARNING(msg) std::cerr << __FILE__ << ":" << __LINE__ << ": warning: " << std::string(msg) << std::endl
#define ERROR(msg) std::cerr << __FILE__ << ":" << __LINE__ << ": error: " << std::string(msg) << std::endl

#define DENY(msg) std::cerr << __FILE__ << ":" << __LINE__ << ": DENY: " << std::string(msg) << std::endl
#define PERMIT(msg) std::cerr << __FILE__ << ":" << __LINE__ << ": PERMIT: " << std::string(msg) << std::endl

#if ENABLE_TRACE
#define TRACE(msg) std::cerr << __FILE__ << ":" << __LINE__ << ": trace: " << std::string(msg) << std::endl
#else
#define TRACE(msg)
#endif

#if FOR_REAL
#define ABORT() std::abort();
#else
#define ABORT()
#endif


#define ASSERT_TRUE(cond) \
    if (!(cond)) { \
        DENY(#cond); \
        ABORT(); \
    } else { \
        PERMIT(#cond); \
    }


#define ASSERT_FALSE(cond) \
    if ((cond)) { \
        DENY(#cond); \
        ABORT(); \
    } else { \
        PERMIT(#cond); \
    }


#define ASSERT_LT(a, b) ASSERT_TRUE(a < b)


#define REQUIRE_EQ(call, a, b) \
    if (eq((a), (b))) { \
        INFO(MakeString() << #call << ": PERMIT"); \
    } else { \
        ERROR(MakeString() << #call ": DENY because " << #a << " != " << #b); \
    }


bool eq(long int a, int b) { return a == b; }


class MakeString
{
public:
    template <typename T>
    MakeString & operator<<(const T & datum)
    {
        mBuffer << datum;
        return *this;
    }

    operator std::string() const
    { return mBuffer.str(); }

    std::string str() const
    { return mBuffer.str(); }

private:
    std::stringstream mBuffer;
};



std::string Translate(long id)
{
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


std::string ToString(pid_t child)
{
    std::cerr << "child: " << child << std::endl;
    return std::to_string(static_cast<long long>(child));
}


void HandleSyscall(pid_t child)
{
    auto regs = GetRegisters(child);
    switch (regs.orig_rax)
    {
        case SYS_open:
        {
            if (get_arg1(regs) != O_RDONLY)
            {
                std::cerr << "Writing to the file system is not allowed." << std::endl;
                std::abort();
            }
            break;
        }
        case SYS_access:
        case SYS_arch_prctl:
        case SYS_brk:
        case SYS_close:
        case SYS_exit:
        case SYS_exit_group:
        case SYS_fstat:
        case SYS_futex:
        case SYS_getrlimit:
        case SYS_gettid:
        case SYS_gettimeofday:
        case SYS_madvise:
        case SYS_mmap:
        case SYS_mprotect:
        case SYS_munmap:
        case SYS_nanosleep:
        case SYS_read:
        case SYS_rt_sigaction:
        case SYS_rt_sigprocmask:
        case SYS_set_robust_list:
        case SYS_set_tid_address:
        case SYS_tgkill:
        case SYS_time:
        case SYS_write:
        case SYS_writev:
        {
            break;
        }
        case SYS_fork:
        case SYS_execve:
        case SYS_socket:
        case SYS_sendto:
        default:
        {
            ERROR(MakeString() << "System call is not allowed: " << Translate(regs.orig_rax));
            ABORT();
            break;
        }
    };
}


void RunParent(pid_t child)
{
    while (true)
    {
        pid_t status;
        wait(&status);
        if (WIFEXITED(status))
        {
            TRACE("Child has existed with status: " + std::to_string(static_cast<long long>(status)));
            return;
        }

        static bool first_execve = true;
        if (first_execve)
        {
            TRACE("Allowing first execve call.");
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
        //TRACE(MakeString() << "<" << (inside_syscall ? "" : "/") << Translate(GetRegisters(child).orig_rax) << ">\n");
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
            throw std::runtime_error("Usage: ./sandbox Program\n");
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
