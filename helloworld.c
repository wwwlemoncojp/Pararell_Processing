#include <stdio.h>
#include <omp.h>

void HelloWorld(){
    int i;
    #pragma omp parallel /* num_threads() */
    {
        #pragma omp for
        for(i = 0; i < 48; i++){
            printf("Hello %d\n", i);

        }
    }
    
}

int main(){
    HelloWorld();
    return 0; 
}