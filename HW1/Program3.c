/* CS261- HW1 - Program3.c*/
/* Name: Wyatt Whiting
 * Date: 20210107
 * Solution description: creates a 20-tuple of integers, then prints,
 *                       sorts in ascending order, and prints again.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void sort(int* number, int n){
    /*Sort the array of integeres of length n*/ 
    int i, j;
    for(i = 0; i < n - 1; ++i)
    {
        for(j = 0; j < n - i - 1; ++j)
        {
            if(number[j] > number[j + 1])
            {
                int temp = number[j];
                number[j] = number[j + 1];
                number[j + 1] = temp;
            }
        }
    }
}

int main(){
    /*Declare an integer n and assign it a value of 20.*/
    int n = 20;
    /*Allocate memory for an array of n integers using malloc.*/
    int * arr = malloc(n * sizeof(int));
    /*Fill this array with random numbers, using rand().*/
    srand(time(NULL));
    int i;
    for(i = 0; i < n; ++i)
    {
        arr[i] = rand();
    }
    /*Print the contents of the array.*/
    for(i = 0; i < n; ++i)
    {
        printf("%d \n", arr[i]);
    }

    /*Pass this array along with n to the sort() function of part a.*/
    sort(arr, n);

    /*Print the contents of the array.*/    
    printf("Sorted Array: \n"); 
    
    for(i = 0; i < n; ++i)
    {
        printf("%d \n", arr[i]);
    }

    free(arr);

    return 0;
}
