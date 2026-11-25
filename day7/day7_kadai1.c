#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <stdlib.h>

#define Max 100000000

double start, end;

float a[Max], b[Max], c[Max];

int main(){
    int i;

    #pragma omp parallel num_threads(10)
    {

        for(i = 0; i < Max; i++){
            a[i] = i * 1.e0f;
            b[i] = i * 2.e0f;
        }

        printf("%d", omp_get_num_threads());

        start = omp_get_wtime();

        #pragma omp for


        for(i = 0; i < Max; i++){
            c[i] = a[i] + b[i];
        }

    }

    end = omp_get_wtime();

    printf("\nCal End\n");
    printf("\nProcessing Time : %.10lf [s]", (double)(end - start));
    

    return 0;
}