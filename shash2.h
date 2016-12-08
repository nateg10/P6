#pragma once
#include <mutex>
#include <iostream>

/// TODO: complete this implementation of a thread-safe (concurrent) hash
///       table of integers, implemented as an array of linked lists.  In
///       this implementation, each list should have a "sentinel" node that
///       contains the lock, so we can't just reuse the clist implementation.
///       In addition, the API now allows for multiple keys on each
///       operation.

using namespace std;

class shash2 {
  
  
 private:
  
  struct node{
    int value;
    node* next;
  };

  struct sNode
  {
    std::mutex gate;
    node* head;
  };

  sNode **buckets;

  int len;

  public:

  bool og_insert(int key, node* head){
    node *temp;
    node *prev;
    if(head){
      temp = head;
      if(temp->value == key)return false;
    }
    else{
      head = new node();
      head->value = key;
      return true;
    }

    prev = temp;
    while(temp->next){
      prev = temp;
      temp = temp->next;
      if(temp->value == key) return false;
      else if(temp->value > key){
	node * mynode = new node();
	mynode->value = key;
	prev->next = mynode;
	mynode->next = temp;
	return true;
      }
    }

    if(temp->value == key)return false;
    else{
      node * mynode = new node();
      mynode->value = key;
      temp->next = mynode;
      //mynode->next = temp;                                          
    }
    return true;
  }

  bool og_remove(int key, node* head){
    node *temp;

    if(head){
      temp = head;
      if(temp->value == key){
	head = head->next;
	delete(temp);
	return true;
      }
    }else{
      return false;
    }

    while(temp->next){
      node * prev = temp;
      temp = temp->next;
      if(temp->value == key){
	prev->next = temp->next;
	delete(temp);
	return true;
      }
      else if(temp->value > key){
	return false;
      }
    }

    return false;

  }

  bool og_lookup(int key, node* head){
    node *temp;
    
    if(head){
      temp = head;
      if(temp->value == key)return true;
    }else{
      return false;
    }
    
    while(temp->next){
      node * prev = temp;
      temp = temp->next;
      if(temp->value == key){
	return true;
      }
      else if(temp->value > key){
	return false;
      }
    }
    
    return false;
  }
  

  static int compare(const void *a, const void *b){
    return ( *(int*)a - *(int*)b );
  }

  int getHash(int key){
    return key % len;
  }
  //1. Get an array of all the keys' index values
  //2. Sort this list
  //3. Acquire the locks for all of these lists in the sentinal node
  //4. call the og_insert function in order
  bool *insert(int* keys, bool* results, int num) {
    //cout << "Insert" << endl;
    int indexVals[num];
    // 1.
    for(int x = 0; x < num; x++){
      indexVals[x] = getHash(keys[x]);
    }
    //2.
    qsort(indexVals, num, sizeof(int), compare);
    /*
    for(int i = 0; i < num; i++){
      cout << indexVals[i] << endl;
    }
    */
    //3.
    int last = -1;
    for(int x = 0; x < num; x++){
      if(last == indexVals[x]){
	continue;
      }
      last = indexVals[x];
      //cout << "Insert " << indexVals[x] << endl;
      buckets[indexVals[x]]->gate.lock();
    }
    //4.
    for(int x = 0; x < num; x++){
      results[x] = og_insert(keys[x], buckets[indexVals[x]]->head);
    }
    for(int x = 0; x < num; x++){
      buckets[indexVals[x]]->gate.unlock();
    }
    return results;

  }
   
  bool * remove(int* keys, bool* results, int num) { 
    //cout << "Remove" << endl;
    int indexVals[num];
    // 1.                                                              
    for(int x = 0; x < num; x++){
      indexVals[x] = getHash(keys[x]);
    }
    //2.                                                               
    qsort(indexVals, num, sizeof(int), compare);
    //3.
    int last = -1;
    for(int x = 0; x < num; x++){
      if(last == indexVals[x]){
	continue;
      }
      last = indexVals[x];
      //cout << "Remove " << indexVals[x] << endl;
      buckets[indexVals[x]]->gate.lock();
    }
    //4.                                                               
    for(int x = 0; x < num; x++){
      results[x] = og_insert(keys[x], buckets[indexVals[x]]->head);
    }
    for(int x = 0; x < num; x++){
      buckets[indexVals[x]]->gate.unlock();
    }
    return results;
  }
   

  bool * lookup(int* keys, bool* results, int num) { 
    //cout << "Lookpup " << endl;
    int indexVals[num];
    // 1.                                                            
    for(int x = 0; x < num; x++){
      indexVals[x] = getHash(keys[x]);
    }
    //2.                                                             
    qsort(indexVals, num, sizeof(int), compare);
    //3.
    int last = -1;
    for(int x = 0; x < num; x++){
      if(last == indexVals[x]){
	continue;
      }
      last = indexVals[x];
      //cout << "Lookup " << indexVals[x] << endl;
      buckets[indexVals[x]]->gate.lock();
    }
    //4.                                                             
    for(int x = 0; x < num; x++){
      results[x] = og_insert(keys[x], buckets[indexVals[x]]->head);
    }
    for(int x = 0; x < num; x++){
      buckets[indexVals[x]]->gate.unlock();
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
