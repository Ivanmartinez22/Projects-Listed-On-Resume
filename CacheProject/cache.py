# // File: cachesimulator.py
# // Author(s): Ivan Martinez
# // Date: 12/8/2021
# // Section: 505
# // E-mail(s): ivanattexas@tamu.edu 
# // Description:
# // e.g., The content of this file implements the cache object class and functions
from set import set
from line import line


##class that creates a cache object that stores an array of sets and other cache data 
class cache:
    sets = [] 
    hits = 0
    misses = 0
    ##this class function initializes class data with parameter values 
    def __init__(self,num_sets,num_lines,block_offset,replacement,write_hit,write_miss, cache_size):
        self.num_sets = num_sets
        self.num_lines = num_lines
        self.block_offset = block_offset
        self.replacement = replacement
        self.write_hit = write_hit
        self.write_miss = write_miss
        self.cache_size = cache_size
    ##this class function generates a cold cache
    def generate_empty_cache_sets(self):
        #used when cache is cold 
        #used in flushing
        for i in range(self.num_sets):
            #print("generating")
            local_dict = {}
            local_set = set(i,local_dict)
            for j in range(self.num_lines):
                local_line = line("0","0","00",self.block_offset)
                
                local_dict[str(j)] = local_line
            # print(str(local_set.line_list))
            self.sets.append(local_set)
        # print(str(self.sets))
    ##this class function clears the cache and generates an empty cache 
    def cache_flush(self):
        self.sets.clear()
        self.generate_empty_cache_sets()
        print("cache-cleared")
    ## class function to write cache contents into a .txt file 
    def cache_dump(self):
        # print("cache-dump")
        f = open("cache.txt", "w")
        for i in range(self.num_sets):
            i_iterator = self.sets[i]
            # print(i)
            ll = i_iterator.line_list
            for j in ll:
                # print(j)
                output = ""
                # output += str(ll[j].valid)
                # output += " "
                # output += str(ll[j].dirty)
                # output += " "
                # output += str(ll[j].tag)
                # output += " "
                # output += str(ld[j].size_of_blocks)
                # output += " "
                # output += str(ld[j].byte_blocks)
                for k in range(self.block_offset):
                    byte = str(ll[j].byte_blocks[k])
                    output += byte 
                    output += " "
                f.write(output + '\n')
        f.close()  
    ## class function to view cache contents 
    def cache_view(self):
        # print("cache-view")
        print("cache_size:" + str(self.cache_size))
        print("block_size:" + str(self.block_offset))
        print("associativity:" + str(self.num_lines))
        if(self.replacement == 1):
            print("replacement_policy:random_replacement")
            #code for Random replacement
        elif(self.replacement == 2):
            print("replacement_policy:least_recently_used")
            #code for Least recently used
        
        if(self.write_hit == 1):
            print("write_hit_policy:write_through")
            #code for write through
        elif(self.write_hit == 2):
            print("write_hit_policy:write_back")
            #code for write back
        
        if(self.write_miss == 1):
            print("write_miss_policy:write_allocate")
            #code for write allocate
        elif(self.write_miss == 2):
            print("write_miss_policy:no_write_allocate")
            #code for no write allocate
        print("number_of_cache_hits:" + str(self.hits))
        print("number_of_cache_misses:" + str(self.misses))
        print("cache_content:")
        for i in range(self.num_sets):
            i_iterator = self.sets[i]
            # print(i)
            ll = i_iterator.line_list
            for j in ll:
                # print(j)
                output = ""
                output += str(ll[j].valid)
                output += " "
                output += str(ll[j].dirty)
                output += " "
                output += str(ll[j].tag)
                output += " "
                # output += str(ld[j].size_of_blocks)
                # output += " "
                # output += str(ld[j].byte_blocks)
                for k in range(self.block_offset):
                    byte = str(ll[j].byte_blocks[k])
                    output += byte 
                    output += " "
                print(output)





    
    






