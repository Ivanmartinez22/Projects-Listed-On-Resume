# // File: cachesimulator.py
# // Author(s): Ivan Martinez
# // Date: 12/8/2021
# // Section: 505
# // E-mail(s): ivanattexas@tamu.edu 
# // Description:
# // e.g., The content of this file implements the cache simulator control menu and functions 

from os import write
import sys 
import math
from line import line
from cache import cache
from set import set
import random
filename = sys.argv[1] # command line input

from collections import OrderedDict

ram_string = [] #data appended to array



#---------------------------------------------
#Data collection code 
memory_size = 0
with open(filename, "r") as f:
  for x in f.read().split('\n'):
    ram_string.append(x)
    memory_size += 1
#---------------------------------------------

#cache formula functions 

## this function computes the number of set index bits 
def number_of_set_index_bits(num_of_sets):
    return math.log(num_of_sets, 2)
## this function computes the number of block offset bits 
def number_of_block_offset_bits(Block_size):
    return math.log(Block_size, 2)
## this function finds the range of a specefied address in realtion to memory view 
def cache_range_find(address):
    address_int = int(address, 16)
    if(address_int == 0):
        return [0,8]
    if(address_int % 8 == 0):
        return [address_int,address_int+8]
    while(address_int % 8 != 0):
        address_int += 1
    end_num = address_int
    start_num = end_num - 8
    return_list = [start_num,end_num]
    return return_list
## this function finds the range of a specefied address in int format in realtion to memory view
def cache_range_find_int(address_int):
    if(address_int == 0):
        return [0,8]
    if(address_int % 8 == 0):
        return [address_int,address_int+8]
    while(address_int % 8 != 0):
        address_int += 1
    end_num = address_int
    start_num = end_num - 8
    return_list = [start_num,end_num]
    return return_list
#-------------------------------------------------------------------------------------------------------
#cache control functions 
## function to view the memory of the ram 
def memory_view():
    # print("memory-view")
    print("memory_size:" + str(memory_size))
    print("memory_content:")
    print("address:data")
    index = 0
    for i in range(int(memory_size/8)):
        output = "0x%X" % index
        if(len(output) != 4):
            output += "0"
        output += ": "
        for j in range(index, (index+8)):
            output += ram_init[j]
            output += " "
        index += 8
        print(output)
## function to write ram contents into a .txt file 
def memory_dump():
    # print("memory-dump")
    f = open("ram.txt", "w")
    for i in range(len(ram_init)):
        f.write(str(ram_init[i]) + '\n')
    f.close()

