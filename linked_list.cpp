#include<iostream>

/**
 * Struct to represent a list node
 */
struct list_node {
    unsigned short value;
    struct list_node *next;
};

/**
 * Linked list class
 */
class linked_list {

private:
    struct list_node *head;

public:
    linked_list() {
        head = NULL;
    }

    ~linked_list() {
        head = NULL;
    }

    /**
    * Insert function will add the given element to the head of the list.
    * @param value the value to be added to the list
    */
    void insert(unsigned short value) {
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
    int member(unsigned short value) {
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
    int remove(unsigned short value) {
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
};