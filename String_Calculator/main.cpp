#include <iostream>
#include <string>
#include <limits>
#include "./string_calculator.h"

using std::cout;
using std::endl;
using std::cin;
using std::string;

int main(){
    cout << "String Calculator" << endl;
    cout << "\"q\" or \"quit\" or ctrl+d to exit" << endl;
    string input;
    string operation;
    string answer;
    while(true){
        string lhs = "";
        string rhs = "";
        getline(cin, input);
        if((input == "q") || (input == "quit")){
            break;
        }
        unsigned int counter = 0;
        unsigned int string_length = input.length();
        unsigned int operation_position = 0;
        while(counter != string_length){
            counter++;
            if((input[counter] == '+' ) || (input[counter] == '*')){
                operation_position = counter;
                if(input[counter] == '+'){
                    operation = "+";
                }
                if(input[counter] == '*'){
                    operation = "*";
                }
                counter = string_length;
            }
        }
        if(operation_position == 0){
            throw std::invalid_argument("Invalid Input 10");
            break;
        }
        counter = -1;
        unsigned int space_position = operation_position - 2;
        while(counter != string_length){
            counter++;
            lhs += input[counter];
            if(counter == space_position){
                counter = string_length;
            }
            
        }
        counter = operation_position + 1;
        unsigned int last_num = string_length - 1;
        while(counter != string_length){
            counter++;
            rhs += input[counter];
            if(counter == last_num){
                counter = string_length;
            }
        }
        if(operation == "+"){
            answer = add(lhs, rhs);
        }
        if(operation == "*"){
            answer = multiply(lhs, rhs);
        }
        cout << ">> " << endl;
        cout << "ans =" << endl;
        cout << endl;
        cout << "    " << answer << endl;
        cout << endl;
        
    }
    cout << ">> " << endl;
    cout << "farvel!" << endl;
    return 0;
}

