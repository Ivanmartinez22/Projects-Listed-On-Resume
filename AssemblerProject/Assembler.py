# // File: Assembler.py
# // Author: Ivan Martinez
# // Date: 11/05/2021
# // Section: 505
# // E-mail: Ivanattexas@tamu.edu 
# // Description:
# //The content of this file implements a hack assembler
# //I only used one file for this program so I am not putting a main function in because I feel it is not needed
# //When running the program on my computer/terminal(ubunto) I used the command python3 Assembler.py prog.asm and the file prog.hack is created in the same folder
# // The program takes input from command line when compiling(interpretting) e.i. python3 Assembler.py prog.asm
import sys 
import re
#Input from command line
filename = sys.argv[1]
#@address instruction handling 
def string_to_binary16(str):
  num = int(str)
  binary = '{0:015b}'.format(num)
  return "0" +  binary

Destination_dictionary = {"D": "010","M":"001", "null":"000", "MD":"011", "A":"100", "AM":"101","AD":"110", "AMD":"111"}
Jump_dictionary = {"JEQ": "010","JGT":"001", "null":"000", "JGE":"011", "JLT":"100", "JNE":"101","JLE":"110", "JMP":"111"}
comp_a_dictionary = {"0":"0", "1":"0", "-1":"0"
, "D":"0", "A":"0","!D":"0", "!A":"0", 
"-D":"0","-A":"0", "D+1":"0","A+1":"0",
"D-1":"0","A-1":"0","D+A":"0","D-A":"0","A-D":"0","D&A":"0","D|A":"0","M":"1", "!M":"1", "-M":"1",
"M+1":"1", "M-1":"1", "D+M":"1", "D-M":"1", "M-D":"1", "D&M":"1","D|M":"1"}

comp_dictionary = {"0":"101010", "1":"111111", "-1":"111010"
, "D":"001100", "A":"110000","!D":"001101", "!A":"110001", 
"-D":"001111","-A":"110011", "D+1":"011111","A+1":"110111",
"D-1":"001110","A-1":"110010","D+A":"000010","D-A":"010011","A-D":"000111","D&A":"000000","D|A":"010101","M":"110000", "!M":"110001", "-M":"110011",
"M+1":"110111", "M-1":"110010", "D+M":"000010", "D-M":"010011", "M-D":"000111", "D&M":"000000","D|M":"010101" }
# overall_dictionary = {"D": "010","M":"001", "null":"000", "MD":"011", "A":"100", "AM":"101","AD":"110", "AMD":"111", "JEQ": "010","JGT":"001", "null":"000", "JGE":"011", "JLT":"100", "JNE":"101","JLE":"110", "JMP":"111","0":"101010", "1":"111111", "-1":"111010"
# , "D":"001100", "A":"110000","!D":"001101", "!A":"110001", 
# "-D":"001111","-A":"110011", "D+1":"011111","A+1":"110111",
# "D-1":"001110","A-1":"110010","D+A":"000010","D-A":"010011","A-D":"000111","D&A":"000000","D|A":"010101","M":"110000", "M!":"110001", "-M":"110011",
# "M+1":"110111", "M-1":"110010", "D+M":"000010", "D-M":"010011", "M-D":"000111", "D&M":"000000","D|M":"010101"}
symbol_dictionary = {"R0":"0","R1":"1","R2":"2","R3":"3","R4":"4","R5":"5","R6":"6","R7":"7","R8":"8","R9":"9","R10":"10","R11":"11","R12":"12","R13":"13","R14":"14","R15":"15",
"SP":"0","LCL":"1","ARG":"2","THIS":"3","THAT":"4","SCREEN":"16384","KBD":"24576"}

#File opener 
strings = []
with open(filename, "r") as f:
  for x in f.read().split('\n'):
    strings.append(x)

keep = filename.split('.')
#Removing empty lines and comment only lines 

strings_chopped = []
binary_strings = []





length = len(strings)
for i in range(length):
  if(strings[i] != "" and strings[i][0] != '/'):
      strings_chopped.append(strings[i])
