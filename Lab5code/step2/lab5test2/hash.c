// HASH.C
// Program for use with ELEC278 Lab 5 Part 2.
//
// History:
// 161106	HF	First release
// 171102	DA	Minor tweaks


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DLL.h"
#include <time.h>
#include <math.h>

#define MAX_WORD_SIZE 50

typedef struct HashTable {
	LinkedList** a;
	int size;
	int collisions;
} HashTable;


HashTable* initHashTable(int s)
{
	HashTable* h = malloc(sizeof(HashTable));
	int		i;
	h->size = s;
	h->a = malloc(sizeof(LinkedList) * s);
	for(i=0;i<s;i++)
		h->a[i]= init();
	h->collisions = 0;
	return h;
}//initHashTable()


long h(char* x)
// This function computes a hash code for a given string.  Note that hash
// code is unbounded - it needs to be reduced modulo the size of the array
// used to store the data. (You will see another function hash() below that
// completes the index calculation.)

{
	long sum = 0;
	int len = 0;
	while (*(x + len++) != '\0');
	
	for (int i = 0; i < len; i++) {
		char t = *(x + i);
		sum += ((int)(t)) * pow(31, len - 1 - i);
	}
	
	return sum;
}//h()


double loadFactor(HashTable* ht)
{
	double nonempty = 0;
	int i;
	// count number of non-empty hash table slots
	for(i=0; i<ht->size; i++)	{
		if (isEmpty(ht->a[i])==0)	nonempty++;
		}
	return nonempty/ht->size*100;
}//loadFactor()


int hash(char* x, int size)
// Index calculation. Function h() computes general hash for the string;
// this function turns the hash into a valid index, given the size of the
// array.
{
	return h(x) % size;
}


void insert(HashTable *ht, char* x)
{
	//#########################COMPLETE THIS FUNCTION##########################
	// ---<SNIP>---
	if(loadFactor(ht) > 60){
		HashTable* new = initHashTable(ht->size*2);
		for(int i = 0;i<ht->size; i++){
			LinkedList* linklist = ht->a[i];
			Node* current = linklist->head;
			while(current != NULL){
				insert(new,current->value);
				Node* remove = current;
				current = current -> next;
				free(remove);
			}

		}
		for(int i = 0;i<ht->size; ++i){
			free(ht->a[i]);
		}
		free(ht);
		ht->size = new->size;
		ht->a = new->a;
		ht->collisions = new-> collisions;
	}
	int xhash = hash(x, ht->size);
	LinkedList* linklist = ht->a[xhash];

	if(!isEmpty(linklist)){
		ht->collisions = ht->collisions + 1;
	}
	addFront(linklist,x);





	// ---<SNIP>---
}//insert()


int findInTable(HashTable *ht, char* x)
{
	//#########################COMPLETE THIS FUNCTION##########################
	// ---<SNIP>---
	int index = hash(x,ht->size);
	LinkedList *current = *(ht->a+index);
	return find(current, x);
	// ---<SNIP>---	
}

void erase(HashTable *ht,char* x){
	if(findInTable(ht,x) == 0){
		return;
	}
	int index = hash(x, ht-> size);
	LinkedList* linklist = ht->a[index];
	if(linklist-> head!= NULL && strcmp(x, linklist->head->value) == 0){
		linklist-> head = linklist -> head -> next;
		ht->collisions = ht->collisions - 1;
		return;
	}
	if(linklist->head != NULL){
		Node* current = linklist -> head;
		Node* nextOne = linklist -> head -> next;
		while(nextOne != NULL){
			if(strcmp(x, nextOne->value)==0){
				current->next = nextOne->next;
				ht->collisions = ht->collisions - 1;
				return;
			}
			current = nextOne;
			nextOne = nextOne->next;
		}
		
	}


}


void printTable(HashTable *ht)
{
	int i;
	printf("----------\n");
	for (i = 0; i < ht->size; i++)	{
		printf("%d --> ", i);
		print(ht->a[i]);
		}
	printf("# of Collisions=%d\n", ht->collisions);
	printf("Load Factor %%=%.2f\n----------", loadFactor(ht));
}


int main() {
	//FILE *fp;
	//fp = fopen("words.txt","w+");
	int i=0;
	HashTable* h = initHashTable(101);


	// Generate a set of random strings (given the way this works, everyone
	// gets the same set of random strings!) insert each into the hash table
	// and then print the table.
	for(i=0;i<100;i++){
		int x = rand()%5+1;
		char *p = malloc(sizeof(char)*x);
		int j=0;
		for(j=0;j<x;j++)
			p[j] = rand()%26 + 97;
		p[j]='\0';
		insert(h,p);
	}

	printTable(h);
	return 0;
}
