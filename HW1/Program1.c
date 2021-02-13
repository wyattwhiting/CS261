/* CS261- HW1 - Program1.c*/
/* Name: Wyatt Whiting
 * Date: 20210106
 * Solution description: foo() dereferences a and b before incrementing and decrementing, respectively. 
 *                       Same is done for assigning value of c to return.
 *                       Other than that, it's very straightforward.
 */
 
#include <stdio.h>
#include <stdlib.h>

int foo(int* a, int* b, int c){
    /* Increment a */
    (*a)++;
    /* Decrement  b */
    (*b)--;
    /* Assign a-b to c */
    c = (*a) - (*b);
    /* Return c */
    return c;
}

int main(){
    /* Declare three integers x,y and z and initialize them randomly to values in [0,10] */
    srand(time(NULL));
    int x = rand() % 11;
    int y = rand() % 11;
    int z = rand() % 11;

    /* Print the values of x, y and z */
    printf("x = %d | y = %d | z = %d \n", x, y, z);
    
    /* Call foo() appropriately, passing x,y,z as parameters */
    int ret = foo(&x, &y, z);    

    /* Print the values of x, y and z */
    printf("x = %d | y = %d | z = %d \n", x, y, z);
    
    /* Print the value returned by foo */
    printf("foo returns %d \n" , ret);
 
    /* Is the return value different than the value of z?  Why? */
    /* Yes, it's different because the return value is the difference of (x + 1) and (y - 1),
    *   which does not depend on the value of z at all. The function foo() is only modifying a local
    *   copy of z, called z, which is then changed, so the return value is not always equal to z unless
    *   by coincidence
    */
    return 0;
}
    
    