#Removing white and comments 
length = len(strings_chopped)
for i in range(length):
  strings_chopped[i] = strings_chopped[i].replace(' ', '')
  commentstart = strings_chopped[i].find("//")
  if(commentstart != -1):
    strings_chopped[i] = strings_chopped[i][0:commentstart]



strings_no_labels = []
length = len(strings_chopped)
iterator = 0
for i in range(length):
  if(strings_chopped[i][0]!='('):
    strings_no_labels.append(strings_chopped[i])
    iterator = iterator + 1
  else:
    symbol_dictionary[strings_chopped[i][1:(len(strings_chopped[i])-1)]] = str(iterator)

#Conversion to binary strings 
starting_address = 15
length = len(strings_no_labels)
for i in range(length):
  #A instructions and symbols
  if(strings_no_labels[i][0] == '@'):
    #print(strings_no_labels[i])
    if(strings_no_labels[i][1].isnumeric()):
      binary_strings.append(string_to_binary16(strings_no_labels[i][1:]))
    else:
      if strings_no_labels[i][1:] in symbol_dictionary:
        binary_strings.append(string_to_binary16(symbol_dictionary.get(strings_no_labels[i][1:])))
      else:
        starting_address = starting_address + 1
        value_to_dict = str(starting_address)
        key_to_dict = strings_no_labels[i][1:]
        symbol_dictionary[key_to_dict] = value_to_dict
        binary_strings.append(string_to_binary16(symbol_dictionary.get(strings_no_labels[i][1:])))
  #C instructions 
  else:
    equal_pos = strings_no_labels[i].find('=')
    semi_colon_pos = strings_no_labels[i].find(';')
    #No semi colon case
    if(semi_colon_pos == -1 and equal_pos != -1):
      two_parts = strings_no_labels[i].split('=')
      two_parts.append('null')
      dest_str = two_parts[0]
      comp_str = two_parts[1]
      jump_str = two_parts[2]
      #print(dest_str + " " + comp_str + " " + jump_str)
      bin_str = "111"
      a_str = comp_a_dictionary.get(comp_str)
      bin_str+=a_str
      
      bin_str += comp_dictionary.get(comp_str)
      bin_str += Destination_dictionary.get(dest_str)
      bin_str += Jump_dictionary.get(jump_str)
      binary_strings.append(bin_str)
      #print(bin_str)
    #No equal case 
    elif(equal_pos == -1 and semi_colon_pos != -1):
      two_parts = strings_no_labels[i].split(';')
      comp_str = two_parts[0]
      jump_str = two_parts[1]
      #print("null" + " " + comp_str + " " + jump_str) 
      bin_str = "111"
      a_str = comp_a_dictionary.get(comp_str)
      bin_str+=a_str
      
      bin_str += comp_dictionary.get(comp_str)
      bin_str += Destination_dictionary.get("null")
      bin_str += Jump_dictionary.get(jump_str)
      binary_strings.append(bin_str)
      #print(bin_str)
    #equal and semi colon case
    elif(equal_pos != -1 and semi_colon_pos != -1):
      two_parts = strings_no_labels[i].split('=')
      dest_str = two_parts[0]
      third_part = two_parts[1].split(';')
      comp_str = third_part[0]
      jump_str = third_part[1]
      #print(dest_str + " " + comp_str + " " + jump_str)
      bin_str = "111"
      a_str = comp_a_dictionary.get(comp_str)
      bin_str+=a_str 
      
      bin_str += comp_dictionary.get(comp_str)
      bin_str += Destination_dictionary.get(dest_str)
      bin_str += Jump_dictionary.get(jump_str)
      binary_strings.append(bin_str)
      #print(bin_str)




  

  






#Print
# length = len(strings_chopped)
# for i in range(length):
#   print(strings_chopped[i] +"  index:"+ str(i))


# length = len(binary_strings)
# for i in range(length):
#   print(binary_strings[i])

#File write 

f = open(keep[0] + ".hack", "w")
length = len(binary_strings)
for i in range(length):
  f.write(binary_strings[i] + '\n')

f.close()  