#ifndef LIST_DEFINER
#define LIST_DEFINER

#include <stdlib.h>
#include "global.h"

#pragma region Array
typedef struct BasicArray
{
    void *head;
    int len;
} BasicArray;

#define Array(T)     \
    struct array_##T \
    {                \
        T *head;     \
        int len      \
    }
#define array_t(T) Array(T)

typedef BasicArray VoidArray;
typedef BasicArray void_array_t;

#pragma endregion

#pragma region List
/**
 * @brief 
 * 
 */
typedef struct VoidNode
{
    struct VoidNode *prev;
    void *value;
    struct VoidNode *next;
} VoidNode;
/**
 * @brief 
 * 
 */
typedef struct VoidList
{
    struct VoidNode *head;
} VoidList;

/**
 * @brief Initializes a new list
 *
 * @return VoidList* The list just generated
 */
VoidList *list_init();
/**
 * @brief Checks if the list is empty
 *
 * @param list The list to check
 * @return true if it is empty,
 * @return false otherwise
 */
bool list_empty(VoidList *list);
/**
 * @brief Gets the list's length
 *
 * @param list The list to check
 * @return The size of the list, -1 if list == NULL
 */
int list_length(VoidList *list);
/**
 * @brief Gets element in specified position
 *
 * @param list The list to check
 * @param index The index to get
 * @return void* value
 */
void *list_getvoid(VoidList *list, int index);
/**
 * @brief Gets element in specified position
 *
 * @param T the datatype it will being casted
 * @param list The list to check
 * @param index The index to get
 * @return T* pointer to the data
 */
#define list_getp(T, list, index) ((T*)list_getvoid(list, index))
/**
 * @brief Gets element in specified position
 *
 * @param T the datatype it will being casted
 * @param list The list to check
 * @param index The index to get
 * @return The data casted to T
 */
#define list_get(T, list, index) (*list_getp(T, list, index))

void *list_pop(VoidList *list, int index); // TODO

bool list_set(VoidList *list, int index, void *value);
int list_pushp(VoidList *list, void *value);
#define list_pusht(T, list, value) ({T* v = malloc(sizeof(T)); *v=value; list_pushp(list, v);})

void list_clear(VoidList *list);
void list_free(VoidList *list);

VoidNode *list_nodeat(VoidList *list, int index);

void node_print(VoidNode* node);
void list_print(VoidList* node);

#pragma endregion

#endif