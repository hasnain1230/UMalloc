#include <stdio.h>
#include "../../src/mymalloc.h"

//same as test 1 but expect double free error because free array twice at bottom

int main(){
    
    printf("Enter number of items:"); 

    int n;
    scanf("%d", &n); 

    printf("Number of elements: %d\n", n);
    
    int* array = (int*)malloc(n*sizeof(int)); 
    
    for (int i = 0; i<n; i++){
        array[i]=i+1;
    }

    printf("Array: {");
    for (int i = 0; i<n; i++){
        
        if(i==n-1){
           printf("%d", array[i]);
        }else{
           printf("%d, ", array[i]);
        }
    }
    printf("}\n");
    
    free(array);
	free(array);
    
    return 0;

}