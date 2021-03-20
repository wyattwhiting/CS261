#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/time.h>
#include "avl.h"


int FindMinPath(struct AVLTree *tree, TYPE *path);
void printBreadthFirstTree(struct AVLTree *tree);

/* extra prototype */
void _printAtDepth(struct AVLnode *node, int dep);
void _recurseSearch(struct AVLnode *node, int pathCost, int parVal, int *mpl, int *mpc);


/* -----------------------
The main function
  param: argv = pointer to the name (and path) of a file that the program reads for adding elements to the AVL tree
*/
int main(int argc, char** argv) {

	FILE *file;
	int len, i;
	TYPE num; /* value to add to the tree from a file */
	struct timeval stop, start; /* variables for measuring execution time */
	int pathArray[100];  /* static array with values of nodes along the min-cost path of the AVL tree. The means that the depth of the AVL tree cannot be greater than 100 which is  sufficient for our purposes*/

	struct AVLTree *tree;
	
	tree = newAVLTree(); /*initialize and return an empty tree */
	
	file = fopen(argv[1], "r"); 	/* filename is passed in argv[1] */
	assert(file != 0);

	/* Read input file and add numbers to the AVL tree */
	while((fscanf(file, "%i", &num)) != EOF){
		addAVLTree(tree, num);		
	}
	/* Close the file  */
	fclose(file);

        printf("\nThe AVL tree has %d nodes.\n",tree->cnt);
	
	printf("\nPrinting the AVL tree breadth-first : \n");
	printBreadthFirstTree(tree);

	gettimeofday(&start, NULL);

	/* Find the minimum-cost path in the AVL tree*/
	len = FindMinPath(tree, pathArray);
	
	gettimeofday(&stop, NULL);

	/* Print out all numbers on the minimum-cost path */
	printf("\n\nThe minimum-cost path has %d nodes printed top-down from the root to the leaf: \n", len);
	for(i = 0; i < len; i++)
		printf("%d ", pathArray[i]);
	printf("\n");

	printf("\nYour execution time to find the mincost path is %f microseconds\n", (double) (stop.tv_usec - start.tv_usec));

        /* Free memory allocated to the tree */
	deleteAVLTree(tree); 
	
	return 0;
}


  
/* --------------------
Finds the minimum-cost path in an AVL tree
   Input arguments: 
        tree = pointer to the tree,
        path = pointer to array that stores values of nodes along the min-cost path, 
   Output: return the min-cost path length 

   pre: assume that
       path is already allocated sufficient memory space 
       tree exists and is not NULL
*/
int FindMinPath(struct AVLTree *tree, TYPE *path)
{
    /* FIX ME */
    /* val of leaf doesn't matter, but set minPathCost to maximum int val */
    struct AVLnode * curr;
    int count;
    int minPathLeaf = 0;
    int minPathCost = 2147483647;

    /* start up recursive search */
    /* skip the root node since it has no parent */
    _recurseSearch(tree->root->left, 0, tree->root->val, &minPathLeaf, &minPathCost);
    _recurseSearch(tree->root->right, 0, tree->root->val, &minPathLeaf, &minPathCost);

    /* info for debugging
    printf("\n%d\n", minPathCost);
    printf("\n%d\n", minPathLeaf);
    */

    /* simple binary search to generate path from known leaf 
    with lowest associated path cost */
    curr = tree->root;
    count = 0;
    while(curr != NULL)
    {
        path[count] = curr->val;
        if(LT(minPathLeaf, curr->val))
            curr = curr->left;
        else    
            curr = curr->right;
        count++;
    }
    return count;
}

/* recusively search tree to find minimum path cost along with leaf associated */
void _recurseSearch(struct AVLnode *node, int pathCost, int parVal, int *mpl, int *mpc)
{
    /* update path cost for that node */
    pathCost += abs(parVal - node->val);

    /* if path is more expensive than shortest so far, don't bother */
    if(pathCost >= *mpc) return;

    /* if node is a leaf, update global minimums if necessary */
    if(node->height == 0)
    {
        if(pathCost < (*mpc))
        {
            *mpc = pathCost;
            *mpl = node->val;
        }
    }
    
    /* reduce for each side */
    if(node->left)  _recurseSearch(node->left,  pathCost, node->val, mpl, mpc);
    if(node->right) _recurseSearch(node->right, pathCost, node->val, mpl, mpc);
}

/* -----------------------
Printing the contents of an AVL tree in breadth-first fashion
  param: pointer to a tree
  pre: assume that tree was initialized well before calling this function
*/
void printBreadthFirstTree(struct AVLTree *tree)
{
	/* FIX ME */
	/* variable for height and iterator */
	int totalHeight;
	int i;

	/* make sure the tree is initialized and get it's height */
	assert(tree);
    totalHeight = tree->root->height;


	/* iterate through each level of tree and print only values at that level*/
	for(i = 1; i <= totalHeight + 1; i++)
		_printAtDepth(tree->root, i);

}

void _printAtDepth(struct AVLnode *node, int dep) 
{
    if(node == NULL) return;

	/* terminating condition */
	if(dep == 1)
	{
		printf("%d ", node->val);
	}

	/* otherwise */
	else if(dep > 1)
	{
		_printAtDepth(node->left, dep - 1);
		_printAtDepth(node->right, dep - 1);
	}
}



