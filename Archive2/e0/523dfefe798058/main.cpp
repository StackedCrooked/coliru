    #include <syslog.h>
    
    int main()
    {
        openlog("test-app", LOG_CONS | LOG_NDELAY | LOG_PERROR | LOG_PID, LOG_USER);
        setlogmask(LOG_UPTO(LOG_DEBUG));
        
        syslog(LOG_DEBUG, "Testing!");
    }