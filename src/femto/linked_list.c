#include "femto/linked_list.h"

#include <stdlib.h>

FEMTO_LinkedList* FEMTO_CreateLinkedList()
{
    FEMTO_LinkedList* list = (FEMTO_LinkedList*) malloc(sizeof(struct FEMTO_LinkedList_int));
    
    list->head = NULL;
    
    return list;
}

void FEMTO_DestroyLinkedList(FEMTO_LinkedList* list)
{
    // TODO: Free individual elements using a supplied 'destroy(void* data)' method
    // ...

    free(list);
}

/**
 * Insert the given data at the beginning of the list.
 */
void FEMTO_LinkedListInsert(FEMTO_LinkedList* list, void *data)
{
    // Node to insert
    FEMTO_LinkedList_Node* newNode = (FEMTO_LinkedList_Node*) malloc(sizeof(struct FEMTO_LinkedList_Node_int));
    newNode->data = data;
    newNode->next = NULL;

    // Find insert location
    FEMTO_LinkedList_Node* n = list->head;
    if(n == NULL)
    {
        // Set head of list
        list->head = newNode;
    }
    else
    {
        // Insert at head of list
        list->head = newNode;
        newNode->next = n;
    }
}

/**
 * Push the given data to the end of the linked list.
 * 
 * WARNING: the FEMTO_LinkedListInsert <O(1)> is much more efficient than using this method <O(n)>,
 *  only use it when absolutely necessary.
 */
void FEMTO_LinkedListPush(FEMTO_LinkedList* list, void *data)
{
    // Node to insert
    FEMTO_LinkedList_Node* newNode = (FEMTO_LinkedList_Node*) malloc(sizeof(struct FEMTO_LinkedList_Node_int));
    newNode->data = data;
    newNode->next = NULL;

    // Find insert location
    FEMTO_LinkedList_Node* n = list->head;
    if(n == NULL)
    {
        // Set head of list
        list->head = newNode;
    }
    else
    {
        // Traverse to end of list
        while(n->next != NULL)
        {
            n = n->next;
        }
    
        // Append to end of list
        n->next = newNode;
    }
}

void* FEMTO_LinkedListFind(FEMTO_LinkedList* list, void* key, bool (*compare)(void* key, void* data))
{
    // TODO: Implement this
    // ...

    return NULL;
}
void FEMTO_LinkedListRemove(FEMTO_LinkedList* list, void* key, bool (*compare)(void* key, void* data))
{
    // TODO: Implement this
    // ...
}

/**
 * Run the given method on each element in the list.
 * 
 * The 'extra' parameter is optional data that can be included in each call.
 */
void FEMTO_LinkedListTraverse(FEMTO_LinkedList* list, void (*call)(void* data, void* extra), void* extra)
{
        FEMTO_LinkedList_Node* n = list->head;
        // Traverse to end of list
        while(n != NULL)
        {
            call(n->data, extra);
            n = n->next;
        }
}