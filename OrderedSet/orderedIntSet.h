/**
 * @file orderedIntSet.h
 * @brief Ordered set of integers built on a double linked list.
 */

#ifndef ORDEREDINTSET_H
#define ORDEREDINTSET_H
#include "doubleLinkedList.h"
/**
 * @brief Ordered set structure.
 *
 * Stores a double linked list and the number
 * of elements in the set.
 */
typedef struct OrderedIntSet
{
    DoubleLinkedList *list;     /**< list holding the numbers in ascending order */
    int count;                  /**< number of elements in the set */
} OrderedIntSet;

OrderedIntSet *createOrderedSet(void);
void deleteOrderedSet(OrderedIntSet *set);

/**
 * @brief Return values of the ordered set operations.
 */
typedef enum
{
    NUMBER_ALREADY_IN_SET, /**< element was already in the set */
    NUMBER_NOT_IN_SET,     /**< element was not in the set */
    NUMBER_ADDED,          /**< element was added */
    NUMBER_REMOVED,        /**< element was removed */
    ALLOCATION_ERROR       /**< memory could not be allocated */
} SetStatus;

SetStatus addElement(OrderedIntSet *s, int elem);
SetStatus removeElement(OrderedIntSet *s, int elem);
OrderedIntSet *setIntersection(OrderedIntSet *s1, OrderedIntSet *s2);
OrderedIntSet *setUnion(OrderedIntSet *s1, OrderedIntSet *s2);
OrderedIntSet *setDifference(OrderedIntSet *s1, OrderedIntSet *s2);
void printToStdout(OrderedIntSet *s);
#endif // ORDEREDINTSET_H
