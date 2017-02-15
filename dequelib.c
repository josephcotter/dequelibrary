//JOEY COTTER DEQUE
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "deque.h"

struct node 
{
	int data;
	struct node *prev;
	struct node *next;
};

struct deque
{
	int count;
	struct node *dummy;
};

DEQUE *createDeque(void)
{
	DEQUE *dp;
	struct node *dummy;
	
	dp = (DEQUE*)malloc(sizeof(DEQUE));		//allocating memory for deque
	assert(dp!=NULL);
	dp->count=0;	//initializing count
	
	dummy = (struct node*)malloc(sizeof(struct node));		//allocating memory for dummy node
	assert(dummy!=NULL);
	dummy->next = dummy;	//circular doubly linked list -- making dummy point to itself
	dummy->prev = dummy;
	dp->dummy = dummy;
	
	return dp;
}

int numItems(DEQUE *dp)
{
	return dp->count;
}

void addFirst(DEQUE *dp, int x)
{
	struct node *new;
	
	new = (struct node*)malloc(sizeof(struct node));	//allocating memory for node to be added
	assert(new!=NULL);
	new->data = x;		//setting node data to int argument
	new->next = dp->dummy->next;	//inserting new node 
	dp->dummy->next->prev = new;
	dp->dummy->next = new;
	new->prev = dp->dummy;
	
	dp->count++;	//incrementing count
}

void addLast(DEQUE *dp, int x)
{
	struct node *new;
	
	new = (struct node*)malloc(sizeof(struct node));	//allocating memory for node to be added
	assert(new!=NULL);
	new->data = x;	//setting node data to int argument
	new->next = dp->dummy;	 //inserting new node
	new->prev = dp->dummy->prev;
	dp->dummy->prev->next = new;
	dp->dummy->prev = new;
	
	dp->count++;	//incrementing count
}	

int removeFirst(DEQUE *dp)
{
	struct node *temp;
	int x;

	if (dp->count == 0)		//testing if there is a node to remove
		return -1;

	temp = (struct node *)malloc(sizeof(struct node));		//allocating memory for temporary node
	assert(temp!=NULL);
	temp = dp->dummy->next;		//setting temp to first node in list
	x = temp->data;		//noting data in first node (to be returned)
	dp->dummy->next->next->prev = dp->dummy;	//removing first node
	dp->dummy->next = dp->dummy->next->next;

	free (temp);	//freeing first node
	
	dp->count--;	//decrementing count
	
	return x;
}

int removeLast(DEQUE *dp)
{
	struct node *temp;
	int x;
	
	if (dp->count == 0)		//testing if there is a node to be removed
		return -1;
		
	temp = (struct node *)malloc(sizeof(struct node));		//allocating memory for temporary node
	temp = dp->dummy->prev;		//setting temp to last node in list
	x = temp->data;		//noting data in last node(to be returned)
	dp->dummy->prev->prev->next = dp->dummy;	//removing last node
	dp->dummy->prev = dp->dummy->prev->prev;

	free(temp);		//freeing last node
	
	dp->count--;	//decrementing count
	
	return x;
}

int getFirst(DEQUE *dp)
{
	if (dp->count == 0)
		return -1;
		
	return dp->dummy->next->data;	//if a first node exists, its data is returned
}

int getLast (DEQUE *dp)
{
	if (dp->count == 0)
		return -1;
		
	return dp->dummy->prev->data;	//if a last node exists, its data is returned
}

void destroyDeque(DEQUE *dp)
{
	while (dp->count > 0)	//while the deque has nodes
	{
		removeFirst(dp);
	}
	
	free(dp->dummy);
	free(dp);
}



