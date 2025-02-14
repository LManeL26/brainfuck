#include <stdlib.h>
#include <stdio.h>
#include "list.h"
#include "global.h"

#pragma region Array

inline void *array_at(VoidArray *arr, int index)
{
    if (arr == NULL)
        return NULL;
    if (arr->len >= index)
        return NULL;

    return arr->head + index;
}

#pragma endregion
#pragma region List

void node_print(VoidNode *node)
{
    if (node == NULL)
    {
        printf("node NULL\n");
        return;
    }
    printf("node (%p) => %p %p | %p\n",
           node,
           node->prev,
           node->next,
           node->value);
}

void list_print(VoidList *list)
{
    if (list == NULL)
    {
        printf("list NULL\n");
        return;
    }
    VoidNode *node = list->head;
    while (node != NULL)
    {
        node_print(node);
        node = node->next;
    }
}

VoidList *list_init()
{
    VoidList *list = malloc(sizeof(VoidList));
    list->head = NULL;
    return list;
}

bool list_empty(VoidList *list)
{
    return list->head == NULL;
}

int list_length(VoidList *list)
{
    if (list == NULL)
        return -1;
    size_t size = 0;
    VoidNode *node = list->head;
    for (size = 0; node != NULL; size++)
    {
        node = node->next;
    }
    return size;
}

VoidNode *list_nodeat(VoidList *list, int index)
{
    if (list == NULL || list_empty(list))
        return NULL;
    VoidNode *node = list->head;
    if (index < 0) //TODO from tail
    {
        int size = list_length(list);
        index += size;
        if (index < -1)
            return NULL;
    }
    int currentPos = 0;
    while (currentPos++ < index)
    {
        node = node->next;
        if (node == NULL)
            return NULL;
    }
    return node;
}

void *list_getvoid(VoidList *list, int index)
{
    VoidNode *node = list_nodeat(list, index);
    if (node == NULL)
        return NULL;
    return node->value;
}

bool list_set(VoidList *list, int index, void *value)
{
    VoidNode *node = list_nodeat(list, index);
    if (node == NULL)
        return false;
    node->value = value;
    return true;
}

void list_clear(VoidList *list)
{
    VoidNode *node = list->head;
    while (node != NULL)
    {
        VoidNode *tmp = node;
        node = node->next;
        free(tmp);
    }
    list->head = NULL;
}

void list_free(VoidList *list)
{
    list_clear(list);
    free(list);
}

int list_pushp(VoidList *list, void *value)
{
    if (list == NULL)
        return -1;

    VoidNode *currentNode = malloc(sizeof(VoidNode));
    if (currentNode == NULL)
        return -2;

    currentNode->value = value;
    currentNode->next = NULL;

    VoidNode *lastNode = list->head;
    if (lastNode == NULL)
    {
        list->head = currentNode;
        currentNode->prev = NULL;
        return 0;
    }

    u32 size = 1;
    for (; lastNode->next != NULL; ++size)
    {
        lastNode = lastNode->next;
    }
    lastNode->next = currentNode;
    currentNode->prev = lastNode;
    return size;
}

void *list_pop(VoidList *list, int index)
{
    return NULL;
}

#pragma endregion