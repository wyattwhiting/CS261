/* CS261- HW1 - Program2.c*/
/* Name: Wyatt Whiting
 * Date: 20210106
 * Solution description: struct array is allocated, populated, and printed.
 *                       Some simple stats are calculated and printed as well. 
 *                       Memory is then de-allocated before program terminates. 
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

struct student{
	char initials[2];
	int score;
};

struct student* allocate(){
     /*Allocate memory for ten students*/
     struct student * arr = malloc(10 * sizeof(*arr));
     /*return the pointer*/
     return arr;
}

void generate(struct student* students){
     /*Generate random initials and scores for ten students.
	The two initial letters must be capital and must be between A and Z. 
	The scores must be between 0 and 100*/
     srand(time(NULL));
     int i;
     for(i = 0; i < 10; ++i)
     {    
          /* set initials to random ascii values in capitals range */
          students[i].initials[0] = (rand() % 26) + 65;
          students[i].initials[1] = (rand() % 26) + 65;

          /* score set to random integer in [0, 100] */
          students[i].score = rand() % 101;
     }
     
}

void output(struct student* students){
     /*Output information about the ten students in the format:
              1. Initials  Score
              2. Initials  Score
              ...
              10. Initials Score*/
     int i;
     for(i = 0; i < 10; ++i)
     {
          printf("%c%c  %d \n", students[i].initials[0], students[i].initials[1], students[i].score);
     }
}

void summary(struct student* students){
     /*Compute and print the minimum, maximum and average scores of the ten students*/
     int i;
     int min = students[0].score;
     int max = students[0].score;
     int sum = 0;
     for(i = 0; i < 10; ++i)
     {
          int score = students[i].score; /* save on syntax */
          if(score > max) max = score; 
          if(score < min) min = score;
          sum += score; /* accumulate score */
     }
     printf("min:%d | max:%d | avg:%.1f \n", min, max, (float)(sum / 10.0));
     
}

void deallocate(struct student* stud){
     /*Deallocate memory from stud*/
     free(stud);
}

int main(){
    struct student* stud = NULL;
    
    /*call allocate*/
    stud = allocate();
    
    /*call generate*/
    generate(stud);

    /*call output*/
    output(stud);
    
    /*call summary*/
    summary(stud);
    
    /*call deallocate*/
    deallocate(stud);

    return 0;
}
