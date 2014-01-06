void copyfunction(const char* const data) 
{
    (void)data;
}

int main()
{
    char sourcebuffer[] = {0x00};

    copyfunction(sourcebuffer);
}
