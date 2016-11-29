#include "clist.h"

#pragma once

/// TODO: complete this implementation of a thread-safe (concurrent) hash
///       table of integers, implemented as an array of linked lists.
class chash {
    /// The bucket list
    clist buckets[];

  public:
    /// insert *key* into the appropriate linked list if it doesn't already
    /// exist; return true if the key was added successfully.
    bool insert(int key) { return false; }
    /// remove *key* from the appropriate list if it was present; return true
    /// if the key was removed successfully.
    bool remove(int key) { return false; }
    /// return true if *key* is present in the appropriate list, false
    /// otherwise
    bool lookup(int key) { return false; }
    /// constructor code goes here
    chash(unsigned _buckets) { }
};
