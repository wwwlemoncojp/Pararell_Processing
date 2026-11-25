#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <stdlib.h>

#define Max 10000

double start, end;

float **a, **b, **c, **hc;

int main(){
    int i, j;

    a = (float **)malloc(Max * sizeof(float *));
    b = (float **)malloc(Max * sizeof(float *));
    hc = (float **)malloc(Max * sizeof(float *));

    for(i = 0; i < Max; i++){
        a[i] = (float *)malloc(sizeof(float) * Max);
        b[i] = (float *)malloc(sizeof(float) * Max);
        hc[i] = (float *)malloc(sizeof(float) * Max);
    }
    
    for(i = 0; i < Max; i++){
        for(j = 0; j < Max; j++){
            a[i][j] = i * j * 1.e0f;
            b[i][j] = i * j * 2.e0f;
        }
    }

    printf("a\n");
    
    #pragma omp parallel num_threads(12)
    {
        printf("%d", omp_get_num_threads());
        
        start = omp_get_wtime();
    
        #pragma omp for private(i)
    
        for(j = 0; j < Max; j++){
            for(i = 0; i < Max; i++){
                hc[i][j] = a[i][j] + b[i][j];
            }
        }

    }

    end = omp_get_wtime();

    printf("\nCal End\n");
    printf("\nProcessing Time : %.10lf [s]", (double)(end - start));

    free(a);
    free(b);
    free(hc);

    return 0;
}