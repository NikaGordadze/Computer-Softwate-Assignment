#ifndef ORDEREDINTSET_H
#define ORDEREDINTSET_H
#include "doubleLinkedList.h"
/**
 * @brief Ordered set structure.
 *
 * Stores a double linked list and the number
 * of elements in the set.
 */
typedef struct OrderedIntSet{
    DoubleLinkedList *list;
    int count;
}OrderedIntSet;
/**
 * @brief Creates an empty ordered set.
 *
 * Creates a new set with an empty
 * double linked list.
 * @return Pointer to the created set.
 */
OrderedIntSet *createOrderedSet(void);
/**
 * @brief Deletes an ordered set.
 *
 * Frees the list and the set memory.
 * @param set Pointer to the set.
 */
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
