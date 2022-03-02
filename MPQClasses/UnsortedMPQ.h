#ifndef UNSORTEDMPQ_H
#define UNSORTEDMPQ_H

#include <stdexcept>
#include <vector>
#include "MPQ.h"
using std::vector;
using std::invalid_argument;
/**
 * Minimum Priority Queue based on a vector
 */
template <typename T>
class UnsortedMPQ: MPQ<T> {
   // Implement the four funtions (insert, is_empty, min, remove_min) from MPQ.h
   // To hold the elements use std::vector
   // For remove_min() and min() just throw exception if the UnsortedMPQ is empty. Mimir already has a try/catch block so don't use try/catch block here.
   private:
   vector<T> vec;
   public:
   void insert(const T& data){
      vec.push_back(data);
   }
   bool is_empty(){
      if(vec.empty()){
         return true;
      }
      else{
         return false;
      }
   }
   T min(){
      if(vec.size() == 0){
         throw invalid_argument("Empty Queue");
      }
      T min = vec[0];
      for(int i = 0; i < vec.size(); i++){
         if(vec[i] < min){
            min = vec[i];
         }
      }
      return min;
   }
   T remove_min(){
      if(vec.size() == 0){
         throw invalid_argument("Empty Queue");
      }
      T min = vec[0];
      int min_index = 0;
      for(int i = 0; i < vec.size(); i++){
         if(vec[i] < min){
            min = vec[i];
            min_index = i;
         }
      }
      vec[min_index] = vec[vec.size()-1];
      vec.pop_back();
      return min;
   }

};

#endif