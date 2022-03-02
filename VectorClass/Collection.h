/**
 * There is no Collection.cpp for this assignment.
 * Move all the functions from Collection.cpp to this file
 * Covert the Collection class to a templated form.
 *      Stress_ball should be replaced with typename "Obj".
 *      Stress_ball_colors
 *      Stress_ball_sizes should be replaced with typename "F2"
 */

#ifndef COLLECTION_H
#define COLLECTION_H
#include <exception>
#include <string>
#include <iostream>
 
using std::exception;
using std::cout;
using std::endl;
using std::string;
 
 
enum class Sort_choice
{
    bubble_sort,
    insertion_sort,
    selection_sort
};
 
 
 
 
 
struct EmptyCollectionException : public std::exception
{
    const char * what () const noexcept
    {
        return "Collection is Empty!";
    }
};
 
 
template<class Obj, typename F1,  typename F2> class Collection
{
 
    
    Obj *array;
    int size;
    int capacity;
    void resize();
 
public:
    Collection();
    Collection(const int cap);
    Collection(const Collection &c);
    Collection &operator=(const Collection &c);
    ~Collection();
    Collection(Collection &&c);
    Collection &operator=(Collection &&c);
    //bool operator==(const Obj &ob) const;
    void insert_item(const Obj &Ob);
    bool contains(const Obj &Ob) const;
    Obj remove_any_item();
    void remove_this_item(const Obj &Ob);
    void make_empty();
    bool is_empty() const;
    int total_items() const;
    int total_items(const F1 s) const;
    int total_items(const F2 c) const;
    void print_items() const;
    Obj &operator[](const int i);
    const Obj &operator[](const int i) const;
};



 
template<class Obj, typename F1,  typename F2>
std::istream &operator>>(std::istream &is, Collection<Obj, F1, F2> &c);
 
 
template<class Obj, typename F1,  typename F2>
std::ostream &operator<<(std::ostream &os, const Collection<Obj, F1, F2> &c);
 
template<class Obj, typename F1,  typename F2> 
Collection<Obj, F1, F2> make_union(const Collection<Obj, F1, F2> &c1, const Collection<Obj, F1, F2> &c2);
 
template<class Obj, typename F1,  typename F2>
void swap(Collection<Obj, F1, F2> &c1, Collection<Obj, F1, F2> &c2);
 
template<class Obj, typename F1,  typename F2>
void sort_by_size(Collection<Obj, F1, F2> &c, const Sort_choice sort);

 
 
template<class Obj, typename F1,  typename F2>
Collection<Obj, F1, F2>::Collection(){ // default constructor
    size = 0;
    capacity = 0;
    array = nullptr;
 
}
 
template<class Obj, typename F1,  typename F2>
Collection<Obj, F1, F2>::Collection(const int cap){ // parameterized constructor
    // cap describes the required capacity of
    // the Collection<Obj, F1, F2>. The array should be allocated with memory equal to cap
    // and capacity == cap
 
    
    array = new Obj[cap]; 
    // creates dynamic array with cap as size
    capacity = cap;
    size = 0;
}
 
template<class Obj, typename F1,  typename F2>
Collection<Obj, F1, F2>::Collection(const Collection<Obj, F1, F2> &c){ // copy constructor
// - copy the contents of c into this
    size = c.size;
    capacity = c.capacity;
    array = new Obj[capacity];
    for(int i = 0; i < c.size; i++){
        array[i] = c.array[i]; // array[i] = c.array[i]
    }
}
 
template<class Obj, typename F1,  typename F2>
Collection<Obj, F1, F2>& Collection<Obj, F1, F2>::operator=(const Collection<Obj, F1, F2> &c){ // copy assignment
// Copy Assignment -
// copy the contents of c into this. Be sure to not introduce memory leaks.
// • ~Collection<Obj, F1, F2>(); - Destructor - deallocate array, set size and capacity
// to 0
    if(this == &c){
        return *this;
    }   
    Obj* temp = new Obj[c.capacity];
    for(int i = 0; i < c.size; i++){
        temp[i] = c.array[i];
    }
    delete[] array;
    array = temp;
    size = c.size;
    capacity = c.capacity;
    return *this;
}
 
 
template<class Obj, typename F1,  typename F2>
Collection<Obj, F1, F2>::Collection(Collection<Obj, F1, F2> &&c){ // move constructor
// Move Constructor - move the contents
// of c into this. Return c to the same state as the default constructor.
    this->array = c.array;
    this->capacity = c.capacity;
    this->size = c.size;
    c.array = nullptr;
    c.capacity = 0;
    c.size = 0;
 
}
 
 
template<class Obj, typename F1,  typename F2>
Collection<Obj, F1, F2>& Collection<Obj, F1, F2>::operator=(Collection<Obj, F1, F2> &&c){ // move assignment 
// Move Assignment - move
// the contents of c into this. Return c to the same state as the default
// constructor. Be sure to not introduce any memory leaks.
 
    if(this == &c){
        return *this;
    }
    delete[] this->array;
    this->array = c.array;
    this->size = c.size;
    this->capacity = c.capacity;
    c.array = nullptr;
    c.size = 0;
    c.capacity = 0;
    return *this;
} 
 
 
template<class Obj, typename F1,  typename F2>
Collection<Obj, F1, F2>::~Collection<Obj, F1, F2>(){
    delete[] array;
    array = nullptr;
    size = 0;
    capacity = 0;
}
 
