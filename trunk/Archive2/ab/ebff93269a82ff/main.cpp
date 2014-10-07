    pid_t fork() {
        pid_t ChildPid = OperatingSystemCloneProcess();
        pid_t MyPid = GetPid();
        if (MyPid == ChildPid) //is the child
            return 0;
        else //is the parent
            return ChildPid;
    }