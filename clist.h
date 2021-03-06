#pragma once
#include <mutex>
#include <iostream>

using namespace std;
/// TODO: complete this implementation of a thread-safe (concurrent) sorted
/// linked list of integers
class clist {
    /// a node consists of a value and a pointer to another node
 private:
  std::mutex gate;

  std::string nobody = "Lock is Free";
  std::string whoHasLock;

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
      //printf("INSERTING %i\n", key);
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
          while(!gate.try_lock()){
	    //cout << whoHasLock << endl;
          }
          whoHasLock = "insert";
          bool result = og_insert(key);
          gate.unlock();
          whoHasLock = "nobody";
          return result;
    }

    bool og_remove(int key){
      //printf("REMOVING %i", key);
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
          while(!gate.try_lock()){
	    //cout << whoHasLock << endl;
	    
          }
          whoHasLock = "remove";
          bool result = og_remove(key);
          whoHasLock = "nobody";
          gate.unlock();
          return result;
    }

    bool og_lookup(int key){
      //printf("LOOKING FOR %i", key);
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
          while(!gate.try_lock()){
	    //cout << whoHasLock << endl;
	    
          }
          whoHasLock = "lookup";
          bool result = og_lookup(key);
          whoHasLock = "nobody";
          gate.unlock();
          return result;
    }
    /// constructor code goes here
    //clist(int): head(NULL) {
 clist(unsigned int&): head(NULL) {

    }
   ~clist(){
         node * next;
         node * temp = head;
         if(temp == NULL){
               return;
         }
         next = temp->next;
         while(next){
               delete(temp);
               temp = next;
               next = temp->next;
         }
         delete(temp);
   }
};
