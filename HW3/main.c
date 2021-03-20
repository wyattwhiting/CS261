#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "hashMap.h"

/*
 the getWord function takes a FILE pointer and returns you a string which was
 the next word in the in the file. words are defined (by this function) to be
 characters or numbers separated by periods, spaces, or newlines.
 
 when there are no more words in the input file this function will return NULL.
 
 this function will malloc some memory for the char* it returns. it is your job
 to free this memory when you no longer need it.
 */
char* getWord(FILE *file); /* prototype */
void printHashMap(struct hashMap * ht); /* prototype */

/****************************************/

int main (int argc, const char * argv[]) 
{
    /*Write this function*/

    /* declare variables */
    hashMap map;
    char * word;
    FILE * fp;

    /* check for number of command line arguments */
    if(argc != 2)
    {
        printf("You did not specify the correct number of command line arguments. \n");
        return 0;
    }

    /* initialize map and open file from command line string argument */
    initMap(&map, 50); 
    fp = fopen(argv[1], "r");

    /* seed with first word from file */
    for(word = getWord(fp); word != NULL; word = getWord(fp))
    {   
        insertMap(&map, word, 1);
        free(word);
    }

    /* word count */
    printf("links: %d \n", sizeMap(&map));

    /* print the (key, value) pairs */
    printHashMap(&map);

    /* free map at end of program, close file, and return 0 */
    fclose(fp);
    freeMap(&map);
    return 0;
}




char* getWord(FILE *file)
{
	
	int length = 0;
	int maxLength = 16;
	char character;
    
	char* word = (char*)malloc(sizeof(char) * maxLength);
	assert(word != NULL);
    
	while( (character = fgetc(file)) != EOF)
	{
		if((length+1) > maxLength)
		{
			maxLength *= 2;
			word = (char*)realloc(word, maxLength);
		}
		if((character >= '0' && character <= '9') || /*is a number*/
		   (character >= 'A' && character <= 'Z') || /*or an uppercase letter*/
		   (character >= 'a' && character <= 'z') || /*or a lowercase letter*/
		   character == 39) /*or is an apostrophy*/
		{
			word[length] = character;
			length++;
		}
		else if(length > 0)
			break;
	}
    
	if(length == 0)
	{
		free(word);
		return NULL;
	}
	word[length] = '\0';
	return word;
}

