#include <stdlib.h>
#include "doubleLinkedList.h"

/**
 * @brief Inserts a new node holding newData after the current node.
 *
 * The list uses dummy head and tail nodes, so nothing can be inserted
 * after the tail. The current node is not changed by this operation.
 *
 * @param list    Valid double linked list
 * @param newData Value to store in the new node
 * @return LIST_OK on success, LIST_ERROR if current is the tail,
 *         LIST_ALLOC_ERROR if memory could not be allocated
 */
ListStatus insertAfter(DoubleLinkedList *list, int newData)
{
    DListNode *newNode;

    /* Nothing may be inserted after the tail */
    if (list->current == list->tail)
    {
        return LIST_ERROR;
    }

    newNode = malloc(sizeof(DListNode));
    if (newNode == NULL)
    {
        return LIST_ALLOC_ERROR;
    }

    /* Point the new node at its neighbours */
    newNode->data = newData;
    newNode->prev = list->current;
    newNode->next = list->current->next;

    /* Re-link the neighbours to the new node (successor first, since
       current->next is overwritten on the next line) */
    list->current->next->prev = newNode;
    list->current->next = newNode;

    return LIST_OK;
}

/**
 * @brief Inserts a new node holding newData before the current node.
 *
 * Nothing can be inserted before the dummy head node. The current node
 * is not changed by this operation.
 *
 * @param list    Valid double linked list
 * @param newData Value to store in the new node
 * @return LIST_OK on success, LIST_ERROR if current is the head,
 *         LIST_ALLOC_ERROR if memory could not be allocated
 */
ListStatus insertBefore(DoubleLinkedList *list, int newData)
{
    DListNode *newNode;

    /* Nothing may be inserted before the head */
    if (list->current == list->head)
    {
        return LIST_ERROR;
    }

    newNode = malloc(sizeof(DListNode));
    if (newNode == NULL)
    {
        return LIST_ALLOC_ERROR;
    }

    /* Point the new node at its neighbours */
    newNode->data = newData;
    newNode->next = list->current;
    newNode->prev = list->current->prev;

    /* Re-link the neighbours to the new node (predecessor first, since
       current->prev is overwritten on the next line) */
    list->current->prev->next = newNode;
    list->current->prev = newNode;

    return LIST_OK;
}

/**
 * @brief Deletes the current node from the list.
 *
 * The dummy head and tail cannot be deleted. After a successful delete,
 * current is set to the successor of the deleted node.
 *
 * @param list Valid double linked list
 * @return LIST_OK on success, LIST_ERROR if current is head or tail
 */
ListStatus deleteCurrent(DoubleLinkedList *list)
{
    DListNode *victim = list->current;

    /* Head and tail are structural and may not be deleted */
    if (victim == list->head || victim == list->tail)
    {
        return LIST_ERROR;
    }

    /* Make the two neighbours skip over the victim */
    victim->prev->next = victim->next;
    victim->next->prev = victim->prev;

    /* Move current off the victim BEFORE freeing it, so it never dangles */
    list->current = victim->next;

    free(victim);
    return LIST_OK;
}