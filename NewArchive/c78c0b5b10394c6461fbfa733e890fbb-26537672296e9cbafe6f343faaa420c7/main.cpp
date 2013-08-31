
int is_running();
int something_impl(const char*);

#if OPTIMIZE_BRANCH
int something(const char * c)
{
    if (is_running())
    {
        return something_impl(c);
    }
    return -1;
}
#else
int something(const char * c)
{
    if (!is_running())
    {
        return -1;
    }
    
    return something_impl(c);
}
#endif


int main()
{
    return something(OPTIMIZE_BRANCH ? "branch optimized (?)" : "no branch optimize");
}
