#include "list.h"


List* listCreate() {
    List* list = (List*)malloc(sizeof(List));

    list->size = 0;
    list->head = NULL;

    return list;
};

void listInsert(List* list, void* data) {
    // Create new node
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;

    // Insert it at the start
    node->next = list->head;
    list->head = node;
    list->size++;
};

void listPush(List* list, void* data) {
    // Create new node
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;

    // If list is empty
    if (list->size == 0) {
        node->next = list->head;
        list->head = node;
        list->size++;
        return;
    }

    // Get last item on the list
    Node* current = list->head;
    while (current->next != NULL) {
        current = current->next;
    }

    // Append node at the end
    node->next = current->next;
    current->next = node;
    list->size++;
};

void listInsertAt(List* list, int index, void* data) {
    // Push if index is the same as or over list size
    if (index > list->size - 1) {
        listPush(list, data);
        return;
    }

    // Insert if index is 0 or lower
    if (index <= 0) {
        listInsert(list, data);
        return;
    }


    // Create new node
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;

    // Get node at an index and node one before
    Node* current = list->head;
    Node* oneBefore = NULL;
    for (int i = 0; i < index; i++) {
        oneBefore = current;
        current = current->next;
    }

    // Insert new node between them
    oneBefore->next = node;
    node->next = current;
    list->size++;
};


void* listShift(List* list) {
    if (list->size == 0) return NULL;

    Node* head = list->head;
    list->head = head->next;
    void* data = head->data;
    free(head);
    list->size--;

    return data;
};

void* listPop(List* list) {
    if (list->size == 0) return NULL;

    // Get last item on the list
    Node* last = list->head;
    Node* beforeLast = NULL;
    while (last->next != NULL) {
        beforeLast = last;
        last = last->next;
    }

    if (beforeLast != NULL) beforeLast->next = last->next; // List has at least 2 items
    else list->head = NULL;  // List has only 1 item
    void* data = last->data;
    free(last);
    list->size--;

    return data;
};

void* listRemoveAt(List* list, int index) {
    if (index > list->size - 1) return NULL;
    if (index == list->size - 1) return listPop(list);

    if (index < 0) return NULL;
    if (index == 0) return listShift(list);


    // Get node at an index and node one before
    Node* current = list->head;
    Node* oneBefore = NULL;
    for (int i = 0; i < index; i++) {
        oneBefore = current;
        current = current->next;
    }

    // Remove node at the index
    oneBefore->next = current->next;
    void* data = current->data;
    free(current);
    list->size--;

    return data;
};


void* listGet(List* list, int index) {
    if (index > list->size - 1) return NULL;


    Node* current = list->head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }

    return current->data;
};

void* listFirst(List* list) {
    if (list->size == 0) return NULL;

    return list->head->data;
};

void* listLast(List* list) {
    if (list->size == 0) return NULL;

    // Get last item on the list
    Node* current = list->head;
    while (current->next != NULL) {
        current = current->next;
    }

    return current->data;
};


void listClear(List* list) {
    Node* current = list->head;
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }

    free(list);
};