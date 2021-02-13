/* TO COMPILE, ENTER:  gcc -Wall -ansi -o program Group1.c */
/* name: WYATT WHITING */

/* TO RUN, ENTER PROGRAM ARGUMENTS: SIZE  */
/* FOR EXAMPLE:  ./program 10   */


#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<assert.h>

#define TYPE int
#define LT(a, b) (a<b)
#define GT(a, b) (a>b)
#define EQ(a, b) (a == b)

struct DynArr {
   TYPE * data;
   int size;
   int capacity;
};

/*----------------------------------------------*/
/*Interface for Sorted Bag*/
void initSortedBag(struct DynArr * bag, int capacity);
void addSortedBag(struct DynArr * bag, TYPE val);
void removeSortedBag(struct DynArr * bag, TYPE val);


/*----------------------------------------------*/
/*Auxiliary functions*/
void _increaseCapacity (struct DynArr * bag);
void _printBag(struct DynArr * bag);

/*----------------------------------------------*/
int main(int argc, char **argv){
   struct DynArr sorted;
   int i;
   int  capacity = 1;
   int  size = atoi(argv[1]);

   if(size < 0){
     printf("\nInvalid value for the size of Bag; size must be a positive integer.\n");
     return 0;
   }

   initSortedBag(&sorted, capacity);


   /*Generate integers in [0,100] and add them
     to the sorted bag in the ascending order*/
   srand ( time(NULL) );
   for(i=0; i<size; i++) addSortedBag(&sorted, rand()%101);

   printf("\nSorted bag after adding %d elements:\n", size);
   _printBag(&sorted);

   addSortedBag(&sorted, 200);

   printf("\nSorted bag after adding %d:\n", 200);
   _printBag(&sorted);

   addSortedBag(&sorted, -1);

   printf("\nSorted bag after adding %d:\n", -1);
   _printBag(&sorted);

   TYPE val = sorted.data[1];

   removeSortedBag(&sorted, val);

   printf("\nSorted bag after removing %d:\n", val);
   _printBag(&sorted);

   removeSortedBag(&sorted, 200);

   printf("\nSorted bag after removing %d:\n", 200);
   _printBag(&sorted);

   removeSortedBag(&sorted, -1);

   printf("\nSorted bag after removing %d:\n", -1);
   _printBag(&sorted);

   removeSortedBag(&sorted, 500);

   printf("\nSorted bag after attempting to remove %d:\n", 500);
   _printBag(&sorted);


   return 0;
}

/*----------------------------------------------*/
/* Initializes a sorted bag
  input arguments:
  bag -- pointer to a bag implemented as a dynamic array
  cap -- capacity of memory block allocated to dynamic array
*/
void initSortedBag(struct DynArr * bag, int cap) {
   assert (bag!=0 && cap>0);
   bag->data = (TYPE *) malloc(cap * sizeof(TYPE));
   bag->size = 0;
   bag->capacity = cap;

}


/*----------------------------------------------*/
/* Increases the memory capacity of a sorted bag */
/*  Input: bag -- pointer to a bag implemented as a dynamic array */
void _increaseCapacity (struct DynArr * bag) {
  assert (bag);
   TYPE * newArr = (TYPE *) malloc((bag->capacity * 2) * sizeof(TYPE));

    int i;
    for(i = 0; i < bag->size; i++)
    {
        /* copying old data to new array */
        newArr[i] = bag->data[i]; 
    }

    /* free old mem, assign new */
    free(bag->data);
    bag->data = newArr;
}

/*----------------------------------------------*/
/* Prints out all elements of a sorted bag */
/*  Input: bag -- pointer to a bag implemented as a dynamic array */
void _printBag(struct DynArr * bag) {
   assert (bag);
   int i;
   if(bag->size == 0) printf("Sorted dynamic array is empty!\n");
   for(i=0; i< bag->size; i++) printf("%d, ", bag->data[i]);
   printf("\n");
}

/*----------------------------------------------*/
/* Adds a new element to a bag sorted in the ascending order
  input arguments:
  bag -- pointer to a bag implemented as a dynamic array 
  val -- value of the data element to be added
  After returning from the function the bag must remain sorted
*/
void addSortedBag(struct DynArr * bag, TYPE val) {
   assert(bag);

    if(bag->size == bag->capacity) _increaseCapacity(bag);
    if(bag->size == 0)
    {
        bag->data[0] = val;
    }
    if(LT(bag->data[bag->size - 1], val))
    {
        bag->data[bag->size] = val;
    }

    TYPE* newArr = (TYPE*) malloc(bag->capacity * sizeof(TYPE));

    int i;
    for(i = 0; i < bag->size; i++)
    {
        if(LT(bag->data[i], val))
        {
            newArr[i] = bag->data[i];
        }
        if(EQ(bag->data[i], val)) newArr[i] = val;
        else
        {
            newArr[i + 1] = bag->data[i];
        }
        
    }

    bag->data = newArr;
    bag->size++;



}

/*----------------------------------------------*/
/* Removes a single element from a bag sorted in the ascending order
  input arguments:
  bag -- pointer to a bag implemented as a dynamic array
  val -- value of the data element to be removed
  After returning from the function the bag must remain sorted
*/
void removeSortedBag(struct DynArr * bag, TYPE val) {
   assert(bag);
   if(bag->data[bag->size - 1] == val) bag->size--;

    
    int i;
    int flag = 0;
    for(i = 0; i < bag->size - 1; i++)
    {
        if(EQ(bag->data[i], val) && !flag)
        {
            flag = 1;
        }
        if(flag)
        {
            /* shift data down */
            bag->data[i] = bag->data[i + 1];
        }
    }
    bag->size--;
}
