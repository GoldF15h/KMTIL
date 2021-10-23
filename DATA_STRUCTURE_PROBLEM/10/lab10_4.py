# ใช้ while loop ในการ insert เข้าไปตาม index ถ้า return false ให้ ทำการเริ่ม insert ใหม่ตั้งแต่ index 0 
# แต่ต้องจำไว้ว่า index ไหนที่เรา print hash table ไปแล้วบ้าง


class hash:
    def __init__ (self,table_size,max_collision,threshold) :
        self.hash_table = [None]*table_size
        self.max_collision = max_collision
        self.threshold = threshold
        print('Initial Table :')
        self.print_hash_table()

    def insert(self,data) :
        list_of_prime_number = [2,3,5,7,11,13,17,19,23,29,31,37,41,43,49,53,59,61,67,71,73,79,83,89,97]
        jumps = 0
        index = int(data) % len(self.hash_table)
        jumps_index = [0]*self.max_collision
        for i in range(1,self.max_collision) :
            jumps_index[i] = (index + i**2) % len(self.hash_table)
        
        none_counter = 0
        for i in self.hash_table :
            if i == None : 
                none_counter += 1
        cur_element_size = len(self.hash_table) - none_counter 
        if cur_element_size + 1 >= len(self.hash_table) * self.threshold // 100 :
            print('****** Data over threshold - Rehash !!! ******')
            for i in list_of_prime_number :
                if i > len(self.hash_table) * 2 :
                    self.hash_table = [None]*i
                    return False

        while True :
            if self.hash_table[index] == None :
                self.hash_table[index] = data 
                return True
            else :
                print('collision number {} at {}'.format(jumps+1,index))
                index = jumps_index[jumps]
                jumps += 1
            
            if jumps >= self.max_collision :
                print('****** Max collision - Rehash !!! ******')
                for i in list_of_prime_number :
                    if i > len(self.hash_table) * 2 :
                        self.hash_table = [None]*i
                        # self.insert(inp_data,False)
                        return False

    def print_hash_table(self):
        for i in range(len(self.hash_table )) :
            if self.hash_table[i] != None :
                print(f'#{i+1}	{self.hash_table[i]}')
            else :
                print(f'#{i+1}      None')

        print('---------------------------')

inp = input(' ***** Rehashing *****\nEnter Input : ').split('/')
table_size, max_collision, threshold = list(map(int,inp[0].split()))
inp_data = inp[1].split(' ')
# print(table_size, max_collision)
# print(inp_data)
my_hash = hash(table_size, max_collision, threshold)
# print(inp_data)
success = 0
i = 0
is_print = True
while i < len(inp_data) :
    if is_print :
        print('Add : {}'.format(inp_data[i]))
        is_print = False
    if my_hash.insert(inp_data[i]) :
        i += 1
        if i > success :
            my_hash.print_hash_table()
            success += 1
            is_print = True
    else :
        i = 0
        
    # print(i)