#include <iostream>
#include <string>
#include "./string_calculator.h"

using std::cout;
using std::endl;
using std::string;

unsigned int digit_to_decimal(char digit) {
    /*
    convert a character digit to an integer value
    input: digit - a character representing a digit, e.g. '7'
    output: the corresponding integer value of the digit, e.g. 7
    throws: std::invalid_argument if the input is not a valid digit, e.g. '0' -- '9'
    */
    unsigned int return_value;
    if(digit == '0'){
        return_value = 0;
    }
    else if(digit == '1'){
        return_value = 1;
    }
    else if(digit == '2'){
        return_value = 2;
    }
    else if(digit == '3'){
        return_value = 3;
    }
    else if(digit == '4'){
        return_value = 4;
    }
    else if(digit == '5'){
        return_value = 5;
    }
    else if(digit == '6'){
        return_value = 6;
    }
    else if(digit == '7'){
        return_value = 7;
    }
    else if(digit == '8'){
        return_value = 8;
    }
    else if(digit == '9'){
        return_value = 9;
    }
    else{
        throw std::invalid_argument("Invalid Input1");
    }
    return return_value;
}

char decimal_to_digit(unsigned int decimal) {
    /*
    convert an integer value to a character digit
    input: decimal - an integer value of a digit, e.g. 7
    output: the corresponding character of the digit, e.g. '7'
    throws: std::invalid_argument if the input is not a valid decimal, e.g. 0 -- 9
    */
    char return_value;
    if(decimal == 0){
        return_value = '0';
    }
    else if(decimal == 1){
        return_value = '1';
    }
    else if(decimal == 2){
        return_value = '2';
    }
    else if(decimal == 3){
        return_value = '3';
    }
    else if(decimal == 4){
        return_value = '4';
    }
    else if(decimal == 5){
        return_value = '5';
    }
    else if(decimal == 6){
        return_value = '6';
    }
    else if(decimal == 7){
        return_value = '7';
    }
    else if(decimal == 8){
        return_value = '8';
    }
    else if(decimal == 9){
        return_value = '9';
    }
    else{
        throw std::invalid_argument("Invalid Input2");
    }
    return return_value;   
}




string trim_negative_and_zeros(string input_num) {
    /*
    remove the leading zeros from a number
    input: num - a string representing a number with zero or more leading 0s
    output: a copy of the input with all leading 0s removed
    throws: none 
    */
    string return_value;
    bool is_zero = false;
    while((input_num[0] == '0') || (input_num[0] == '-')){
        if(input_num.length() == 1){
            is_zero = true;
            break;
        }
        input_num.erase(input_num.begin());
    }
    if(is_zero == false){
        input_num.insert(0, "-");
        return_value = input_num;
    }
    else{
        return_value = input_num;
    }
    return return_value;
}


string trim_only_zeros(string input_num) {
    /*
    trims only the leading zeros 
    */
    string return_value;
    while(input_num[0] == '0'){
        if(input_num.length() == 1){
            break;
        }
        input_num.erase(input_num.begin());
    }
    return_value = input_num;
    return return_value;
}

string trim_leading_zeros(string input_num){
    string return_value;
    if(input_num[0] == '-'){
        return_value = trim_negative_and_zeros(input_num);
    }
    else{
        return_value = trim_only_zeros(input_num);
    }
    return return_value;
}


unsigned int char_counter(string input_num){
    // Determines length of a string after removing leading zeros 
    input_num = trim_leading_zeros(input_num);
    unsigned int length = input_num.length();
    return length;
}

string top_string(string a, string b){
    // Determines the "top" string 
    string new_a = trim_leading_zeros(a);
    string new_b = trim_leading_zeros(b);
    string top = new_a;
    string bottom = new_b;
    if(char_counter(new_a) < char_counter(new_b)){
        top = new_b;
        bottom = new_a;
    }
    return top;
}

string bottom_string(string a, string b){
    // Determines "bottom" string 
    string new_a = trim_leading_zeros(a);
    string new_b = trim_leading_zeros(b);
    string top = new_a;
    string bottom = new_b;
    if(char_counter(new_a) < char_counter(new_b)){
        top = new_b;
        bottom = new_a;
    }
    return bottom;
}

string adding_zeros_to_bottom_string(string a, string b){
    // Adds zeros to bottom number
    string return_value;
    string bottom = bottom_string(a, b);
    string top = top_string(a, b);
    if(char_counter(bottom) < char_counter(top)){
        unsigned int number_of_zeros = char_counter(top) - char_counter(bottom);
        unsigned int counter = 0;
        while(counter != number_of_zeros){
            bottom.insert(0, "0");
            counter++;  
        }
        return_value = bottom;
    }
    else{
        return_value = bottom;
    }
    return return_value;
} 

