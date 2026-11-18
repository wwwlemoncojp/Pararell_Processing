#include <stdio.h>
#include <omp.h>

void HelloWorld(){
    int i;
    #pragma omp parallel num_threads(4)
    {
        #pragma omp for
        for(i = 0; i < 48; i++){
            printf("Hello %d %d of %d\n", i, omp_get_thread_num(),omp_get_num_threads());

        }
    }
    
}

int main(){
    HelloWorld();
    
    return 0; 
}