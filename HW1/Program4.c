/* CS261- HW1 - Program4.c*/
/* Name: Wyatt Whiting
 * Date: 20210107
 * Solution description: takes user input and generates dynamic array of student structs from input.
 *                       It then displays, sorts by first then last initial, and prints again. 
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct student{
	char initials[2];
	int score;
};

void sort(struct student* students, int n){
    /*Sort n students based on their initials*/     
    int i, j;
    for(i = 0; i < n - 1; ++i)
    {
        for(j = 0; j < n - i - 1; ++j)
        {
            if(students[j].initials[0] > students[j + 1].initials[0] || (students[j].initials[0] == students[j + 1].initials[0] && students[j].initials[1] > students[j + 1].initials[1]))
            {
                struct student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
}

int main(){
    srand(time(NULL));

    /*Declare an integer n and assign it a value.*/
    int n;
    printf("Enter n: ");
    scanf("%d", &n);
    /*Allocate memory for n students using malloc.*/
    struct student * arr = malloc(n * sizeof(*arr));
    
    /*Generate random IDs and scores for the n students, using rand().*/
    int i;
    for(i = 0; i < n; ++i)
    {
        arr[i].initials[0] = (rand() % 26) + 'A';
        arr[i].initials[1] = (rand() % 26) + 'A';
        arr[i].score = rand() % 101;
    }
    
    /*Print the contents of the array of n students.*/
    for(i = 0; i < n; ++i)
    {
        printf("%c %c %d \n", arr[i].initials[0], arr[i].initials[1], arr[i].score);
    }

    /*Pass this array along with n to the sort() function*/
    sort(arr, n);
    printf("Sorted: \n");

    /*Print the contents of the array of n students.*/
    for(i = 0; i < n; ++i)
    {
        printf("%c %c %d \n", arr[i].initials[0], arr[i].initials[1], arr[i].score);
    }

    free(arr);
    
    return 0;
}
