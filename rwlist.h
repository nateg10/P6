#pragma once

#include <pthread.h>

/// TODO: complete this implementation of a thread-safe (concurrent) sorted
/// linked list of integers, which should use readers/writer locking.
class rwlist {
    
    private:
    std::mutex readgate;
    std::mutex writegate;
    std::mutex gate;
    int readers;
    bool writing;

    pthread_rwlock_t  rwlock;
    

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
    bool og_insert(int key) { 
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
	    /*node *printNode;
	    printNode = head;
	    while(printNode){
	      printf("%i->", printNode->value);
	      printNode = printNode->next;
	      }*/
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

    bool insert(int key){
      //printf("Inserting %i\n", key);
      int e;
      while((e = pthread_rwlock_trywrlock(&rwlock))){
            if(e != EBUSY){
                  printf("ERROR: inserting %i erron num %i", key, e);
                  return false;
            }
      }
      //printf("Inserting %i\n", key);
          bool result = og_insert(key);
          pthread_rwlock_unlock(&rwlock);
          return result;
    }

    bool og_remove(int key){
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
    /// remove *key* from the list if it was present; return true if the key
    /// was removed successfully.
    bool remove(int key) {
      int e;
      while((e = pthread_rwlock_trywrlock(&rwlock))){
            if(e != EBUSY){
                  printf("ERROR: removing %i erron num %i", key, e);
                  return false;
            }
      }
      //printf("Removing %i\n", key);
	  bool result = og_remove(key);
          pthread_rwlock_unlock(&rwlock);
          return result;
    }

    bool og_lookup(int key){
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

    /// return true if *key* is present in the list, false otherwise
    bool lookup(int key) {
      //printf("Looking up %i\n", key);
          int e;
          while((e = pthread_rwlock_tryrdlock(&rwlock))){
                if(e != EBUSY){
                  printf("ERROR: lookingup %i erron num %i", key, e);
                  return false;
            }
          }
	  //printf("Looking up %i\n", key);
          bool result = og_lookup(key);
          pthread_rwlock_unlock(&rwlock);
          return result;
    }
    /// constructor code goes here
    rwlist(int): head(NULL) {
        rwlock = PTHREAD_RWLOCK_INITIALIZER;
     }
     ~rwlist(){
           node * next;
         node * temp = head;
         next = temp->next;
         while(next){
               delete(temp);
               temp = next;
               next = temp->next;
         }
         delete(temp);
     }
};
