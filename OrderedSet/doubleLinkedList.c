#include <stdio.h>
#include <stdlib.h>
#include "doubleLinkedList.h"

/**
 * @brief Creates an empty double linked list.
 *
 * Creates a new list with head and tail nodes.
 *
 * @return Pointer to the newly created list.
 */
// create a double linked list
DoubleLinkedList*createDoubleLinkedList(void){
    DoubleLinkedList*list=(DoubleLinkedList*)malloc(sizeof(DoubleLinkedList));
    // create head and tail nodes
    DListNode*head=malloc(sizeof(DListNode));
    DListNode*tail=malloc(sizeof(DListNode));
    // connect head and tail
    head->next=tail;
    head->prev=NULL;

    tail->next=NULL;
    tail->prev=head;
    // save pointers in list
    list->head=head;
    list->tail=tail;

    // current starts at head
    list->current=head;

    // return list
    return list;
}
/**
 * @brief Deletes a double linked list.
 *
 * Frees all nodes including head and tail
 * and releases list memory.
 *
 * @param list Pointer to the list.
 */
void deleteDoubleLinkedList(DoubleLinkedList*list){
    // start from head node in the list
    DListNode*current=list->head;

    // delete all nodes
    while (current!= NULL){
        DListNode*temp=current;
        //move to next node
        current=current->next;
        //free current node
        free(temp);
    }
    // free list structure
    free(list);
}

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