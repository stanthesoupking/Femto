#pragma once

#include <stdbool.h>

typedef struct FEMTO_LinkedList_Node_int FEMTO_LinkedList_Node;

struct FEMTO_LinkedList_Node_int
{
    void *data;
    FEMTO_LinkedList_Node *next;
};

typedef struct FEMTO_LinkedList_int
{
    FEMTO_LinkedList_Node *head;
} FEMTO_LinkedList;

FEMTO_LinkedList* FEMTO_CreateLinkedList();
void FEMTO_DestroyLinkedList(FEMTO_LinkedList* list);

/**
 * Insert the given data at the beginning of the list.
 */
void FEMTO_LinkedListInsert(FEMTO_LinkedList* list, void *data);

/**
 * Push the given data to the end of the linked list.
 * 
 * WARNING: the FEMTO_LinkedListInsert <O(1)> is much more efficient than using this method <O(n)>,
 *  only use it when absolutely necessary.
 */
void FEMTO_LinkedListPush(FEMTO_LinkedList* list, void *data);

/**
 * Return the first element that the given compare function returns true for.
 * 
 * Key is a utility variable for that is passed to the compare method.
 */
void* FEMTO_LinkedListFind(FEMTO_LinkedList* list, void* key, bool (*compare)(void* key, void* data));

/**
 * Remove all elements that return true for the given search method.
 * 
 * Key is a utility variable for that is passed to the compare method.
 */
void FEMTO_LinkedListRemove(FEMTO_LinkedList* list, void* key, bool (*compare)(void* key, void* data));

/**
 * Run the given method on each element in the list.
 * 
 * The 'extra' parameter is optional data that can be included in each call.
 */
void FEMTO_LinkedListTraverse(FEMTO_LinkedList* list, void (*call)(void* data, void* extra), void* extra);