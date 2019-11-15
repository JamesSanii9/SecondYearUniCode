// LinkedLists.c
// Code provided for ELEC278 Lab 2
// This version uses a linked list to store the data in the set

#include <stdio.h>
#include <stdlib.h>


// Node (or element) in list holds value and pointer to next element
typedef struct Node {
	int			value;
	struct Node	*next;
} Node;


Node *createNode (int x, Node *nxt)
// Create new Node and initialize its value and next pointer
{
	Node *pNode = (Node *)malloc (sizeof(Node));
	if (pNode != NULL)	{
		pNode->value = x;
		pNode->next = nxt;
		}
	return pNode;
}


// LinkedList structure has pointer to first element, and count of
// elements in list.
typedef struct LinkedList {
	Node	*head;
	Node    *end;
	int		size;
} LinkedList;


int isEmpty(LinkedList *l)
// Check if LinkedList is empty. It is empty if head pointer is NULL
{
	return (l->head == NULL);
}


void init(LinkedList *l)
// Initialize LinkedList structure
{
    l->head = NULL;
    l->end = NULL;
    l->size = 0;
}


void addFront(LinkedList* l,int x)
// Add new Node to front of linked list. Create and initialize new Node
// structure with value and current head-of-list pointer.  Make head-of-list
// point to new node
{
    Node* newNode = createNode (x, l->head);
	printf ("Adding %d to front of list\n", x);
    
    l->head = newNode;
    if (l->size == 0){
        l->end = l->head;
    }
    l->size++;
}


void addEnd(LinkedList* l,int x)
// Add new Node to end of linked list
{
    Node* newNode = createNode (x, NULL);
	printf ("Adding %d to end of list\n", x);
	// start by increasing size of linked list
    l->size++;
	// Now comes the fun part - have to find current last Node, so it
	// can be made to point to the new node
	if (isEmpty (l))	{
		// LinkedList currently empty - new node becomes first in list
		l->head = newNode;
	} else	{
	    Node* ptr = l->end;
	    ptr->next = newNode;
	    l->end = ptr->next;
	    
		}
	// Our work is done.
}


void removeFront(LinkedList* l)
// Remove first Node from list
{
	printf ("Remove item at front of list\n");
	if (!isEmpty (l))	{
		// List is not empty, so there is a first Node to delete.
		Node *ptr = l->head;		// point to first node
		// Note that list will be one shorter
		l->size--;
		// head of list is now element after first
		l->head = l->head->next;
		// discard node we no longer need
		free(ptr);
		}
}


void removeEnd(LinkedList* l)
// Remove last Node from list
{
	printf ("Remove item at end of list\n");
	// First determine if any work to do
	if (!isEmpty (l))	{
		// Special case - if there is only one Node
		if (l->size==1)	{
			removeFront(l);
		} else	{
			// More than 1. Note how this code requires that a Node
			// be found that points to a last Node (one with a NULL
			// next pointer, and that doesn't work for the list with
			// only 1 Node.  Fun exercise for the student - think about 
			// how to redesign data and code so that all cases can
			// be handled with one piece of code.
			Node* ptr = l->head;

			// As long as the Node we're pointing to isn't the end of
			// the list, move to next Node
			while(ptr->next->next)	{
				ptr = ptr->next;
				}
			Node* delPtr = ptr->next;
			ptr->next = NULL;
			free(delPtr);
			l->size--;
			}
		}
}


void destroy(LinkedList* l)
// Delete entire linked list - basically by repeatedly deleting first Node
{
	while(!isEmpty(l))	{
		removeFront(l);
		}
}


void removeValue(LinkedList* l,int x)
{
	printf ("Find first %d in list and remove it\n", x);
	Node* ptr = l->head;//node pointer assigned to head
	Node* placeholder;
    if (l->size < 1){
        printf("no nodes found");
        return;
    }

    else if(l->head->value == x){
        removeFront(l);
    }
    else{
        while(ptr -> next != NULL && ptr != NULL){
            if(ptr->next->value == x){
                placeholder = ptr->next;
                ptr->next = ptr->next->next;
                l -> size = l->size -1;
                free(placeholder);
            }
            ptr=ptr->next;
        }
    }
}


void print(LinkedList *l)
{
    Node* ptr = l->head;
	printf("(");
    if(!ptr)	{
        printf("<EMPTY>");
    } else	{
    	while(ptr->next){
        	printf("%d -> ",ptr->value);
        	ptr = ptr->next;
			}
    	printf("%d",ptr->value);
		}
	printf(") [%d]\n",l->size);
}


void update(LinkedList* l)
// Find smallest value in linked list and subtract that value from each value
{
	printf ("Subtract smallest value from all values in list\n");
    if (l->size < 1){
        printf("no nodes found");
        return;
    }
		// Special case - if there is only one Node
		if (l->size==1)	{
			l->head->value = 0;
		} 
		else{
			Node* ptr = l->head;//node pointer assigned to head
            int min = ptr->value;//get first value,make it the minimum
            int counter;//create counter for while loop
            ptr = ptr->next;//move to next node
			// loop through all nodes to find minimum value, assign it to min
			for(counter = 1; counter < l->size; counter++){
			    if(min > ptr->value){
			        min = ptr->value;
			    }
			ptr=ptr->next;
		    }
		    //puts pointer back at start
		    ptr = l->head;
		    //for loop to subtract values
		    for(counter = 0; counter < l->size; counter++){
			    ptr->value -= min;
			    ptr=ptr->next;
		    }
		    
		}
}


int main ()
{
    LinkedList ll;
	printf ("ELEC278 Lab 2 Part 2 - LinkedLists\n");
    init(&ll);
    
    addFront(&ll,5);
    addFront(&ll,2);
    addEnd(&ll,4);
    addEnd(&ll,3);
    
    print(&ll);
    
    update(&ll);
    print(&ll);
    
    removeValue(&ll,0);
        print(&ll);

    removeValue(&ll,2);
    //removeFront(&ll);
    //removeEnd(&ll);
    print(&ll);

    //removeFront(&ll);
    removeValue(&ll,3);
    print(&ll);

    removeValue(&ll,1);
    print(&ll);

    return 0;
}