##this function evicts lines based on replacement policy and returns the eviction line number. It takes lines from a set as input as well as the binary number of the set, number of block bits, new write line and hexadecimal address.
def eviction(set_lines,set_bin,block_bits,tag_loc,this_line,address_output):
    if(main_cache.replacement == 1):
        tags = []
        #code for Random replacement
        #iterate through lines and write dirty lines to ram also append tags to tag list
        #choose random number from 0 to len(tags) - 1
        #tags[random_num] is the tag to be removed 
        #del line at tag to be removed
        #add new line 
        # return evicted line num 
        for i in set_lines: # dirty bit line writing
            tags.append(i)
            if(set_lines[i].dirty == "1"):
                set_lines[i].dirty = "0"
                the_tag = "0x" + i
                tag_num = int(the_tag, 16)
                bin_tag = bin(tag_num)
                bin_tag = bin_tag[2:]
                while(len(bin_tag)!=block_bits):
                    bin_tag = "0" + bin_tag
                address_bin = bin_tag + set_bin
                while(len(address_bin)!=8):
                    address_bin = address_bin + "0"
                address_int = int(("0b"+address_bin),2)

                range_list = cache_range_find_int(address_int)
                start = range_list[0]
                end = range_list[1]
                index = 0
                for j in range(start,end):
                    ram_init[j] = set_lines[i].byte_blocks[index] 
                    index += 1
        #block size of 1 case
        if(main_cache.num_lines == 1):
            del set_lines[tags[0]]
            selector = tags[0]
            selector = "0x" + selector
            evicted_line_num = int(selector, 16)
        else: #randon line selection
            selector = random.choice(tags)
            del set_lines[selector]
            selector = "0x" + selector
            evicted_line_num = int(selector, 16)
        set_lines[tag_loc] = this_line
        #problem area !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        range_list = cache_range_find(address_output)
        start = range_list[0]
        end = range_list[1]
        index = 0
        for i in range(start,end):
            set_lines[tag_loc].byte_blocks[index] = ram_init[i]
            index += 1
    elif(main_cache.replacement == 2):
        #code for Least recently used
        #find line that is least recently used and delete 
        #easier to describe then to implement 
        least_recently_used = [] #least recently used tags 

        for i in set_lines:# dirty bit line writing
            if(set_lines[i].dirty == "1"):
                set_lines[i].dirty = "0"
                the_tag = "0x" + i
                tag_num = int(the_tag, 16)
                bin_tag = bin(tag_num)
                bin_tag = bin_tag[2:]
                while(len(bin_tag)!=block_bits):
                    bin_tag = "0" + bin_tag
                address_bin = bin_tag + set_bin
                while(len(address_bin)!=8):
                    address_bin = address_bin + "0"
                address_int = int(("0b"+address_bin),2)

                range_list = cache_range_find_int(address_int)
                start = range_list[0]
                end = range_list[1]
                index = 0
                for j in range(start,end):
                    ram_init[j] = set_lines[i].byte_blocks[index] 
                    index += 1
        #block size of 1 case
        for i in set_lines:
            if(set_lines[i].rank == main_cache.num_lines or set_lines[i].rank == 0):
                hex_num = "0x" + set_lines[i].tag
                to_list = int(hex_num, 16)
                least_recently_used.append(to_list)
        if(len(least_recently_used)==1):
            evicted_line_num = least_recently_used[0]
            the_tag = "0x%X" % least_recently_used[0]
            the_tag = the_tag[2:]
            zeros = ""
            if(len(the_tag) != 2):
                zeros += "0"
            the_tag = zeros + the_tag
            
            del set_lines[the_tag]
            #resetting rankings due to eviction 
            for i in set_lines:
                set_lines[i].rank = 0
            set_lines[tag_loc] = this_line
        else: # min finding for tie cases 
            #finds min tag
            min = least_recently_used[0]
            for i in range(len(least_recently_used)):
                if(least_recently_used[i] < min):
                    min = least_recently_used[i]
            evicted_line_num = min
            the_tag = "0x%X" % min
            the_tag = the_tag[2:]
            zeros = ""
            if(len(the_tag) != 2):
                zeros += "0"
            the_tag = zeros + the_tag
            del set_lines[the_tag]
            #resetting rankings due to eviction 
            for i in set_lines:
                set_lines[i].rank = 0
        #problem area !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        range_list = cache_range_find(address_output)
        start = range_list[0]
        end = range_list[1]
        index = 0
        for i in range(start,end):
            set_lines[tag_loc].byte_blocks[index] = ram_init[i]
            index += 1
    return evicted_line_num
    



