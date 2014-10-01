#include <stdio.h>      /* puts, printf */
#include <time.h>       /* time_t, struct tm, time, localtime */
#include <iostream>

int main ()
{   
    #define globcnt 10000
            int array[globcnt];
            for (int i = 0; i < globcnt; i++)
            {
                array[i] = globcnt - i;
            }
            time_t begin = time(NULL);
            for (int cnt = 0; cnt < globcnt; cnt++)
            {
                for (int i = 1; i < globcnt; i++)
                {
                    for (int j = 0 ; j < globcnt; j++)
                    {
                        if (array[i] < array[i - 1])
                        {
                            int tmp = array[i - 1];
                            array[i - 1] = array[i];
                            array[i] = tmp;
                        }
                    }
                }
            }
            std::cerr << time(NULL) - begin << std::endl;
  return 0;
}