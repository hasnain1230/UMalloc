#include <stdio.h>
#include "../../src/mymalloc.h"

//test will get size of identity matrix from user and make identity matrix

int main(){

    //get input on size of identity matrix from user
    printf("Enter size of matrix: ");
    int size;
    scanf("%d", &size);

    //allocate mem for indentity matrix
    int **identityMatrix = (int**)malloc(size*size*sizeof(int*));
    for(int i = 0; i<size; i++){
        identityMatrix[i]= (int*)malloc(size*sizeof(int));
    }

    //fill in 2d array with inputs to make identity matrix
    for(int i = 0; i<size; i++){
        for (int j = 0; j<size; j++){
            if(i==j){
                identityMatrix[i][j]=1;
            }else{
                identityMatrix[i][j]=0;
            }
        }
    }

    //traverse 2d array to print out identity matrix
    for(int i = 0; i<size; i++){
        for (int j = 0; j<size; j++){
            if (j != 0){
                printf(" ");
            }
            printf("%d",identityMatrix[i][j]);
        }
        printf("\n");
    }

    //free identity matrix
    for(int i = 0; i<size; i++){
        free(identityMatrix[i]);
    }
    free(identityMatrix);

    /*expected output will look like 
    Enter size of matrix: #
    1 0 ... 0
    .       .
    .       .
    .       .
    0 0 ... 1

    e.g. if user inputs 5 as the size of identity matrix output will look like
    Enter size of matrix: 5
    1 0 0 0 0
    0 1 0 0 0
    0 0 1 0 0
    0 0 0 1 0
    0 0 0 0 1
    */

    return 0;
}