template<class Obj, typename F1,  typename F2>
void Collection<Obj, F1, F2>::insert_item(const Obj &obj){
    /* insert sb into the Collection<Obj, F1, F2>. If the Collection<Obj, F1, F2> is full, resize by doubling capacity and allocating
    more memory. Be sure to not introduce any memory leaks.
    */
//    if(capacity == 0){ // empty 
//        capacity = 1;
//        array = new Stress_ball[1];
//        array[0] = sb;
//        size = 1;
//        capacity = 1;
//     }
//     else if((size + 1) > capacity){ // needing more capacity 
//         int temp_cap = capacity;
//         capacity *= 2;
//         Stress_ball* temp = new Stress_ball[capacity];
//         for(int i = 0; i < temp_cap; i++){
//             temp[i] = array[i];
//         }
//         delete [] array;
//         array = temp;
//         array[size + 1] = sb;
//         size += 1;
 
//     }
//     else if(size < capacity){ // ample capacity but with items 
//         array[size + 1] = sb;
//         size += 1;
//     }
//     else if(size == 0){ // has capacity and no items 
//         array[0] = sb;
//         size += 1;
 
//     }
    if(size == capacity){
        capacity = capacity == 0 ? 1: capacity * 2;
        if(capacity == 0){
            capacity = 1;
            array = new Obj[1];
        }
        Obj* temp = new Obj[capacity];
        for(int i = 0; i < size; i++){
            temp[i] = array[i];
        }
        delete[] array;
        array = temp;
    }
    array[size++] = obj;
 
 
 
}
 
 
template<class Obj, typename F1,  typename F2>
bool Collection<Obj, F1, F2>::contains(const Obj &ob) const{
    for(int i = 0; i < size; i++){
        if(array[i] == ob){
            return true;
        }
    }
    return false;
 
}

// template<class Obj, typename F1,  typename F2>
// bool Collection<Obj, F1, F2>::operator==(const Obj &ob) const{ // copy assignment
//     Obj other = ob;
//     if((this->get_color() == other.get_color()) && (this->get_size() == other.get_size())){
//         return true;
//     }
//     else{
//         return false;
//     }
// }
 
 
template<class Obj, typename F1,  typename F2>
Obj Collection<Obj, F1, F2>::remove_any_item(){
    if(size == 0){
        throw std::invalid_argument("Empty array");
 
    }
     
    int random_index = rand() % size;
    Obj the_random = array[random_index];
    if(random_index == 0){ // beginning of array
        
        Obj* temp = new Obj[capacity];
        for(int i = 1; i < size; i++){
            temp[i] = array[i];
        }
        capacity -= 1;
        size -= 1;
        delete [] array;
        array = temp;
    }
    else if(random_index == size){ // end of array
        
        Obj* temp = new Obj[capacity];
        for(int i = 0; i < size - 1; i++){
            temp[i] = array[i];
        }
        capacity -= 1;
        size -= 1;
        delete [] array;
        array = temp;
    }
    else{ // in between case
        
        Obj* temp = new Obj[capacity];
        for(int i = 0; i < (random_index); i++){
            temp[i] = array[i];
        }
        for(int i = (random_index + 1); i < (size); i++){
            temp[i] = array[i];
        }
        size -= 1;
        capacity -=1;
        delete [] array;
        array = temp;
    }
    return the_random;
} 
 
 
template<class Obj, typename F1,  typename F2>
void Collection<Obj, F1, F2>::remove_this_item(const Obj &Ob){
    if(size == 0){
        throw std::invalid_argument("Empty array");
 
    }
    int specific_index;
    // int i = 0;
    // while( i < size){
    //     if(array[i] == sb){
    //         specific_index = i;
    //         break;
    //     }
    //     i++;
    // }
     for(int i = 0; i < size; i++){
        if(array[i] == Ob){
            specific_index = i;
 
        }
 
    }
    if(specific_index == 0){ // beginning of array
        Obj* temp = new Obj[capacity];
        for(int i = 1; i < size; i++){
            temp[i] = array[i];
        }
        size -= 1;
        capacity -= 1;
        delete [] array;
        array = temp;
    }
    else if(specific_index == size){ // end of array
        
        Obj* temp = new Obj[capacity];
        for(int i = 0; i < size - 1; i++){
            temp[i] = array[i];
        }
        capacity -= 1;
        size -= 1;
        delete [] array;
        array = temp;
    }
    else{ // in between case
        
        Obj* temp = new Obj[capacity];
        for(int i = 0; i < (specific_index); i++){
            temp[i] = array[i];
        }
        for(int i = (specific_index + 1); i < (size); i++){
            temp[i] = array[i];
        }
        size -= 1;
        capacity -= 1;
        delete [] array;
        array = temp;
    }
 
}
 
 
template<class Obj, typename F1,  typename F2>
void Collection<Obj, F1, F2>::make_empty(){
    size = 0;
    delete [] array;
    array = new Obj[capacity];
 
}
 
