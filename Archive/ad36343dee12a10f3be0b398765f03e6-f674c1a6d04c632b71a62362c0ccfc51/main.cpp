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
    const int numloops = 5000;
    const int nums = 1000000;//atoi(argv[0]);
    int* myarray = new int[nums];
    for(int i = 0; i < nums; i++)
        myarray[i] = i+1;
    printf("Nums is: %d\n",nums);
        
    double average = 0;
    double nocheat = 0;
    clock_t begin_time = clock();
    for(int i=0; i<numloops; ++i) {
        average = avg(myarray, 0, nums - 1);
        nocheat += average;
    }
    clock_t end_time = clock();
    printf("Nocheat:%f, Answer: %f\n", nocheat, average);
    clock_t delta = end_time-begin_time;
    double seconds = double(delta)/CLOCKS_PER_SEC;
    double avgsec = seconds/numloops;
    printf("Ticks: %ld, Seconds: %f, Average: %f\n", delta, seconds, avgsec);
    return 0;
}    