#ifndef LIST_h_
#define LIST_h_

#include <stdio.h>
#include <stdlib.h>

/**
 * A node struct for the linked list
 */
typedef struct Node {
    void* data;
    struct Node* next;
} Node;

/**
 * A linked list struct
 */
typedef struct List {
    int size;
    Node* head;
} List;



/**
 * Creates new list.
 *
 * \return pointer to the new list
 */
List* listCreate();

/**
 * Inserts new data at the beggining of the list.
 *
 * \param list Pointer to the list
 * \param data Data to be inserted
 */
void listInsert(List* list, void* data);

/**
 * Pushes new data at the end of the list.
 *
 * \param list Pointer to the list
 * \param data Data to be pushed
 */
void listPush(List* list, void* data);

/**
 * Inserts new data at the specific index of the list.
 *
 * \param list Pointer to the list
 * \param index Index
 * \param data Data to be inserted
 */
void listInsertAt(List* list, int index, void* data);


/**
 * Removes first element of the list and returns it.
 *
 * \param list Pointer to the list
 * \return Removed data
 */
void* listShift(List* list);

/**
 * Removes last element of the list and returns it.
 *
 * \param list Pointer to the list
 * \return Removed data
 */
void* listPop(List* list);

/**
 * Removes data at the specific index from the list, and returns it.
 *
 * \param list Pointer to the list
 * \param index Index
 * \param data Removed data
 */
void* listRemoveAt(List* list, int index);


/**
 * Gets element from the list from the specified index.
 *
 * \param list Pointer to the list
 * \param index Index to get data from
 * \return Data from specified index
 */
void* listGet(List* list, int index);

/**
 * Gets first element from the list.
 *
 * \param list Pointer to the list
 * \return Data
 */
void* listFirst(List* list);

/**
 * Gets last element from the list.
 *
 * \param list Pointer to the list
 * \return Data
 */
void* listLast(List* list);


/**
 * Clears the whole list from the memory.
 *
 * \param list Pointer to the list
 */
void listClear(List* list);

#endif