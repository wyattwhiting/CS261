/* ENTER YOUR FIRST AND LAST NAME: Wyatt Whiting     */

/* TO COMPILE:  gcc -Wall -ansi -o program Group1.c */

/* TO RUN, ENTER SIZE OF QUEUE */
/* FOR EXAMPLE:  ./program 30 */


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#define TYPE int
#define EQ(a,b) (a==b)

struct DLink {
   TYPE value;
   struct DLink * next;
   struct DLink * prev;
};

struct DList {
   int size;
   struct DLink * frontSentinel;
   struct DLink * backSentinel;
};

/*----------------------------------------------*/
/*Interface of a doubly linked list*/
void initDList (struct DList *dl);
void _printDList(struct DList *dl);
int _containsDList(struct DList* dl, TYPE e);
void addLink(struct DList* dl, TYPE e);

/*----------------------------------------------*/
/*Interface of Queue implemented as doubly linked list*/
void addSmartQueue (struct DList *q, TYPE val);



/*----------------------------------------------*/
int main(int argc, char **argv)
{
   /* Queue implemented as a doubly linked list */
   struct DList *q = (struct DList *) malloc(sizeof(struct DList));
   assert(q);

   int i;
   TYPE val;
   int  size = atoi(argv[1]); /* input argument is the size of Queue */

   assert(size >= 0);

   srand(time(NULL)); /*initialize random generator*/

   initDList(q); /*initialize Queue*/

   for(i=1; i<=size; i++)
   {
      val = (TYPE) rand() % 5;
      addSmartQueue(q, val); /*add val to Queue*/
   }
   printf("\nQueue:\n");
   _printDList(q); /*print Queue from Front to Back*/

   return 0;
}




/*============= IMPLEMENTATION OF QUEUE =============*/
/*----------------------------------------------*/
/*Add val to Queue only if val is not already in Queue */
/*input:
    q -- pointer to Queue implemented as doubly linked list
    val -- value to be added to Queue if possible
    Memory constraint: Except for a few local variables, no new memory can be allocated.
    Complexity constraint: no higher than O(n).
*/
void addSmartQueue (struct DList *q, TYPE val){
    assert(q);

    /* if it contains the member, just return and do nothing */
    if(_containsDList(q, val)) return;

    /* if here, need to add to end */
    /* call function to do that with 'val' */
    addLink(q, val);

    /* increment size */
    q->size++;

}

void addLink(struct DList* dl, TYPE e)
{
    /* pointers for last link and new to add */
    struct DLink * lastLink = dl->backSentinel->prev;
    struct DLink * newLink = (struct DLink *)malloc(sizeof(struct DLink));

    /* give newLink the proper value */
    newLink->value = e;

    /* update the four pointers are necessary */
    lastLink->next = newLink;
    newLink->prev = lastLink;
    newLink->next = dl->backSentinel;
    dl->backSentinel->prev = newLink;
}


/*==== IMPLEMENTATION OF DOUBLY LINKED LIST ====*/
/*----------------------------------------------*/
/*Initialize doubly linked list*/
void initDList (struct DList *dl) {
   dl->frontSentinel = (struct DLink *) malloc(sizeof(struct DLink));
   assert(dl->frontSentinel != 0);
   dl->backSentinel = (struct DLink *) malloc(sizeof(struct DLink));
   assert(dl->backSentinel);
   dl->frontSentinel->next = dl->backSentinel;
   dl->backSentinel->prev = dl->frontSentinel;
   dl->size = 0;
}
/*----------------------------------------------*/
/*Print elements of doubly linked list from front to back */
void _printDList(struct DList *dl){ 
   assert(dl);
   printf("\nFRONT: ");
   struct DLink *current = dl->frontSentinel->next;
   while (current != dl->backSentinel){
      printf("%d ", current->value);
      current = current->next;
   }
   printf(" :END\n");
}

int _containsDList(struct DList* dl, TYPE e)
{
    /* loop through all links to see if 'e' is in there */
    struct DLink * curr = dl->frontSentinel->next;
    if(dl->size == 0) return 0;
    while(curr != dl->backSentinel)
    {
        /* if equal value is found, return 1 to indicate presence */
        if(EQ(e, curr->value)) return 1;
        curr = curr->next;
    }

    /* if it makes it here, it's not present */
    return 0;
}