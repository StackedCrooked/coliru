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
    for(int i=0; i<50; ++i) {
        int nums = 1000000;//atoi(argv[0]);
        int* myarray = new int[nums];
        double timediff;
        printf("Nums is: %d\n",nums);
        clock_t begin_time = clock();
        for(int i = 0; i < nums; i++)
            myarray[i] = i+1;
        double average = avg(myarray, 0, nums - 1);
        printf("%f\n",average); 
        clock_t end_time = clock();
        timediff = (double) difftime(end_time, begin_time);
        printf("Time to Average: %f\n", timediff);
    }
    return 0;
}    