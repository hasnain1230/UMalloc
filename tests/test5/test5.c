#include <stdio.h>
#include <stdlib.h>
#include "../../src/umalloc.h"

//same as test 1 but expect wrong pointer error because it's trying to free something that's not pointing to the address of the 0th part of what we malloced

int main(){

    printf("Enter number of items:");

    int n;
    scanf("%d", &n);

    printf("Number of elements: %d\n", n);

    int* array = malloc(n * sizeof(int) * 0);

    if (array == NULL) {
        printf("Something went wrong! Please see error message above.\n");
        exit(1);
    }

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

    return 0;

}