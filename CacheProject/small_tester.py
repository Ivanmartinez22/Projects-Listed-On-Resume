

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

address = input("enter address hex")
print(cache_range_find(address))