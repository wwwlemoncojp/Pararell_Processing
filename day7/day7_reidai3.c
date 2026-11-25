#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <stdlib.h>

#define Max 1000

double start, end;

float a[Max][Max], b[Max][Max], c[Max][Max];

int main(){
    int i, j;

    start = omp_get_wtime();

    for(i = 0; i < Max; i++){
        for(j = 0; j < Max; j++){
            a[i][j] = i * j * 1.e0f;
            b[i][j] = i * j * 2.e0f;
        }
        
    }

    #pragma omp parallel num_threads(4)

    printf("%d", omp_get_num_threads());

    #pragma omp for private(i)


    for(i = 0; i < Max; i++){
        for(j = 0; j < Max; j++){
            c[i][j] = a[i][j] + b[i][j];
        }
    }

    end = omp_get_wtime();

    printf("\nCal End\n");
    printf("\nProcessing Time : %.10lf [s]", (double)(end - start));
    

    return 0;
}