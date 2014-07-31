
int main()

// These values dont really matter, just stopping an uninitialized variable warning.
unsigned char *m_start = static_cast<unsigned char*>(0x243);
unsigned char *m_end = static_cast<unsigned char*>(0x24F);
size_t pos = 10;
if (m_start + pos >= m_end) // This gives the error
{

}

}