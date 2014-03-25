#include <stdio.h>
#include <pthread.h>

typedef const char* sun_date_t;
typedef const char* sun_time_t;

typedef struct sun_t {
  int luminosity;

  /* private */
  sun_date_t date;
  sun_time_t time;
  sun_time_t sunrise;
  sun_time_t sunset;

  pthread_t tid;
  pthread_mutex_t mutex;
} sun_t;

void sun_parse_data (sun_t* this, FILE* f){}

int main()
{
}

