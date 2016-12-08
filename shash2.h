#include "clist"
#pragma once

/// TODO: complete this implementation of a thread-safe (concurrent) hash
///       table of integers, implemented as an array of linked lists.  In
///       this implementation, each list should have a "sentinel" node that
///       contains the lock, so we can't just reuse the clist implementation.
///       In addition, the API now allows for multiple keys on each
///       operation.
class shash2 {
  
  sNode **buckets;
  
 private:

  struct node{
    int value;
    node* next;
  };

  struct sNode
  {
    std::mutex gate;
    struct node* head;
  };
  
  int len;

  public:

  bool og_insert(int key, node* head){
    
  }

  bool og_remove(int key, node* head){
  }

  bool og_lookup(int key, node* head){
  }

  int compare(const void *a, const void *b){
    return ( *(int*)a - *(int*)b );
  }

  int getHash(int key){
    return key % len;
  }
  //1. Get an array of all the keys' index values
  //2. Sort this list
  //3. Acquire the locks for all of these lists in the sentinal node
  //4. call the og_insert function in order
  void insert(int* keys, bool* results, int num) {
    int indexVals[num];
    // 1.
    for(int x = 0; x < num; x++){
      indexVals[x] = getHash(keys[x]);
    }
    //2.
    qsort(indexValues, num, sizeof(int), compare);
    //3.
    for(int x = 0; x < num; x++){
      buckets[indexVals[x]].gate.lock();
    }
    //4.
    for(int x = 0; x < num; x++){
      results[x] = og_insert(keys[x], buckets[indexVals[x]].head);
    }
    return results;

  }
   
  void remove(int* keys, bool* results, int num) { 
    int indexVals[num];
    // 1.                                                              
    for(int x = 0; x < num; x++){
      indexVals[x] = getHash(keys[x]);
    }
    //2.                                                               
    qsort(indexValues, num, sizeof(int), compare);
    //3.                                                               
    for(int x = 0; x < num; x++){
      buckets[indexVals[x]].gate.lock();
    }
    //4.                                                               
    for(int x = 0; x < num; x++){
      results[x] = og_insert(keys[x], buckets[indexVals[x]].head);
    }
    return results;
  }
   

  void lookup(int* keys, bool* results, int num) { 
    int indexVals[num];
    // 1.                                                            
    for(int x = 0; x < num; x++){
      indexVals[x] = getHash(keys[x]);
    }
    //2.                                                             
    qsort(indexValues, num, sizeof(int), compare);
    //3.                                                            
    for(int x = 0; x < num; x++){
      buckets[indexVals[x]].gate.lock();
    }
    //4.                                                             
    for(int x = 0; x < num; x++){
      results[x] = og_insert(keys[x], buckets[indexVals[x]].head);
    }
    return results;
  }
  
    
 shash2(unsigned _buckets):len(_buckets) { 
      int x = 0;
      buckets = (sNode**)malloc(sizeof(sNode) * len);
      while(x < len){
	sNode *head = new sNode();
	buckets[x] = head;
	x++;
      }
    }
};
