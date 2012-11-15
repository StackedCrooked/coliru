#include <string>
#include "syscalls.h"


std::string gRole = "Parent";

#define ERROR(msg) std::cerr << __FILE__ << ":" << __LINE__ << ": error: " << gRole << ": " << msg << std::endl
#define TRACE(msg) std::cerr << __FILE__ << ":" << __LINE__ << ": " << gRole << ": " << msg << std::endl


std::string TranslateSyscall(long id)
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


void HandleSysWrite(const user_regs_struct &)
{
}


void HandleSysOpen(const user_regs_struct & regs)
{
    //int open(const char *pathname, int flags);
    //int open(const char *pathname, int flags, mode_t mode);
    //int creat(const char *pathname, mode_t mode);
    long long unsigned int flags = get_arg1(regs);
    if (flags != 0)
    {
        throw std::runtime_error("HandleSysOpen: flag not allowed: " + std::to_string(flags));
    }
}


std::string ToString(pid_t child)
{
    std::cerr << "child: " << child << std::endl;
    return std::to_string(static_cast<long long>(child));
}



void HandleSyscall(pid_t child)
{
    auto regs = GetRegisters(child);
    TRACE("Handle system call " + ToString(regs.orig_rax) + " (" +  TranslateSyscall(regs.orig_rax) + ")");
    switch (regs.orig_rax)
    {
        case SYS_write:
        {
            HandleSysWrite(regs);
            break;
        }
        case SYS_open:
        {
            HandleSysOpen(regs);
            break;
        }
        default:
        {
            throw std::runtime_error(std::string("Syscall not allowed: ") + linux_syscallnames_64[regs.orig_rax]);
        }
    }
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
        gRole = "Child";
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
        ERROR(exc.what());
    }
}
