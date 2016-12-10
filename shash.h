#pragma once

/// TODO: complete this implementation of a thread-safe (concurrent) hash
///       table of integers, implemented as an array of linked lists.  In
///       this implementation, each list should have a "sentinel" node that
///       contains the lock, so we can't just reuse the clist implementation
class shash {
  private:
    
    struct node
    {
      int value;
      node* next;
    };

    struct sNode
    {
      std::mutex gate;
      node* head;
    };
  
    int len;
    sNode* bucket;

  public:
    bool og_insert(int key, node * head) { 
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

    bool og_remove(int key, node * head){
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

    bool og_lookup(int key, node * head){
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
    
    int getHash(int key){
      int i = (key % len);
      return i;
    }
    
    /// insert *key* into the appropriate linked list if it doesn't already
    /// exist; return true if the key was added successfully.
    bool insert(int key) { 
      int i = getHash(key);
      bucket[i].gate.lock();
      bool res = og_insert(key, bucket[i].head);
      bucket[i].gate.unlock();
      return res;
    }

    /// remove *key* from the appropriate list if it was present; return true
    /// if the key was removed successfully.
    bool remove(int key) {
      int i = getHash(key);
      bucket[i].gate.lock();
      bool res = og_remove(key, bucket[i].head);
      bucket[i].gate.unlock();
      return res;
    }
    /// return true if *key* is present in the appropriate list, false
    /// otherwise
    bool lookup(int key) {
      int i = getHash(key);
      bucket[i].gate.lock();
      bool res = og_lookup(key, bucket[i].head);
      bucket[i].gate.unlock();
      return res;
    }
    /// constructor code goes here
    shash(unsigned _buckets):len(_buckets) { 

      bucket = new sNode[len];
    }
  ~shash(){
    for(int i = 0; i < len; i++){
      node * next;
         node * temp = bucket[i].head;
         next = temp->next;
         while(next){
               delete(temp);
               temp = next;
               next = temp->next;
         }
         delete(temp);
    }
  }
};
