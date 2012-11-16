#include "MakeString.h"
#include <iomanip>
#include <iostream>
#include <string>
#include <cstdlib>
#include "syscalls.h"


using Futile::ss;


std::string gRole = "";

#define INFO(msg) std::cerr << __FILE__ << ":" << __LINE__ << ": i: " << __FUNCTION__ << ": " << gRole << ": " << std::string(msg) << std::endl
#define WARNING(msg) std::cerr << __FILE__ << ":" << __LINE__ << ": warning: " << __FUNCTION__ << ": "<< gRole << ": " << std::string(msg) << std::endl
#define ERROR(msg) std::cerr << __FILE__ << ":" << __LINE__ << ": error: " << __FUNCTION__ << ": "<< gRole << ": " << std::string(msg) << std::endl

#ifdef ENABLE_TRACE
#define TRACE(msg) std::cerr << __FILE__ << ":" << __LINE__ << ": " << __FUNCTION__ << ": "<< gRole << ": " << std::string(msg) << std::endl
#else
#define TRACE(msg)
#endif

#ifdef FOR_REAL
#define ABORT() std::abort();
#else
#define ABORT()
#endif


#define ASSERT_TRUE(cond) \
    if (!(cond)) { \
        ERROR(#cond); \
        ABORT(); \
    }


#define ASSERT_FALSE(cond) \
    if ((cond)) { \
        ERROR(#cond); \
        ABORT(); \
    }


#define ASSERT_LT(a, b) \
    if ((a) >= (b)) { \
        WARNING(Futile::MakeString() << "Assertion failed: \"" << #a << " < " << #b << "\" because " << a << (a > b ? " > " : " >= ") << b << "!"); \
        ABORT(); \
    }



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


void HandleSysWrite(const user_regs_struct & /*regs*/)
{
}

/**
 * Linux system call signatures:
 *   int open(const char *pathname, int flags);
 *   int open(const char *pathname, int flags, mode_t mode);
 *   int creat(const char *pathname, mode_t mode);
 */
void HandleSysOpen(const user_regs_struct & regs)
{
    std::stringstream ss;
    ss << "SYS_open: flags: " << std::hex << "0x" << std::setw(4) << std::setfill('0') << int(get_arg1(regs)) << std::dec << std::endl;
    TRACE(ss.str());
    ASSERT_TRUE(get_arg1(regs) == 0);
}


/**
 * Linux system call signatures:
 *   void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
 *   int munmap(void *addr, size_t length);
 */
void HandleSysMMap(const user_regs_struct & regs)
{
    uint64_t len = get_arg1(regs);
    ASSERT_LT(len, 10 * 1000 * 1000);

    static uint64_t sum = 0;
    sum += len;
    ASSERT_LT(sum, 256 * 1000 * 1000);
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
            HandleSysOpen(regs);
            break;
        }
        case SYS_fork:
        case SYS_execve:
        case SYS_socket:
        case SYS_sendto:
        {
            ERROR(Futile::MakeString() << "System call is not allowed: " << Translate(regs.orig_rax));
            ABORT();
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
        default:
        {
            ERROR(Futile::MakeString() << "System call is not allowed: " << Translate(regs.orig_rax));
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
        if (inside_syscall)
        {
            HandleSyscall(child);
        }
        ptrace(PTRACE_SYSCALL, child, NULL, NULL);
    }
}


void run(int argc, char ** argv)
{
    TRACE("Start parent application.");
    pid_t child = fork();

    if (child == 0)
    {
        gRole = "";
        TRACE("I am a child!");
        if (argc < 2)
        {
            throw std::runtime_error("Usage: ./sandbox Program");
        }

        TRACE("Trace me.");
        ptrace(PTRACE_TRACEME, 0, NULL, NULL);

        TRACE("execl " + std::string(argv[1]));
        execl(argv[1], argv[1], NULL);

        TRACE("Child exited gracefully.");
    }
    else
    {
        TRACE("I still the parent.");
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
