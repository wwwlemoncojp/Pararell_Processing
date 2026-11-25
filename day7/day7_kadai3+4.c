#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

#define Max 10000

int main() {
    int i, j;
    double start, end;

    float **a  = (float **)malloc(Max * sizeof(float *));
    float **b  = (float **)malloc(Max * sizeof(float *));
    float **hc = (float **)malloc(Max * sizeof(float *));

    for (i = 0; i < Max; i++) {
        a[i]  = (float *)malloc(sizeof(float) * Max); // sizeof(float) に修正（合計約1.2GB）
        b[i]  = (float *)malloc(sizeof(float) * Max);
        hc[i] = (float *)malloc(sizeof(float) * Max);
    }

    // 事前初期化（hcもここで物理メモリ割り当てを完了させる）
    for (i = 0; i < Max; i++) {
        for (j = 0; j < Max; j++) {
            a[i][j]  = i * j * 1.0f;
            b[i][j]  = i * j * 2.0f;
            hc[i][j] = 0.0f;
        }
    }

    // 1. 外側 i, 内側 j（行優先）
    #pragma omp parallel num_threads(1)
    {
        #pragma omp single
        start = omp_get_wtime();

        #pragma omp for private(j)
        for (i = 0; i < Max; i++) {
            for (j = 0; j < Max; j++) {
                hc[i][j] = a[i][j] + b[i][j];
            }
        }

        #pragma omp single
        end = omp_get_wtime();
    }
    printf("Outer i, Inner j : %.6lf [s]\n", end - start);

    // 2. 外側 j, 内側 i（列優先）
    #pragma omp parallel num_threads(1)
    {
        #pragma omp single
        start = omp_get_wtime();

        #pragma omp for private(i)
        for (j = 0; j < Max; j++) {
            for (i = 0; i < Max; i++) {
                hc[i][j] = a[i][j] + b[i][j];
            }
        }

        #pragma omp single
        end = omp_get_wtime();
    }
    printf("Outer j, Inner i : %.6lf [s]\n", end - start);

    // 最適化による計算省略を防ぐためのダミー参照
    printf("Check: %f\n", hc[Max - 1][Max - 1]);

    for (i = 0; i < Max; i++) {
        free(a[i]);
        free(b[i]);
        free(hc[i]);
    }
    free(a);
    free(b);
    free(hc);

    return 0;
}