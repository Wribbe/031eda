#include <iostream>
#include "list.h"

List::List() : first(nullptr) {}

List::~List()
    /* Destructor for list class. */
{
    if (first == nullptr) { // Nothing to remove.
        return;
    }

    Node * prev = first;
    for (Node * iter = prev->next; iter != nullptr; iter=iter->next) {
        delete prev;
        prev = iter;
    }
    if (prev != nullptr) { // Delete last / single element.
        delete prev;
    }
}

bool List::exists(int d) const
    /* Return if int d exists in list or not. */
{
    for (Node * iter = first; iter != nullptr; iter = iter->next) {
        if (iter->value == d) {
            return true;
        }
    }
    return false;
}

int List::size() const
    /* Iterate through the list and count how long it is, return size. */
{
    int size = 0;
    for (Node * iter=first; iter != nullptr; iter=iter->next,++size);
    return size;
}

bool List::empty() const
    /* Return if the list is empty or not. */
{
	return first == nullptr;
}

void List::insertFirst(int d)
    /* Prepend Node with value d to the head of the list. */
{
    // If the list is empty, previous was null, otherwise take current.
    Node * prev_node = empty() ? nullptr : first;
    // Create new node with prev, make new first.
    Node * new_node = new Node(d, prev_node);
    first = new_node;
}

bool match(int a, int b, List::DeleteFlag df)
    /* Local compare functions that compares two values against flag and
     * returns boolean reflecting the comparison result. */
{
    switch(df) {
        case List::DeleteFlag::LESS: return a < b; break;
        case List::DeleteFlag::EQUAL: return a == b; break;
        case List::DeleteFlag::GREATER: return a > b; break;
    }
    return false;
}

void List::remove(int d, DeleteFlag df)
    /* Remove item depending on the d and DeleteFlag parameters. */
{
    Node * prev = nullptr;
    for (Node * iter = first; iter != nullptr; iter = iter->next) {
        if (match(iter->value, d, df)) {
            if (prev == nullptr) { // First value matches.
                first = iter->next;
            } else { // Re-link with previous value.
                prev->next = iter->next;
            }
            delete iter;
            return;
        }
        prev = iter;
    }
}

void List::print() const
    /* Print the list. */
{
    std::cout << "[";
    for (Node * iter = first; iter != nullptr; iter = iter->next) {
        std::cout << iter->value;
        // Only print separators on all numbers except last.
        if (iter->next != nullptr) {
            std::cout << ",";
        }
    }
    std::cout << "]" << std::endl;
}

