#ifndef SORTEDMPQ_H
#define SORTEDMPQ_H

#include <stdexcept>
#include <list>
#include "MPQ.h"
using std::list;
using std::invalid_argument;
/*
 * Minimum Priority Queue based on a linked list
 */
template <typename T>
class SortedMPQ: MPQ<T> {
   // Implement the four funtions (insert, is_empty, min, remove_min) from MPQ.h
   // To hold the elements use std::list
   // For remove_min() and min() throw exception if the SortedMPQ is empty. Mimir already has a try/catch block so don't use try/catch block here.
   private:
   list<T> listl;
   public:
   void insert(const T& data){
      if(listl.empty()){
         listl.push_back(data);
         return;
      }
      typename list<T> :: iterator i;
      for(i = listl.begin(); i != listl.end(); ++i){
         if(data < *i){
            listl.insert(i, data);
            return;
         }
         // ++i;
      }
      listl.push_back(data);
   }
   bool is_empty(){
      if(listl.empty()){
         return true;
      }
      else{
         return false;
      }
   }
   T min(){
      if(listl.empty()){
         throw invalid_argument("Empty Queue");
      }
      typename list<T> :: iterator i = listl.begin();
      return *i;
   }
   T remove_min(){
      if(listl.empty()){
         throw invalid_argument("Empty Queue");
      }
      typename list<T> :: iterator i = listl.begin();
      listl.pop_front();
      return *i;
      
      
   }
};

#endif