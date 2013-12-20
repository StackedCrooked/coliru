





#if BRANCH_PREDICT == 0

    void clean_code();


    int main(int argc, char**)
    {
        if (argc != 1)
        {
            // early return
            return 1;
        }
        
        clean_code();
    }

#elif BRANCH_PREDICT == 1

    void clever_code();
    
    int main(int argc, char**)
    {
        if (argc == 1)
        {
            clever_code();
            return 0;
        }
        else
        {
            return 1;
        }
    }
    
#endif

