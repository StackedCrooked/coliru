#define DECL_ROUTE(name, ret, args) \
  ret CLibProxy::name args \
  { \
    if (m_hDLL) \
      return m_f##name (args); \
    return ret(); \
  }

DECL_ROUTE(AttachCWnd, int, (CWnd* pControl));