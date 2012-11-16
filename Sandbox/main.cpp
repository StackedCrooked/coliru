#define ENABLE_TRACE 0
#define FOR_REAL 0


#include "MakeString.h"
#include "syscalls.h"
#include <fcntl.h>
#include <iomanip>
#include <iostream>
#include <string>
#include <stdexcept>
#include <cassert>
#include <cstdlib>


using Futile::ss;


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



bool eq(long int a, int b) { return a == b; }


#define REQUIRE_EQ(call, a, b) \
    if (eq((a), (b))) { \
        INFO(Futile::MakeString() << #call << ": PERMIT"); \
    } else { \
        ERROR(Futile::MakeString() << #call ": DENY because " << #a << " != " << #b); \
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
            REQUIRE_EQ(SYS_open, get_arg1(regs), O_RDONLY);
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
        //TRACE(Futile::MakeString() << "<" << (inside_syscall ? "" : "/") << Translate(GetRegisters(child).orig_rax) << ">\n");
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
            throw std::runtime_error("Usage: ./sandbox Program");
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
