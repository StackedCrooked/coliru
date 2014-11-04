
CStringA ConvertUTF16ToUTF8( __in LPCWSTR pszTextUTF16, size_t wlen = 0 ) {
    if (pszTextUTF16 == NULL) return "";

    int utf8len = WideCharToMultiByte(CP_UTF8, 0, pszTextUTF16, wlen, 
        NULL, 0, NULL, NULL );

    CStringA result;
    WideCharToMultiByte(CP_UTF8, 0, pszTextUTF16, wlen, 
        result.GetBuffer(utf8len), utf8len, 0, 0 );
    result.ReleaseBuffer();

    return result;
}