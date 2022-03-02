# // File: cachesimulator.py
# // Author(s): Ivan Martinez
# // Date: 12/8/2021
# // Section: 505
# // E-mail(s): ivanattexas@tamu.edu 
# // Description:
# // e.g., The content of this file implements the line object class
## a class that creates a line object which stores cache line data 
class line:
    size_of_blocks = 1
    byte_blocks = []
    rank = 0
    #default line values 
    ## a class function function that inializes line data from given parameters
    def __init__(self,valid,dirty,tag,size_of_blocks):
        self.valid = valid
        self.tag = tag
        self.dirty = dirty
        self.size_of_blocks = size_of_blocks
        self.byte_blocks = ["00"] * size_of_blocks
    
