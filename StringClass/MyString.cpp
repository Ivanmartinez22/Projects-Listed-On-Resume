// TODO: Implement this source file
// TODO: Implement this source file
#include "MyString.h"
#include <iostream>
using std::ostream;
using std::out_of_range;
MyString::MyString() : size_header(0) , capacity_header(1), str(new char[capacity_header]{}){}// default constructor 

MyString::MyString(const MyString& other) 
    :size_header(other.size_header) , capacity_header(other.capacity_header),str(new char[other.capacity_header]{}){
    for(unsigned int i = 0; i < size_header; i++){
        str[i] = other.str[i];
    }
} // copy constructor 

MyString::MyString(const char* copy) : size_header(0), capacity_header(1), str(new char[1]{}){ // temporary initializaion values
    size_t num_of_chars = 0;
    
    while(copy[num_of_chars] != '\0'){
        num_of_chars++;
    }
    // length_local += 1;
    char* temp = new char[num_of_chars + 1]{};
    for(size_t i = 0; i < (num_of_chars+1); i++){
        temp[i] = copy[i];
    }
    size_header = num_of_chars;
    capacity_header = num_of_chars + 1;
    delete[] str;
    str = temp;
} // from c-string constructor 

void MyString::resize(size_t n){
    if(n < size_header){
        size_header = n;
        capacity_header = n + 2;
        char* temp = new char[capacity_header]{};
        for(size_t i = 0; i < size_header; i++){
            temp[i] = str[i];
        }
        temp[n + 1] = '\0';
        delete[] str;
        str = temp;
    }
    else if(n > size_header){
        size_header = n;
        capacity_header = n *2;
        char* temp = new char[capacity_header]{};
        for(size_t i = 0; i < size_header; i++){
            temp[i] = str[i];
        }
        temp[n + 1] = '\0';
        delete[] str;
        str = temp;
    }
}

size_t MyString::capacity() const{
    return capacity_header;
}

size_t MyString::size() const{
    return size_header;
}

size_t MyString::length() const{
    return size_header;
}

const char* MyString::data() const{ // iffy
    return str;
}

bool MyString::empty() const{
    if(size_header == 0){
        return true;
    }
    else{
        return false;
    }
}

const char& MyString::front() const{ // iffy 
    if(!(size_header == 0)){
        return str[0];
    }
    else{
        throw out_of_range("Out of range");
    }

}

const char& MyString::at(size_t pos) const{
    if(pos < size_header){
        
        return str[pos];
    }
    else{
        throw out_of_range("Out of range");
    }
}

void MyString::clear(){
    delete[] str;
    str = new char[1]{};
    str[0] = '\0';
    size_header = 0;
    capacity_header = 1;
}

size_t MyString::find(const MyString& string, size_t pos) const{
    // implement 
    // string is the target to find 
    static const size_t npos = -1;
    char first_letter = string.str[0];
    size_t length_of_target = string.length();
    size_t return_value = 0;
    bool flag = true;
    for(size_t i = pos; i < size_header; i++){
        if(str[i] == first_letter){
            return_value = i;
            size_t iterator = i;
            //cout << "here 1" << endl;
            for(size_t j = 0; j < length_of_target; j++){
                //cout << "here 2" << endl;
                if(str[iterator] != string.str[j]){
                    //cout << "here 3" << endl;
                    flag = false;
                    break;
                }
                iterator++;
            }
            if(flag){
                return return_value;
            }
        }
    }
    return npos;
    
}

ostream& operator<<(ostream& out, MyString string) {
    for(size_t i = 0; i < string.size(); i++){
        out << string.at(i);
    }
    return out;
}

MyString& MyString::operator= (const MyString& other){
    char* temp = new char[other.size_header + 1];
    for(size_t i = 0; i < (other.size_header + 1); i++){
        temp[i] = other.str[i];
    }
    delete[] str;
    str = temp;
    size_header = other.size_header;
    capacity_header = other.capacity_header;
    
    return *this;
}

MyString& MyString::operator+= (const MyString& other){
    size_t other_length = other.size_header;
    size_t new_length = other_length + size_header + 1;
    
    
    // string.str[string_length] = str[0];
    char* temp = new char[new_length]{};
    for(size_t i = 0; i < size_header; i++){
        temp[i] = str[i];
    }
    for(size_t i = (size_header); i < (new_length); i++){
        temp[i] = other.str[i - size_header];
    }
    size_header = new_length - 1;
    capacity_header = size_header + 1;
    delete[] str;
    str = temp;
    return *this;
}


MyString::~MyString() {
    delete[] str;
    str = nullptr;
}