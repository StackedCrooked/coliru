#include <malloc.h>
#include <stdio.h> // for size_t

// ----------------------------------------------------------------------------
// MemoryLeakInfo
// ----------------------------------------------------------------------------
typedef struct _MemoryLeakInfo
{
  void*  p;
  size_t size;
  char*  file;
  int    line;
} MemoryLeakInfo;

// ----------------------------------------------------------------------------
// MemoryLeak
// ----------------------------------------------------------------------------
class MemoryLeak
{
  friend void* debug_malloc(size_t size, const char* file, const int line);
  friend void  debug_free  (void* p,     const char* file, const int line);

protected:
  MemoryLeakInfo* m_info;
  bool            m_del_check;
  int             m_cnt;
  int             m_cur_max_cnt;

public:
  static const int MEMORY_LEAK_CNT = 65536;

public:
  MemoryLeak();
  virtual ~MemoryLeak();

protected:
  void _start(bool del_check, int cnt);
  int  _stop(bool auto_free);

protected:
  MemoryLeakInfo* find(void* p);
  MemoryLeakInfo* add (void* p, size_t size, char* file, int line);
  MemoryLeakInfo* del (void* p);

public:
  static void start(bool del_check = true, int cnt = MEMORY_LEAK_CNT);
  static int  stop(bool auto_free = true);
};


static MemoryLeak g_memoryLeak{};

// ----------------------------------------------------------------------------
// Overload functions
// ----------------------------------------------------------------------------
void* debug_malloc      (size_t size, const char* file, const int line);
void  debug_free        (void* p,     const char* file, const int line);
void* operator new      (size_t size, const char* file, const int line);
void  operator delete   (void* p,     const char* file, const int line);
void  operator delete   (void* p) noexcept;
void* operator new[]    (size_t size, const char* file, const int line);
void  operator delete[] (void* p,     const char* file, const int line);
void  operator delete[] (void* p) noexcept;

// ----------------------------------------------------------------------------
// Overload functions
// ----------------------------------------------------------------------------
void* debug_malloc(size_t size, const char* file, const int line)
{
  void* p = ::malloc(size);
 
  MemoryLeakInfo* info = g_memoryLeak.find(p);
  if (info != NULL)
  {
    printf("already exist %p %s %d\n", p, file, line);
    ::free(p);
    return NULL;
  }
  info = g_memoryLeak.add(p, size, (char*)file, (int)line);
  if (info == NULL)
  {
    ::free(p);
    return NULL;
  }
  return p;
}

void debug_free(void* p, const char* file, const int line)
{
  MemoryLeakInfo* info = g_memoryLeak.del(p);
  if (g_memoryLeak.m_del_check && info == NULL)
  {
    printf("can not del %p %s:%d\n", p, file, line);
  }
  ::free(p);
}

void* operator new (size_t size, const char* file, const int line)
{
  void* p = debug_malloc(size, file, line);
  return p;
}

void operator delete (void* p, const char* file, const int line)
{
 
  operator delete(p);
  debug_free(p, file, line);
}

void operator delete (void* p) noexcept
{
 
  return debug_free(p, "unknown", 0);
}

void* operator new[] (size_t size, const char* file, const int line)
{
  void* p = debug_malloc(size, file, line);
  return p;
}

void operator delete[] (void* p, const char* file, const int line)
{
 
  //delete[] p;
  return debug_free(p, file, line);
}

void  operator delete[] (void* p) noexcept
{
  
  return debug_free(p, "unknown", 0);
}


// ----------------------------------------------------------------------------
// Macros
// ----------------------------------------------------------------------------
#define debug_new new(__FILE__, __LINE__)
#define new       debug_new
//#define malloc(A) debug_malloc((A), __FILE__, __LINE__)
//#define free(A)   debug_free((A), __FILE__, __LINE__)
#define delete(A) operator delete((A), __FILE__, __LINE__) // deprecated /// gilgil temp 2011.09.14


MemoryLeak::MemoryLeak()
{
  start(MEMORY_LEAK_CNT); // initialize memory
  m_del_check = false;
}

MemoryLeak::~MemoryLeak()
{
  stop(false);     // check last memory leak
  start(false, 0); // clear memory
}

void MemoryLeak::_start(bool del_check, int cnt)
{
  if (m_info != NULL)
  {
    ::free(m_info);
    m_info = NULL;
  }
  m_del_check = del_check;
  if (cnt != 0)
  {
    m_info = (MemoryLeakInfo*) ::malloc(sizeof(MemoryLeakInfo) * cnt);
    for (int i = 0; i < cnt; i++)
    {
      MemoryLeakInfo* info = &m_info[i];
      info->p    = NULL;
      info->size = 0;
      info->file = NULL;
      info->line = 0;
    }
  }
  m_cnt          = cnt;
  m_cur_max_cnt  = 0;
}

int MemoryLeak::_stop(bool auto_free)
{
  m_del_check = false;

  int res = 0;
  for (int i = 0; i < m_cur_max_cnt; i++)
  {
    MemoryLeakInfo* info = &m_info[i];
    if (info->p != NULL)
    {
      res++;
      if (auto_free)
      {
        ::free(info->p);
        info->p    = NULL;
        info->size = 0;
        info->file = NULL;
        info->line = 0;
      }
    }
  }
  return res;
}

MemoryLeakInfo* MemoryLeak::find(void* p)
{
  for (int i = 0; i < m_cur_max_cnt; i++)
  {
    MemoryLeakInfo* info = &m_info[i];
    if (info->p == p)
    {
      return info;
    }
  }
  return NULL;
}

MemoryLeakInfo* MemoryLeak::add(void* p, size_t size, char* file, int line)
{
  for (int i = 0; i < m_cnt; i++)
  {
    MemoryLeakInfo* info = &m_info[i];
    if (info->p == NULL)
    {
      info->p    = p;
      info->size = size;
      info->file = file;
      info->line = line;
      if (i + 1 > m_cur_max_cnt) m_cur_max_cnt = i + 1;
      return info;
    }
  }
  return NULL;
}

MemoryLeakInfo* MemoryLeak::del(void* p)
{
  for (int i = 0; i < m_cur_max_cnt; i++)
  {
    MemoryLeakInfo* info = &m_info[i];
    if (info->p == p)
    {
      info->p    = NULL;
      info->size = 0;
      info->file = NULL;
      info->line = 0;

      bool m_cur_max_cnt_move = true;
      MemoryLeakInfo* temp = info + 1;
      for (int j = i + 1; j < m_cur_max_cnt; j++)
      {
        if (temp->p != NULL)
        {
          m_cur_max_cnt_move = false;
          break;
        }
        temp++;
      }

      if (m_cur_max_cnt_move) m_cur_max_cnt = i + 1;

      return info;
    }
  }
  return NULL;
}

void MemoryLeak::start(bool del_check, int cnt)
{
  g_memoryLeak._start(del_check, cnt);
}

int MemoryLeak::stop(bool auto_free)
{
  return g_memoryLeak._stop(auto_free);
}


int main()
{
   MemoryLeak::start(false);
   auto n = new char();
   delete n;
   printf("leaked = %d\n", MemoryLeak::stop());
}
