#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <stdlib.h>

#define Max 100000000

double start, end;

float **a, **b, **c, **hc;

int main(){
    int i, j, n = 1024;

    a = (float **)malloc(n * sizeof(float *));
    b = (float **)malloc(n * sizeof(float *));
    hc = (float **)malloc(n * sizeof(float *));

    for(i = 0; i < n; i++){
        a[i] = (float *)malloc(sizeof(float *) * n);
        b[i] = (float *)malloc(sizeof(float *) * n);
        hc[i] = (float *)malloc(sizeof(float *) * n);
    }
    
    for(i = 0; i < Max; i++){
        for(j = 0; j < Max; j++){
            a[i][j] = (float)(rand() / 4096);
            b[i][j] = (float)(rand() / 4096);
        }
    }
    
    #pragma omp parallel
    
    start = omp_get_wtime();

    #pragma omp for

    for(i = 0; i < Max; i++){
        c[i] = a[i] + b[i];
    }

    end = omp_get_wtime();

    printf("\nCal End\n");
    printf("\nProcessing Time : %.10lf [s]", (double)(end - start));

    free(a);
    free(b);
    free(c);
    

    return 0;
}