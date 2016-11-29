#pragma once

/// TODO: complete this implementation of a thread-safe (concurrent) sorted
/// linked list of integers, which should use readers/writer locking.
class rwlist {
    /// a node consists of a value and a pointer to another node
    struct node
    {
        int value;
        node* next;
    };

    /// The head of the list is referenced by this pointer
    node* head;

  public:
    /// insert *key* into the linked list if it doesn't already exist; return
    /// true if the key was added successfully.
    bool insert(int key) { return false; }
    /// remove *key* from the list if it was present; return true if the key
    /// was removed successfully.
    bool remove(int key) { return false; }
    /// return true if *key* is present in the list, false otherwise
    bool lookup(int key) { return false; }
    /// constructor code goes here
    rwlist(int): head(NULL) { }
};
