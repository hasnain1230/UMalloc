#include <stdio.h>
#include <stdlib.h>
#include "../../src/umalloc.h"

//same as test 1 but expect seg fault error because trying to access something you already freed

int main(){
    
    printf("Enter number of items:"); 

    int n;
    scanf("%d", &n); 

    printf("Number of elements: %d\n", n);
    
    int* array = (int*)malloc(n*sizeof(int));

    if (array == NULL) {
        perror("Malloc Returned NULL");
        exit(1);
    }
    
    for (int i = 0; i<n; i++){
        array[i]=i+1;
    }

    free(array + 1);

    printf("Array: {");
    for (int i = 0; i<n; i++){
        
        if(i==n-1){
           printf("%d", array[i]);
        }else{
           printf("%d, ", array[i]);
        }
    }
    printf("}\n");
    
    return 0;

}