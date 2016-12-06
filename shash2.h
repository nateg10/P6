#include "clist"
#pragma once

/// TODO: complete this implementation of a thread-safe (concurrent) hash
///       table of integers, implemented as an array of linked lists.  In
///       this implementation, each list should have a "sentinel" node that
///       contains the lock, so we can't just reuse the clist implementation.
///       In addition, the API now allows for multiple keys on each
///       operation.
class shash2 {
  
  node **buckets;
  
 private:

  struct node{
    int value;
    node* next 
    std::mytex gate;
  };
  
  int len;

  public:

  bool og_insert(int key, node* head){
  }

  bool og_remove(int key, node* head){
  }

  bool og_lookup(int key, node* head){
  }


  int getHash(int key){
    return key % len;
  }
    /// insert /num/ values from /keys/ array into the hash, and return the
    /// success/failure of each insert in /results/ array.
    void insert(int* keys, bool* results, int num) {
      for(int x = 0; x < num; x++){
	int index = getHash(keys[x]);
	results[x] = og_insert(keys[x], buckets[index]);
	return res;
      }
    }
    /// remove *key* from the list if it was present; return true if the key
    /// was removed successfully.
    void remove(int* keys, bool* results, int num) { 
      for(int x = 0; x < num; x++){
        int index = getHash(keys[x]);
	results[x] = og_remove(keys[x], buckets[index]);
	return res;
      }
    }
    /// return true if *key* is present in the list, false otherwise
    void lookup(int* keys, bool* results, int num) { 
      for(int x = 0; x < num; x++){
        int index = getHash(keys[x]);
	results[x] = og_insert(keys[x], buckets[index]);
	return res;
      }
    }
    /// constructor code goes here
 shash2(unsigned _buckets):len(_buckets) { 
      int x = 0;
      buckets = (node**)malloc(sizeof(node) * len);
      while(x < len){
	node *head = new node(len);
	buckets[x] = member;
	x++;
      }
    }
};
