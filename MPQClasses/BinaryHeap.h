#ifndef BINARYHEAP_H
#define BINARYHEAP_H

#include <stdexcept>
#include <iostream>
#include <vector>
#include <math.h>
using std::invalid_argument;
/*
 * Binary Heap class
 */
template <typename T>
class BinaryHeap {
    public:
        //Implement the below 4 methods. Please note these methods are not from MPQ.h
        //BinaryHeap class does not inherit MPQ class 
        //Implement BinaryHeap insert operation
        //Also implement upheap and downheap operations (functions provided below) and call them from wherever necessary
        void insert(const T& data){
            if(elements.empty()){
                elements.push_back(data);
                size++;
                return; 
            }
            elements.push_back(data);
            size++;
            int pos_new_element = elements.size() - 1;
            up_heap(pos_new_element);
        }
        // Return true if BinaryHeap is empty otherwise false
        bool is_empty(){
            return elements.empty();
        }
        // Return minimum element in the BinaryHeap
        T min(){
            if(elements.empty()){
                throw invalid_argument("Empty Queue");
            }
            return elements[0];
        }
        // Remove minimum element in the BinaryHeap and return it
        T remove_min(){
            if(elements.empty()){
                throw invalid_argument("Empty Queue");
            }
            T min = elements[0];
            swap(0,(elements.size()-1));
            elements.pop_back();
            size--;
            down_heap(0);
            return min;
        }
    private:
        //
        std::vector<T> elements;
        int size = 0;
        //Implement down heap operation
        void down_heap_helper(int i, T &parent_node);
        //Implement down heap operation
        void down_heap(int i);
        //Implement up heap operation
        void up_heap(int i);

        //Pre-implemented helper functions
        //swaps two elements at positions a and b
        void swap(int a, int b) { T c(elements[a]); elements[a] = elements[b]; elements[b] = c;}
        //Binary tree (Complete Binary tree) can be represented in vector form and hence, stored in a vector. 
        //Returns the right child index of current index
        int right_child(int i) {return 2*i + 2;}
        //Returns the left child index of current index
        int left_child(int i) {return 2*i + 1;}
        //Returns the parent index of current index
        int parent(int i) {return floor((i-1)/2);}
        //Checks if current index is an internal node
        bool is_internal(int i) {return left_child(i) < size || right_child(i) < size;}
        //Checks if current index is a leaf
        bool is_leaf(int i) {return left_child(i) >= size && right_child(i) >= size;}
};

/*
 * Restores the binary heap property starting from a node that is smaller than its parent
 */
template <typename T>
void BinaryHeap<T>::up_heap(int i){
    int parent_index = parent(i);
    /*
     * Can be computed iteratively or recursively
     */
    T parent_node = elements[parent_index];
    T data = elements[i];
    while(parent_node > data){
        //call upheap
        // a = i;
        // b = parent_index;
        swap(i, parent_index);
        i = parent_index;
        parent_index = parent(i); 
        data = elements[i];
        parent_node = elements[parent_index];
    }
}

/*
 * Restores the binary heap property starting from an node that is larger than its children
 */

template <typename T>
void BinaryHeap<T>::down_heap(int i){
    int child_index;
    T iterator = elements[i];
    for(;2*i+1 < elements.size(); i = child_index){
        child_index = left_child(i);
        if((child_index != (elements.size()-1)) && (elements[child_index]>elements[child_index+1])){
            child_index = right_child(i);
        }
        if(iterator > elements[child_index])
            elements[i] = elements[child_index];
        else
            break;
        
    }
    elements[i] = iterator;
}



#endif