string add(string lhs, string rhs) {
    /*
    add two numbers 
    input: lhs,rhs - strings representing numbers, e.g. "1", "2"
    output: the result of adding rhs to lhs: lhs + rhs e.g. "3"
    throws: none.
    */
    string return_value;
    string negative_sign = "-";
    bool is_negative;
    if((lhs[0] == '-') && (rhs[0] == '-')){
        is_negative = true;
        lhs.erase(lhs.begin());
        rhs.erase(rhs.begin());
    }
    else if((lhs[0] != '-') && (rhs[0] != '-')){
        is_negative = false;
    }
    else{
        throw std::invalid_argument("Invalid Input3");
    }
    string top = top_string(lhs, rhs);
    string bottom = adding_zeros_to_bottom_string(lhs, rhs);
    unsigned int length = char_counter(top);
    unsigned int index = length;
    string sum = "";
    unsigned int carry = 0;
    while(index != 0){
        index--;
        char alpha = top[index];
        char beta = bottom[index];
        unsigned int a = digit_to_decimal(alpha);
        a += carry;
        unsigned int b = digit_to_decimal(beta);
        unsigned int sum_int = a + b;
        if(sum_int >= 10){
            carry = 1;
            sum_int %= 10;
        }
        else{
            carry = 0;
        }
        char sum_chr = decimal_to_digit(sum_int);
        string sum_str = "";
        sum_str += sum_chr;
        sum.insert(0, sum_str);
    }
    char carry_chr = decimal_to_digit(carry);
    string carry_str = "";
    carry_str += carry_chr;
    sum.insert(0, carry_str);
    return_value = trim_leading_zeros(sum);
    if(is_negative == true){
        return_value.insert(0, negative_sign);
    }
    return return_value;
}

string multiply(string lhs, string rhs) {
    string negative_sign = "-";
    bool is_negative;
    if((lhs[0] == '-') && (rhs[0] == '-')){
        is_negative = false;
        lhs.erase(lhs.begin());
        rhs.erase(rhs.begin());
    }
    if((lhs[0] != '-') && (rhs[0] != '-')){
        is_negative = false;
    }
    if((lhs[0] != '-') && (rhs[0] == '-')){
        is_negative = true;
        rhs.erase(rhs.begin());
    }
    if((lhs[0] == '-') && (rhs[0] != '-')){
        is_negative = true;
        lhs.erase(lhs.begin());
    }
    string return_value;
    string top = top_string(lhs, rhs);
    string bottom = adding_zeros_to_bottom_string(lhs, rhs);
    unsigned int index = char_counter(top) - 1;
    unsigned int index_copy = index;
    unsigned int bottom_index = char_counter(top) - 1;
    unsigned int counter = (index + 1 ) * (index + 1);
    unsigned int starting_point = 0;
    unsigned int counter_of_zeros = starting_point;
    string product = "0";
    while(counter != 0){
        string product_str;
        string carry_str;
        unsigned int carry = 0;
        char alpha = top[index];
        char beta = bottom[bottom_index];
        unsigned int a = digit_to_decimal(alpha);
        unsigned int b = digit_to_decimal(beta);
        unsigned int product_int = a * b;
        if(product_int >= 10){
            carry = product_int / 10;
            product_int %= 10;
            carry_str += "0";
        }
        else{
            carry = 0;
        }
        char carry_chr = decimal_to_digit(carry);
        string carry_chr_str = "";
        carry_chr_str += carry_chr;
        carry_str.insert(0, carry_chr_str);
        for(unsigned int i = 0; i < counter_of_zeros; i++){
            carry_str += "0";
        }
        product = add(product, carry_str);
        char product_chr = decimal_to_digit(product_int);
        string product_chr_str = "";
        product_chr_str += product_chr;
        for(unsigned int i = 0; i < counter_of_zeros; i++){
            product_chr_str += "0";
        }
        product = add(product, product_chr_str);
        counter_of_zeros++;
        if(index == 0){
            index = index_copy + 1;
            bottom_index--;
            starting_point++;
            counter_of_zeros = starting_point;
        }
        index--;
        counter--;
    }
    if(is_negative == true){
        negative_sign += product;
        return_value = negative_sign;
    }
    else{
        return_value = product;
    }
    return return_value;
}
