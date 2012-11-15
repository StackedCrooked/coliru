#include <string>
#include "syscalls.h"


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



void HandleSyscall(pid_t child)
{
    auto regs = GetRegisters(child);
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
    int inside_syscall = 0;
    while (1)
    {
        pid_t status;
        wait(&status);
        if (WIFEXITED(status))
        {
            break;
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

        if (inside_syscall == 0)
        {
            inside_syscall = 1;
            HandleSyscall(child);
        }
        else
        {
            inside_syscall = 0;
        }
        ptrace(PTRACE_SYSCALL, child, NULL, NULL);
    }
}


int main(int, char ** argv)
{
    pid_t child = fork();

    if (child == 0)
    {
        ptrace(PTRACE_TRACEME, 0, NULL, NULL);
        execl(argv[1], argv[1], NULL);
    }
    else
    {
        RunParent(child);
    }
    return 0;
}