template<class Obj, typename F1,  typename F2>
bool Collection<Obj, F1, F2>::is_empty() const{
    if(size == 0){
        return true;
    }
    return false;
}
 
template<class Obj, typename F1,  typename F2>
int Collection<Obj, F1, F2>::total_items() const {
    return size;
}
 
 
template<class Obj, typename F1,  typename F2>
int Collection<Obj, F1, F2>::total_items(const F2 s) const {
 
    int counter = 0;
    for(int i = 0; i < size; i++){
        if(array[i].get_size() == s){
            counter++;
        }
    }
    return counter;
}
 
 
template<class Obj, typename F1,  typename F2>
int Collection<Obj, F1, F2>::total_items(const F1 c) const {
 
    int counter = 0;
    for(int i = 0; i < size; i++){
        if(array[i].get_color() == c){
            counter++;
        }
    }
    return counter;
}
 
 
template<class Obj, typename F1,  typename F2>
void Collection<Obj, F1, F2>::print_items() const{
    for(int i = 0; i < size; i++){
        cout << array[i] << endl;     
    }
}
 
 
template<class Obj, typename F1,  typename F2>
Obj& Collection<Obj, F1, F2>::operator[](const int i){
    Obj& ref = array[i];
    return ref;
}
 
 
template<class Obj, typename F1,  typename F2>
const Obj& Collection<Obj, F1, F2>::operator[](const int i) const{
    Obj& ref = array[i];
    return ref;
}
 
 
 
 
 
 
template<class Obj, typename F1,  typename F2>
std::istream &operator>>(std::istream &is, Collection<Obj, F1, F2> &c){
    Obj sb;
    string color;
    string size;
    while(is >> sb){
        
        c.insert_item(sb);
    }
    return is;
 
}
 
 
template<class Obj, typename F1,  typename F2>
std::ostream &operator<<(std::ostream &os, const Collection<Obj, F1, F2> &c){ // fix 
    for(int i = 0; i < c.total_items(); i++){
        os << c[i] << endl;
    }
    return os;
}
 
template<class Obj, typename F1,  typename F2>
Collection<Obj, F1, F2> make_union(const Collection<Obj, F1, F2> &c1, const Collection<Obj, F1, F2> &c2){
    
    int size1 = c1.total_items();
    int size2 = c2.total_items();
    int new_size = size1 + size2;
    Obj* list = new Obj[new_size];
    for(int i = 0; i < size1; i++){
        list[i] = c1[i];
    }
    int start_point = size1 - 1;
    for(int i = 0; i < size2; i++){
        start_point++;
        list[start_point] = c2[i];
        
    }
    Collection<Obj, F1, F2> new_Collection(new_size);
    for(int i = 0; i < new_size; i++){
 
       new_Collection.insert_item(list[i]);
        
    }
    delete[] list;
 
    return new_Collection;
} // fix
 
 
template<class Obj, typename F1,  typename F2>
void swap(Collection<Obj, F1, F2> &c1, Collection<Obj, F1, F2> &c2){
    Collection<Obj, F1, F2> temp1 = std::move(c1);
    c1 = std::move(c2);
    c2 = std::move(temp1);
}
 
 
template<class Obj, typename F1,  typename F2>
void sort_by_size(Collection<Obj, F1, F2> &c, const Sort_choice sort){
 
    switch(sort)
    {
    case Sort_choice::bubble_sort:
 
        for(int i = 0; i < c.total_items() - 1; i++){
            for(int j = 0; j < (c.total_items() - i - 1); j++){
                if(c[j].get_size() > c[j + 1].get_size()){
                    Obj temp = c[j];
                    c[j] = c[j + 1];
                    c[j+ 1] = temp;
                    
                }
            } 
        }
        break;
    case Sort_choice::insertion_sort:
        
        for(int i = 1; i < c.total_items(); i++){
            int j = i;
            while(j > 0 &&  c[i].get_size() < c[j-1].get_size()){
                c[j] = c[j - 1];

                j = j - 1;
            }

            c[j] = c[i];
        }
        break;
 
    case Sort_choice::selection_sort:
        for(int i = 0; i < c.total_items() - 1; i++){
            int index = i;
            for(int j = i + 1; j < c.total_items(); j++){
                if(c[j].get_size() < c[index].get_size()){
                    index = j;
                }
            }
            Obj temp = c[i];
            c[i] = c[index];
            c[index] = temp;
        }
        break;
    }
}
#endif