##function to write into the cache object takes an address and data to write as input 
def cache_write(address, data):
    #converting for use 
    address_output = address
    data_modified = data
    data_modified = data_modified[2:]
    address_str = address
    address = int(address, 16)
    bin_address = bin(address)
    set_bits = number_of_set_index_bits(int(set_size))
    block_bits = number_of_block_offset_bits(int(block_size))
    tag_bits = 8 - (set_bits + block_bits)
    address_str = str(bin_address)
    address_str = address_str[2:]
    zeros = ""
    # print(address_str)
    trailing_zeros_num = 8-len(address_str)
    for i in range(trailing_zeros_num):
        zeros += "0"
    address_str = zeros + address_str
    tag_index = int(tag_bits)
    set_index = int(tag_index + set_bits)
    # block_index = int(set_index + block_bits)
    tag_bin = address_str[0:tag_index]
    set_bin = address_str[tag_index:set_index]
    block_bin = address_str[set_index:]
    tag_0d = int(("0b"+tag_bin),2)
    set_0d = int(("0b"+set_bin),2)
    block_0d = int(("0b"+block_bin),2)
    # size_list = len(main_cache.sets[set_0d].line_list)

    write_hit = ""
    need_eviction = True

    

    tag_loc = "0x%X" % tag_0d
    tag_loc = tag_loc[2:]
    if(len(tag_loc) != 2):
        tag_loc = "0" + tag_loc
    this_line = line("1","0", tag_loc, main_cache.block_offset) # used if line is new 
    this_line.byte_blocks[block_0d] = data_modified

    access_set = main_cache.sets[set_0d]
    set_lines = access_set.line_list
    evicted_line_num = -1
    if set_lines.get(tag_loc) is not None:
        need_eviction = False
        #write hit 
        # print("hit")
        write_hit += "yes"
        main_cache.hits += 1
        address_output = "-1"
        if(main_cache.write_hit == 1):
            #code for write through
            main_cache.sets[set_0d].line_list[tag_loc].byte_blocks[block_0d] = data_modified
            ram_init[address] = data_modified
            #update recent access rank
            set_lines[tag_loc].rank = 1
            for i in set_lines:
                if(set_lines[i].rank != main_cache.num_lines):
                    set_lines[i].rank += 1
            #evicting empty lines and writing to cache 
        elif(main_cache.write_hit == 2):
            #code for write back
            main_cache.sets[set_0d].line_list[tag_loc].byte_blocks[block_0d] = data_modified
            #update recent access rank
            set_lines[tag_loc].rank = 1
            for i in set_lines:
                if(set_lines[i].rank != main_cache.num_lines):
                    set_lines[i].rank += 1
    else:
        #write miss  
        # print("miss")
        write_hit += "no"
        main_cache.misses += 1
        if(main_cache.write_miss == 1):
            #code for write allocate
            for i in set_lines:
                # print("looping")
                #adding to empty lines 
                if(set_lines[i].valid == '0'):

                    del set_lines[i]
                    evicted_line_num = int(i)
                    set_lines[tag_loc] = this_line
                    range_list = cache_range_find(address_output)
                    start = range_list[0]
                    end = range_list[1]
                    index = 0
                    for i in range(start,end):
                        set_lines[tag_loc].byte_blocks[index] = ram_init[i]
                        index += 1
                    set_lines[tag_loc].byte_blocks[block_0d] = data_modified
                    ram_init[address] = data_modified 
                    need_eviction = False
                    # print("writing")
                    break
        elif(main_cache.write_miss == 2):
            need_eviction = False
            ram_init[address] = data_modified
            #code for no write allocate
     
    #Eviction handling
    if(need_eviction is True):
        evicted_line_num = eviction(set_lines, set_bin, block_bits,tag_loc, this_line, address_output)
        set_lines[tag_loc].byte_blocks[block_0d] = data_modified
    dirty_bit = ""
    if(main_cache.write_miss != 2):
        set_line = access_set.line_list[tag_loc]
        
        if(ram_init[address] != data_modified):
            dirty_bit += "1"
        else:
            dirty_bit+="0"
        set_line.dirty = dirty_bit
    else:
        dirty_bit += "0"

    print("set:" + str(set_0d))
    print("tag:" + tag_loc)
    print("write_hit:" + write_hit)
    print("eviction_line:"+ str(evicted_line_num))
    print("ram_address:"+address_output)
    print("data:" + data)
    print("dirty_bit:" + dirty_bit)

##function to read from the cache object it takes a hexidecimal address as input
def cache_read(address):
    #converting for use 
    address_output = address
    address_str = address
    address = int(address, 16)
    bin_address = bin(address)
    set_bits = number_of_set_index_bits(int(set_size))
    block_bits = number_of_block_offset_bits(int(block_size))
    tag_bits = 8 - (set_bits + block_bits)
    address_str = str(bin_address)
    address_str = address_str[2:]
    zeros = ""
    
    trailing_zeros_num = 8-len(address_str)
    for i in range(trailing_zeros_num):
        zeros += "0"
    address_str = zeros + address_str
    tag_index = int(tag_bits)
    set_index = int(tag_index + set_bits)
    tag_bin = address_str[0:tag_index]
    set_bin = address_str[tag_index:set_index]
    block_bin = address_str[set_index:]
    tag_0d = int(("0b"+tag_bin),2)
    set_0d = int(("0b"+set_bin),2)
    block_0d = int(("0b"+block_bin),2)
   
    
    
    

    tag_loc = "0x%X" % tag_0d
    tag_loc = tag_loc[2:]
    if(len(tag_loc) != 2):
        tag_loc = "0" + tag_loc
    data_hex = "0x"
    this_line = line("1","0", tag_loc, main_cache.block_offset) # used if line is new 
    read_hit = ""
    access_set = main_cache.sets[set_0d]
    set_lines = access_set.line_list
    evicted_line_num = -1
    need_eviction = True


    if set_lines.get(tag_loc) is not None:
        need_eviction = False
        #read hit 
        address_output = "-1"
        main_cache.hits += 1
        # print("hit")
        read_hit += "yes"
        line_ = set_lines[tag_loc]
        #update recent access rank
        line_.rank = 1
        for i in set_lines:
            if(set_lines[i].rank != main_cache.num_lines):
                set_lines[i].rank += 1
        data = line_.byte_blocks[block_0d]
        data_hex += data
    else:
        #read miss  
        
        # print("miss")
        main_cache.misses += 1 
        read_hit += "no"
        data = ram_init[address]
        data_hex += data
        #write into cache 
        #code for write in read for writing into empty lines 
        for i in set_lines:
            # print("looping")
            if(set_lines[i].valid == '0'):
                del set_lines[i]
                evicted_line_num = int(i)
                set_lines[tag_loc] = this_line
                range_list = cache_range_find(address_output)
                start = range_list[0]
                end = range_list[1]
                index = 0
                for i in range(start,end):
                    set_lines[tag_loc].byte_blocks[index] = ram_init[i]
                    index += 1 
                need_eviction = False
                    # print("writing")
                break
        #Eviction handling
    if(need_eviction is True):
        evicted_line_num = eviction(set_lines, set_bin, block_bits,tag_loc, this_line, address_output)
    
    
    print("set:" + str(set_0d))
    print("tag:" + tag_loc)
    print("hit:" + read_hit)
    print("eviction_line:" + str(evicted_line_num))
    print("ram_address:"+address_output)
    print("data:" + data_hex)

