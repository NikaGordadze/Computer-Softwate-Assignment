/**
 * @file orderedIntSet.c
 * @brief Implementation of the ordered integer set operations.
 */

#include <stdio.h>
#include <stdlib.h>
#include "orderedIntSet.h"

/**
 * @brief Creates an empty ordered set.
 *
 * Creates a new set with empty double linked list
 * @return Pointer to the created set.
 */
OrderedIntSet*createOrderedSet(void){
    // create set
    OrderedIntSet*set=(OrderedIntSet*)malloc(sizeof(OrderedIntSet));
    // create empty list
    set->list=createDoubleLinkedList();
    //set count=0
    set->count=0;
    // return created set
    return set;
}
/**
 * @brief Deletes an ordered set.
 *
 * Deletes the list and frees the set memory.
 * @param set Pointer to the set.
 */
void deleteOrderedSet(OrderedIntSet*set){
    // delete list
    deleteDoubleLinkedList(set->list);
    // free set memory
    free(set);
}

/**
 * @brief Adds elem to the ordered set at its sorted position.
 *
 * The list is kept in ascending order, so the list is searched for the
 * first node whose value is >= elem and the new node is inserted just
 * before it. Duplicates are rejected.
 *
 * @param s    Valid ordered set
 * @param elem Value to add
 * @return NUMBER_ADDED if elem was added, NUMBER_ALREADY_IN_SET if it was
 *         already present, ALLOCATION_ERROR if a new node could not be created
 */
SetStatus addElement(OrderedIntSet *s, int elem)
{
    DoubleLinkedList *list = s->list;

    /* Start at the first real node (the one after the dummy head) */
    gotoHead(list);
    gotoNextNode(list);

    /* Walk forward while values are smaller than elem; stop at the tail */
    while (list->current != list->tail && getData(list) < elem)
    {
        gotoNextNode(list);
    }

    /* Stopped on a real node holding elem: it is a duplicate */
    if (list->current != list->tail && getData(list) == elem)
    {
        return NUMBER_ALREADY_IN_SET;
    }

    /* Current is the first larger node (or the tail): insert just before it */
    if (insertBefore(list, elem) != LIST_OK)
    {
        return ALLOCATION_ERROR;
    }

    s->count++;                 /* keep the element counter up to date */
    return NUMBER_ADDED;
}

/**
 * @brief Removes elem from the ordered set if it is present.
 *
 * @param s    Valid ordered set
 * @param elem Value to remove
 * @return NUMBER_REMOVED if elem was removed, NUMBER_NOT_IN_SET if elem
 *         was not in the set
 */
SetStatus removeElement(OrderedIntSet *s, int elem)
{
    DoubleLinkedList *list = s->list;

    /* Start at the first real node and walk to the first value >= elem */
    gotoHead(list);
    gotoNextNode(list);
    while (list->current != list->tail && getData(list) < elem)
    {
        gotoNextNode(list);
    }

    /* Found elem: delete that node and update the counter */
    if (list->current != list->tail && getData(list) == elem)
    {
        deleteCurrent(list);
        s->count--;
        return NUMBER_REMOVED;
    }

    return NUMBER_NOT_IN_SET;
}


/* Patrick Barry (25403842) - set operations.*/

/**
 * @brief Checks whether the current node of a list is the tail.
 *
 * @param list the double linked list to check
 * @return 1 if current node is the tail, 0 otherwise
 */
static int atTail(DoubleLinkedList *list)
{
    return list->current == list->tail;
}

/**
 * @brief Moves current node to the first real element of a list
 *        (the node after head; this is the tail if the list is empty).
 *
 * @param list the double linked list
 */
static void gotoFirstElement(DoubleLinkedList *list)
{
    gotoHead(list);
    gotoNextNode(list);
}

/**
 * @brief Creates a new set containing the same elements as s.
 *
 * Used when an operation is called with the same set twice
 * (e.g. union of set 3 with set 3), because both "walkers" would
 * otherwise share the same current pointer.
 *
 * @param s set to copy (not modified)
 * @return pointer to the new set, or NULL on allocation error
 */
static OrderedIntSet *copySet(OrderedIntSet *s)
{
    OrderedIntSet *result = createOrderedSet();

    if (result == NULL)
    {
        return NULL;
    }

    gotoFirstElement(s->list);
    while (!atTail(s->list))
    {
        if (addElement(result, getData(s->list)) == ALLOCATION_ERROR)
        {
            deleteOrderedSet(result);
            return NULL;
        }
        gotoNextNode(s->list);
    }

    return result;
}

