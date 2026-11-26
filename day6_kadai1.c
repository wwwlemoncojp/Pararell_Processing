#include <stdio.h>
#include <omp.h>

#define N 32
int main(){
    int i;
    double a[N], b[N], c[N];

    for(i = 0; i < N; i++){
        a[i] = i * 1.e0f;
        b[i] = i * 2.e0f;
    }

    #pragma omp parallel
    {
        #pragma omp for

        for(i = 0; i < N; i++){
            c[i] = a[i] + b[i];
            printf("c[] = %f @ %d : %d @ %d\n", c[i], i, omp_get_thread_num(), omp_get_num_threads());
        }
    }

    return 0;
}