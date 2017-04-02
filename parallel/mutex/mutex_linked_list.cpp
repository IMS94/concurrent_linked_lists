#include<iostream>
#include <pthread.h>

/**
 * Struct to represent a list node
 */
struct list_node {
    long value;
    struct list_node *next;
};

/**
 * Linked list class
 */
class mutex_linked_list {

public:
    struct list_node *head;

    mutex_linked_list() {
        head = NULL;
    }

    ~mutex_linked_list() {
        head = NULL;
    }

    void insert(long value);

    int member(long value);

    int remove(long value);
};

/**
 * Insert function will add the given element to the head of the list.
 * @param value the value to be added to the list
 */
void mutex_linked_list::insert(long value) {
    struct list_node *new_element = new list_node;
    new_element->value = value;
    new_element->next = head;

    head = new_element;
}

/**
 * Check for membership of a value inside the list
 * @param value the value to be searched for membership
 * @return 1 if a member | 0 otherwise
 */
int mutex_linked_list::member(long value) {
    struct list_node *current_node = head;
    while (current_node != NULL) {
        if (current_node->value == value) {
            return 1;
        }
        current_node = current_node->next;
    }
    return 0;
}

/**
 * Removes the given value from the linked list
 * @param value the value to be removed
 * @return 1 if found and deleted | 0 otherwise
 */
int mutex_linked_list::remove(long value) {
    struct list_node *current_node = head;
    struct list_node *previous_node = NULL;

    while (current_node != NULL) {
        if (current_node->value == value) {
            if (previous_node == NULL) {
                head = NULL;
            } else {
                previous_node->next = current_node->next;
            }
            return 1;
        }

        previous_node = current_node;
        current_node = current_node->next;
    }

    return 0;
}