/**
 * @brief Computes the intersection of two ordered sets.
 *
 * Both sets are sorted, so they are walked side by side (like the
 * merge step of merge sort): whichever current value is smaller is
 * skipped, and equal values are copied into the result.
 * Neither s1 nor s2 is modified.
 *
 * @param s1 first set
 * @param s2 second set
 * @return new set with all elements in both s1 and s2 (empty set if
 *         there are none), or NULL on allocation error
 */
OrderedIntSet *setIntersection(OrderedIntSet *s1, OrderedIntSet *s2)
{
    OrderedIntSet *result;
    int a;
    int b;

    if (s1 == s2)
    {
        return copySet(s1); /* A intersect A = A */
    }

    result = createOrderedSet();
    if (result == NULL)
    {
        return NULL;
    }

    gotoFirstElement(s1->list);
    gotoFirstElement(s2->list);

    while (!atTail(s1->list) && !atTail(s2->list))
    {
        a = getData(s1->list);
        b = getData(s2->list);

        if (a < b)
        {
            gotoNextNode(s1->list);
        }
        else if (b < a)
        {
            gotoNextNode(s2->list);
        }
        else /* a == b: element is in both sets */
        {
            if (addElement(result, a) == ALLOCATION_ERROR)
            {
                deleteOrderedSet(result);
                return NULL;
            }
            gotoNextNode(s1->list);
            gotoNextNode(s2->list);
        }
    }

    return result;
}

/**
 * @brief Computes the union of two ordered sets.
 *
 * Copies every element of s1 and every element of s2 into a new set.
 * addElement() already rejects duplicates, so no element appears twice.
 * Neither s1 nor s2 is modified.
 *
 * @param s1 first set
 * @param s2 second set
 * @return new set with all elements in s1 or s2, or NULL on
 *         allocation error
 */
OrderedIntSet *setUnion(OrderedIntSet *s1, OrderedIntSet *s2)
{
    OrderedIntSet *result = copySet(s1);

    if (result == NULL || s1 == s2)
    {
        return result; /* A union A = A */
    }

    gotoFirstElement(s2->list);
    while (!atTail(s2->list))
    {
        /* NUMBER_ALREADY_IN_SET is fine here - it just means a duplicate */
        if (addElement(result, getData(s2->list)) == ALLOCATION_ERROR)
        {
            deleteOrderedSet(result);
            return NULL;
        }
        gotoNextNode(s2->list);
    }

    return result;
}

/**
 * @brief Computes the difference s1 - s2 of two ordered sets.
 *
 * Walks both sorted sets side by side. An element of s1 is copied
 * into the result only if it is not found in s2.
 * Neither s1 nor s2 is modified.
 *
 * @param s1 set to take elements from
 * @param s2 set whose elements are left out
 * @return new set with all elements in s1 but not in s2 (empty set if
 *         s1 and s2 are equal), or NULL on allocation error
 */
OrderedIntSet *setDifference(OrderedIntSet *s1, OrderedIntSet *s2)
{
    OrderedIntSet *result = createOrderedSet();
    int a;

    if (result == NULL || s1 == s2)
    {
        return result; /* A - A = {} */
    }

    gotoFirstElement(s1->list);
    gotoFirstElement(s2->list);

    while (!atTail(s1->list))
    {
        a = getData(s1->list);

        /* skip elements of s2 that are smaller than a */
        while (!atTail(s2->list) && getData(s2->list) < a)
        {
            gotoNextNode(s2->list);
        }

        /* keep a unless s2 is now sitting on the same value */
        if (atTail(s2->list) || getData(s2->list) != a)
        {
            if (addElement(result, a) == ALLOCATION_ERROR)
            {
                deleteOrderedSet(result);
                return NULL;
            }
        }

        gotoNextNode(s1->list);
    }

    return result;
}

/**
 * @brief Prints the set like {1, 2, 3}, or {} if it is empty
 * @param s the ordered set to print
 */
void printToStdout(OrderedIntSet *s)
{
    // start after the head because the head has no number
    DListNode *n = s->list->head->next;

    printf("{");
    while (n != s->list->tail)   // tail has no number either, so stop there
    {
        printf("%d", n->data);

        // no comma after the last number
        if (n->next != s->list->tail)
        {
            printf(", ");
        }
        n = n->next;   // go to the next node
    }
    printf("}");
}