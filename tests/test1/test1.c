#include <stdio.h>
#include "../../src/mymalloc.h"

//test1 will get the number of elements from input and print out the elements of the array, which will be 1 to number of elements in array
//e.g. if there are 5 elements in the array, the elements in the array will be 1,2,3,4,5

int main(){
    
    printf("Enter number of items:"); //asks user for number of items in array

    int n;
    scanf("%d", &n); //scans number of items

    printf("Number of elements: %d\n", n); //prints out number of items
    
    int* array = (int*)malloc(n*sizeof(int)); //make dynamic array
    
    for (int i = 0; i<n; i++){ //fill array with items
        array[i]=i+1;
    }

    //traverse through array to print out items
    printf("Array: {");
    for (int i = 0; i<n; i++){
        
        if(i==n-1){
           printf("%d", array[i]);
        }else{
           printf("%d, ", array[i]);
        }
    }
    printf("}\n");
    
    //need to free stuff i malloc
    free(array);
    
    return 0;

    /*expected output would be 
    Enter number of items:#
    Number of elements: #
    Array: {1,...,#}
   
    e.g. if number of items entered is 4 the output would be 
    Enter number of items:4 
    Number of elements: 4 
    Array: {1, 2, 3, 4}
    */
    
}