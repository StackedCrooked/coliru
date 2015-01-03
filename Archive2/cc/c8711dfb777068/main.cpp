extern "C"
{
#include <unistd.h>
#include <getopt.h>
#include <sys/wait.h>
}

#include <string>
#include <csignal>
#include <cstring>
#include <cassert>
#include <iostream>

/**
 * @brief Context for forked/child processes
 */
struct fork_context
{
    /**< PID of the child */
    pid_t m_pid;
    /**< stdout file descriptor */
    int m_stdout;
    /**< stderr file descriptor */
    int m_stderr;
    /**< return status of the child */
    int & m_return;
    /**< For logging */
    std::string m_name;

    /**
     * @brief Constructor
     */
    explicit fork_context(std::string const & name, int _stdout, 
                 int _stderr, int &return_res) noexcept :
        m_stdout(_stdout),
        m_stderr(_stderr),
        m_return(return_res),
        m_name(name)
    {
        assert(m_stdout >= 0);
        assert(m_stderr >= 0);
    }

    /**
     * @brief Constructor
     * @todo handle ::fileno better 
     */
    explicit fork_context(std::string const & name, std::FILE * _stdout, 
                 std::FILE * _stderr, int &return_res) noexcept :
        fork_context(name, ::fileno(_stdout), ::fileno(_stderr), return_res)
    {
    }

    /**
     * @brief Does the fork and handles the child
     */
    void run()
    {
        m_pid = fork();
        switch(m_pid)
        {
        case -1: /* error */
            std::cerr << std::strerror(errno) << std::endl;
            break;
        case 0: /* child */
            {
                /* close stdin because we're lazy */
                ::close(STDIN_FILENO);

                /* close the childs stdout/stderr and bind to our member fds */
                if (::dup2(m_stdout, STDOUT_FILENO) != STDOUT_FILENO
                    || ::dup2(m_stderr, STDERR_FILENO) != STDERR_FILENO)
                {
                    std::abort();
                }
        
                /* invoke child function */
                child_function();
                
                break;
            }
        default: /* parent */
            std::cout << "Spawned: " << m_name << " with pid: " << m_pid << std::endl;
            break;
        };
    }

    /**
     * @brief Destructor
     * @detail Note: RAII 'joining' of the child process
     */
    ~fork_context()
    {
        ::waitpid(m_pid, &m_return, 0);
        std::cout << "Properly Closed " << m_name << " with exit: " << m_return << std::endl; 
    }

    /**
     * @brief Function to call upon entry in the child
     */
    virtual void child_function()
    {
    }
};


/**
 * @brief Fork context for execvp
 */
struct exec_context : fork_context
{
    /**< arguments for exec */
    const char ** m_args;

    exec_context(std::string const & name, const char ** args,
                 int _stdout, int _stderr, int & return_res) noexcept :
        fork_context(name, _stdout, _stderr, return_res),
        m_args(args)
    {
    }

    exec_context(std::string const & name, const char ** args,
                 std::FILE * _stdout, std::FILE * _stderr, int & return_res) noexcept :
        fork_context(name, ::fileno(_stdout), ::fileno(_stderr), return_res),
        m_args(args)
    {
    }

    void child_function() override
    {
        /* Run exec() in a new session */
        ::setsid();

        ::execvp(((char * const *)m_args)[0],
                 (char * const *)m_args);

        /* when execvp detects and error, e.g., cannot find file path,
         * it'll get here */
        m_return = errno;
        std::cerr << m_name << " Fork failed: " << std::strerror(errno) << std::endl;
        std::_Exit(EXIT_FAILURE);
    }
};



void onsigchld(int sig)
{
    int status;
    pid_t ret;

    std::cout << __func__ << std::endl;

    while((ret = ::waitpid(-1, &status, WNOHANG)) > 0)
        if (WIFEXITED(status) && status) {
            /* check various exit statuses */
        }
}


int main(int argc, char ** argv)
{
    int ret;

    static const char * ls_args[] = {"ls", "-ahl", "/tmp", (char *)NULL, };
    static const char * bad_args[] = {"zoobop", (char *)NULL, };

    //////// RUN 1
    /* output to parents stdout, stderr */
    exec_context e1("myexec1", ls_args, STDOUT_FILENO, STDERR_FILENO, ret);

    //////// RUN 2
    std::FILE * out = std::fopen("myexec.out", "w");
    std::FILE * err = std::fopen("myexec.err", "w");
    exec_context e2("myexec2", ls_args, out, err, ret); 
    
    //////// RUN 3
    exec_context e3("myexec3", bad_args, STDOUT_FILENO, STDERR_FILENO, ret);
    
    
    // register handler
    signal(SIGCHLD, onsigchld);

    
    e1.run();
    e2.run();
    e3.run();
}
