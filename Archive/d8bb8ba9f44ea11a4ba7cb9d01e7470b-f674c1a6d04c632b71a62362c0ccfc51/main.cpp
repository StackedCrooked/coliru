#include <cstdio>
#include <ctime>

double avg (int arr[], int beg, int end) {
    int nums = end - beg + 1;
    double sum = 0.0;
    for(int i = beg; i <= end; i++)
        sum += arr[i];
    return sum/nums;
}

int main ()  { 
    int nums = 1000000;//atoi(argv[0]);
    int* myarray = new int[nums];
    for(int i = 0; i < nums; i++)
        myarray[i] = i+1;
    printf("Nums is: %d\n",nums);
        
    for(int i=0; i<50; ++i) {
        clock_t begin_time = clock();
        double average = avg(myarray, 0, nums - 1);
        clock_t end_time = clock();
        clock_t delta = end_time-begin_time;
        double seconds = double(delta)/CLOCKS_PER_SEC;
        printf("Answer: %f, Ticks: %ld, Seconds: Time: %f\n", average, delta, seconds);
    }
    return 0;
}    