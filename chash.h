#include "clist.h"
#include "rwlist.h"

#pragma once

/// TODO: complete this implementation of a thread-safe (concurrent) hash
///       table of integers, implemented as an array of linked lists.
class chash {

  //rwlist **buckets;
  clist *buckets;
  
  public:

  //clist *buckets;
    int len;


    int getHash(int key){
      int i = (key % len);
      return i;
      /*
      for(int i = 0; i < len; i++){
	printf("try: %i\n", ((key + i) % len));
	if((key + i)% len == 0){
	  return i;
	}
      }
      printf("Hash not found on\n");
      return 0;
      */
    }
    /// insert *key* into the appropriate linked list if it doesn't already
    /// exist; return true if the key was added successfully.
    bool insert(int key) { 
      printf("insert %i in %i ", key, getHash(key));
      fflush(stdout);
      
      bool res = buckets[getHash(key)]->insert(key);
      printf(" i\n");
      return res;
    }
    /// remove *key* from the appropriate list if it was present; return true
    /// if the key was removed successfully.
    
    bool remove(int key) {
      printf("remove %i in %i ", key, getHash(key));
      fflush(stdout);
      bool res = buckets[getHash(key)]->remove(key);
      printf(" r\n");
      return res;
    }
    /// return true if *key* is present in the appropriate list, false
    /// otherwise
    bool lookup(int key) {
      printf("lookup %i in %i ", key, getHash(key));
      fflush(stdout);
      bool res = buckets[getHash(key)]->lookup(key);
       printf(" l\n");
      return res;
    }
    /// constructor code goes here
 chash(unsigned _buckets):len(_buckets){
      int x = 0;

      //buckets = malloc(sizeof(clist) * len);
      buckets = new clist[len];
	
      while(x < _buckets){
	//rwlist *member = new rwlist(_buckets);
	clist member = new clist(_buckets);
	buckets[x] = member;
	x++;
      }

      printf("Num of buckets %i\n", len);
    }
};
