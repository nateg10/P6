#include "clist.h"

#pragma once

/// TODO: complete this implementation of a thread-safe (concurrent) hash
///       table of integers, implemented as an array of linked lists.
class chash {

  public:

    clist **buckets;
    int len;


    int getHash(int key){
      for(int i = 0; i < key; i++){
	if((key + i)% len == 0){
	  return i;
	}
      }
      return 0;
    }
    /// insert *key* into the appropriate linked list if it doesn't already
    /// exist; return true if the key was added successfully.
    bool insert(int key) { 
      return buckets[getHash(key)]->insert(key);
    }
    /// remove *key* from the appropriate list if it was present; return true
    /// if the key was removed successfully.
    
    bool remove(int key) { 
      return buckets[getHash(key)]->remove(key);
    }
    /// return true if *key* is present in the appropriate list, false
    /// otherwise
    bool lookup(int key) { 
      return buckets[getHash(key)]->lookup(key);
    }
    /// constructor code goes here
 chash(unsigned _buckets):len(_buckets){
      int x = 0;

      buckets = malloc(sizeof(clist *) * len);

      while(x < _buckets){
	clist *member = new clist(_buckets);
	buckets[x] = member;
	x++;
      }
    }
};
