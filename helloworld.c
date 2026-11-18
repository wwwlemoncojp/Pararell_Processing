#include <stdio.h>

void HelloWorld(){
    int i;
    for(i = 0; i < 32; i++){
        printf("Hello %d\n", i);

    }
}

int main(){
    HelloWorld();
    return 0; 
}