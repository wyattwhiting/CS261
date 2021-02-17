#include <stdlib.h>
#include "hashMap.h"
#include "structs.h"
#include <string.h>

/* extra prototype */
hashLink * getLinkPointer(struct hashMap * ht, KeyType k);


int stringHash1(char * str)
{
	int i;
	int r = 0;
	for (i = 0; str[i] != '\0'; i++)
		r += str[i];
	return r;
}

int stringHash2(char * str)
{
	int i;
	int r = 0;
	for (i = 0; str[i] != '\0'; i++)
		r += (i+1) * str[i]; /*the difference between 1 and 2 is on this line*/
	return r;
}

void initMap (struct hashMap * ht, int tableSize)
{
	int index;
	if(ht == NULL)
		return;
	ht->table = (hashLink**)malloc(sizeof(hashLink*) * tableSize);
	ht->tableSize = tableSize;
	ht->count = 0;
	for(index = 0; index < tableSize; index++)
		ht->table[index] = NULL;
}

void freeMap (struct hashMap * ht)
{   /*write this*/
    /* declare some variables */
    int bucket;
    hashLink * currLink;

    /* for all buckets */
    for(bucket = 0; bucket < ht->tableSize; bucket++)
    {
        /* while bucket is not empty */
        while(ht->table[bucket] != NULL)
        {
            /* store pointer, advance head pointer to next, free jumped link */
            currLink = ht->table[bucket];
            ht->table[bucket] = ht->table[bucket]->next;
            free(currLink->key);
            free(currLink);
        }
    }

    /* once here, just need to free the pointer array and reset count*/
    free(ht->table);
    ht->count = 0;
}

void insertMap (struct hashMap * ht, KeyType k, ValueType v)
{  /*write this*/
    /* some variables */
    int bucket;
    hashLink * newLink;

    /* see if link with given key exists */
    newLink = getLinkPointer(ht, k);
    bucket = (int)(labs(stringHash1(k)) % ht->tableSize);

    /* if it already exists, just replace the value */
    if(newLink != NULL)
        newLink->value = v;
    /* otherwise, if it doesn't exist */
    else
    {
        /* allocate new memory for link */
        newLink = (hashLink*)malloc(sizeof(hashLink));

        /* insert new link pointer at beginning of bucket */
        newLink->next = ht->table[bucket];
        ht->table[bucket] = newLink;

        /* assign values */
        newLink->value = v;
        newLink->key = (char *)malloc(sizeof(char) * strlen(k) + 1);
        strcpy(newLink->key, k);
        

        /* increment number of links */
        ht->count++;
    }
}

ValueType* atMap (struct hashMap * ht, KeyType k)
{   /*write this*/
    
    /* declare variables */
    int bucket;
    hashLink * currLink;

    /* hashResult gets hash function mod tablesize */
    bucket = (int)(labs(stringHash1(k)) % ht->tableSize);

    /* iterate through links at bucket */
    for(currLink = ht->table[bucket]; currLink != NULL; currLink = currLink->next)
        /* if key is found at currLink , return pointer to value*/
        if(strcmp(currLink->key, k) == 0) return &(currLink->value);

    /* if loop terminates on its own, return null pointer */
    return NULL;
}

int containsKey (struct hashMap * ht, KeyType k)
{   /* write this */
    /* call atMap(ht, k). If return is not NULL, it contains the key */
    /* otherwise, it does not contain the key */
    return atMap(ht, k) != NULL;
}

void removeKey (struct hashMap * ht, KeyType k)
{  /*write this?*/
    /* some variables */
    int bucket;
    hashLink * currLink;


    if(getLinkPointer(ht, k) == NULL) return;   

    bucket = (int)(labs(stringHash1(k)) % ht->tableSize);

    /* start currLink at first link in bucket */
    currLink = ht->table[bucket];

    /* if we get here, link with KeyType k is in list */
    /* edge case, head of bucket is value */
    if(strcmp(currLink->key, k) == 0)
    {
        /* set bucket to point at next element and free head */
        ht->table[bucket] = currLink->next;
        free(currLink->key);
        free(currLink);
        ht->count--;
        return;
    }

    /* special case does not hold, so find link before one to remove */
    while(currLink->next != getLinkPointer(ht, k)) currLink = currLink->next;

    /* currLink now points to hashLink before one to remove */
    currLink->next = currLink->next->next;
    free(currLink->next->key);
    free(currLink->next);
    ht->count--;

}

int sizeMap (struct hashMap *ht)
{  /*write this*/
    return ht->count;
}

int capacityMap(struct hashMap *ht)
{  /*write this*/
    int count;
    int bucket;

    /* iterate through all elements of table and count non-null entries*/
    for(bucket = 0; bucket < ht->tableSize; bucket++)
        if(ht->table[bucket] != NULL) count++;
    
    /* return the result */
    return count;
}

int emptyBuckets(struct hashMap *ht)
{  /*write this*/
    /* number of empty buckets is size of table less number of non-empty buckets */
    return ht->tableSize - capacityMap(ht);
}

float tableLoad(struct hashMap *ht)
{  /*write this*/
    return ((float)ht->count) / ht->tableSize;
}

/* function I wrote to return a hashLink* which points to the link containing
 * key with KeyType k */
hashLink * getLinkPointer(struct hashMap * ht, KeyType k)
{
    /* declare some variables */
    int bucket;
    hashLink * currLink;

    /* calculate bucket */
    bucket = (int)(labs(stringHash1(k)) % ht->tableSize);

    /* loop through all links in bucket */
    for(currLink = ht->table[bucket]; currLink != NULL; currLink = currLink->next)
    {
        /* return pointer when it points to one with matching string */
        if(strcmp(currLink->key, k) == 0) return currLink;
    }

    /* return null if none are found */
    return NULL;
}