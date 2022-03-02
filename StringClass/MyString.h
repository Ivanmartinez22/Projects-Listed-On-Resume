// TODO: Implement this header file
#ifndef _MYSTRING_H
#define _MYSTRING_H
#include <iostream>
using std::ostream;
class MyString {
private:
    size_t size_header; // number of characters 
    size_t capacity_header; // number of items i.e characters and null char
    char* str;
public:
    MyString();
    MyString(const MyString& other);
    MyString(const char* copy);
    ~MyString();
    void resize (size_t n);
    size_t capacity() const;
    size_t size() const;
    size_t length() const;
    const char* data() const;
    bool empty() const;
    const char& front() const;
    const char& at(size_t pos) const;
    void clear();
    size_t find (const MyString& string, size_t pos = 0) const;
    MyString& operator= (const MyString& other);
    MyString& operator+= (const MyString& other);
    
};

ostream& operator<< (ostream& out, MyString string);

#endif

