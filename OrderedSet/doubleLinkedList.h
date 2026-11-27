/**
 * @file doubleLinkedList.h
 * @brief Double linked list of integers with dummy head and tail nodes.
 */

#ifndef DOUBLELINKEDLIST_H
#define DOUBLELINKEDLIST_H
/**
 * @brief Node of a double linked list.
 * Stores an integer value and pointers to the
 * previous and next nodes.
 */
typedef struct DListNode
{
    int data;                   /**< number stored in node */
    struct DListNode *prev;     /**< previous node */
    struct DListNode *next;     /**< next node */
} DListNode;

/**
 * @brief Double linked list structure.
 * contains pointers to the head node,
 * tail node and current node.
 */
typedef struct DoubleLinkedList
{
    DListNode *head;            /**< empty node at the start */
    DListNode *tail;            /**< empty node at the end */
    DListNode *current;         /**< node the operation works on */
} DoubleLinkedList;


DoubleLinkedList*createDoubleLinkedList(void);
void deleteDoubleLinkedList(DoubleLinkedList*list);

/**
 * @brief Return values of the double linked list operations.
 */
typedef enum
{
    LIST_OK,         /**< operation successful*/
    LIST_ERROR,      /**< operation not allowed*/
    LIST_ALLOC_ERROR /**< memory for a new node could not be allocated */
} ListStatus;

int getData(DoubleLinkedList *list);
void gotoNextNode(DoubleLinkedList *list);
void gotoPreviousNode(DoubleLinkedList *list);
void gotoHead(DoubleLinkedList *list);
void gotoTail(DoubleLinkedList *list);
ListStatus insertAfter(DoubleLinkedList *list, int newData);
ListStatus insertBefore(DoubleLinkedList *list, int newData);
ListStatus deleteCurrent(DoubleLinkedList *list);

#endif // DOUBLELINKEDLIST_H
