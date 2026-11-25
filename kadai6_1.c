#include <stdio.h>
#include <omp.h>

#define N 32

double start, end;


int main(){
    int i;
    double a[N], b[N], c[N], thread_num[N], num_threads[N];

    start = omp_get_wtime();

    #pragma omp parallel

    #pragma omp for
    for(i = 0; i < N; i++){
        a[i] = i * 1.e0f;
        b[i] = i * 2.e0f;
    }



    for(i = 0; i < N; i++){
        c[i] = a[i] + b[i];
        printf("c[] is : %lf @ %d %d of %d\n", c[i], i, thread_num[i], num_threads[i], omp_get_thread_num(), omp_get_num_threads());
    }

    end = omp_get_wtime();

    printf("\nCal End\n");
    printf("\nProcessing Time : %.4lf [s]", (double)(end - start));
    

    return 0;
}