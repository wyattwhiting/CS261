/* ENTER YOUR FIRST AND LAST NAME:  Wyatt Whiting    */
/* TO COMPILE:  gcc -Wall -ansi -o program Group1.c */
/* TO RUN, ENTER YOUR INPUT FILE NAME:  ./program input1.txt  */


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#define TYPE int
#define EQ(a,b) (a==b)
# define TYPE int
struct Node {
  TYPE   val;
  struct Node *left;
  struct Node *right;
};
struct BST{
  struct Node *root;
  int size;
};

void addBST(struct BST *tree, TYPE val);
int heightBST(struct BST *tree);

/****************************************/
int main (int argc, const char * argv[]) {
   const char *filename;
   FILE *fileptr;
   struct BST *tree = (struct BST *) malloc(sizeof(struct BST));
   assert(tree);
   tree->root = 0;
   tree->size = 0;
   int value, height;

    if(argc == 2)
        filename = argv[1];
    else
        filename = "input.txt"; /* default file name */
    fileptr = fopen(filename,"r");

    printf("Adding nodes to BST with values from the file: %s\n", filename);
    while (!feof(fileptr)) {
      fscanf(fileptr, "%d", &value);
      addBST(tree, value);
    }

    height = heightBST(tree);
    printf("The tree height is %d\n",height);

    return 0;
}

struct Node * _addNode(struct Node * curr, TYPE val)
{
    if(curr == NULL) /* add a new node if needed */
    {
        struct Node * new = (struct Node *)malloc(sizeof(struct Node));
        assert(new != NULL);
        /* assign value and set pointers for new node */
        new->val = val;
        new->left = 0;
        new->right = 0;

        /* return pointer to new node */
        return new;
    }
    /* is value is less, add to left branch */
     if (val < curr->val)
        curr->left = _addNode(curr->left, val);
        
    /* otherwise, add to right branch */
    else
        curr->right = _addNode(curr->right, val);
    
    /* return pointer  */
    return curr;
}

/****************************************/
/* Add a new node to BST */
/*
    input: tree -- pointer to BST,
           val -- value to be added to BST
    pre-conditions: BST was initialized well
    constraint: complexity <= O(log n)
*/
void addBST(struct BST *tree, TYPE val) {
   assert(tree);

   /* FIX ME */
    /* call helper function to add val to tree as new node */
    tree->root = _addNode(tree->root, val);
    tree->size++;
}


int recursiveHeight(struct Node * curr)
{
    /* if node is null, it has height less than any other member */
    if(curr == NULL) return -1;

    /* recursive call to height function for both sides */
    int leftHeight = recursiveHeight(curr->left);
    int rightHeight = recursiveHeight(curr->right);

    /* if left height is greater, return that plus 1 */
    /* makes it so leaf nodes have height 0 */
    if (leftHeight > rightHeight) return (leftHeight + 1);
    
    /* otherwise, return the right height plus 1 */
    return (rightHeight + 1);

}


/****************************************/
/* Compute the height of BST */
/*
    input: tree -- pointer to BST
    output: the height of BST is returned
    pre-conditions: BST was initialized well
    requirement: If the tree is empty, return -1
    constraints: complexity <= O(n), no new memory allocation 
*/
int heightBST(struct BST *tree){
    assert(tree);

    /* FIX ME */
    /* check for tree being empty */
    if(tree->size == 0) return -1;

    /* otherwise, do a recursive call starting from the root node */
    return recursiveHeight(tree->root);

}