#----------------------------------------------------------------
#Control Menu 
print("*** Welcome to the cache simulator ***")
print("initialize the RAM:")
input_ = input()
print("RAM successfully initialized!")

#ram iniatilization 
strings = input_.split()
start = strings[1]
end = strings[2]
first_num = int(start, 16)
second_num = int(end, 16)

ram_init = []# empty ram all stored values are 00
# actual ram array


for i in range(memory_size):
    ram_init.append("00")

for i in range(first_num,(second_num+1)): # storing only the iniatilized values 
    ram_init[i] = ram_string[i] 

#cache configuration
print("configure the cache:")
cache_size = input("cache size: ")
block_size = input("data block size: ")
associativity = input("associativity: ")
replace = input("replacement policy: ")
w_hit = input("write hit policy: ")
w_miss = input("write miss policy: ")
print("cache successfully configured!")
set_size = int((int(cache_size)/(int(block_size)*int(associativity))))
main_cache = cache(set_size,int(associativity),int(block_size),int(replace),int(w_hit),int(w_miss),int(cache_size))##cache object that stores all cache data 

#control menu print out and input
main_cache.generate_empty_cache_sets()#making a cold cache

while True:
    print("*** Cache simulator menu ***")
    print("type one command:")
    print("1. cache-read")
    print("2. cache-write")
    print("3. cache-flush")
    print("4. cache-view")
    print("5. memory-view")
    print("6. cache-dump")
    print("7. memory-dump")
    print("8. quit")
    print("****************************")
    input_  = input()
    strings = input_.split()

    
    if(strings[0] == "memory-view" or strings[0] == "5"):
        memory_view()
    elif(strings[0] == "cache-view" or strings[0] == "4"):
        main_cache.cache_view()
    elif(strings[0] == "cache-flush" or strings[0] == "3"):
        main_cache.cache_flush()
    elif(strings[0] == "cache-dump" or strings[0] == "6"):
        main_cache.cache_dump()
    elif(strings[0] == "memory-dump" or strings[0] == "7"):
        memory_dump()
    elif(strings[0] == "cache-write" or strings[0] == "2"):
        if(len(strings) != 3):
            print("type cache-write address data please!!!")
            continue
        cache_write(strings[1],strings[2])
    elif(strings[0] == "cache-read" or strings[0] == "1"):
        if(len(strings) != 2):
            print("type cache-write address data please!!!")
            continue
        cache_read(strings[1])
    if(strings[0] == "quit" or strings[0] == "8"):
        break
    
    


    

#-----------------------------------------------------------------
#dirty bit not being set when writing no data under write back and write allocate 
# initialize the RAM: settings under failed test 
# b 0x00 0xFF
# RAM successfully initialized!
# configure the cache:
# cache size: 32
# data block size: 8
# associativity: 1
# replacement policy: 2
# write hit policy: 2
# write miss policy: 1
# cache successfully configured!