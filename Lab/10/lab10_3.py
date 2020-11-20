class hash_data:
    def __init__(self, key, value):
        self.key = key
        self.value = value

    def __str__(self):
        return "({0}, {1})".format(self.key, self.value)

class hash:
    def __init__ (self,table_size,max_collision) :
        self.hash_table = [0]*table_size
        self.max_collision = max_collision

    def insert(self,data) :
        if not 0 in self.hash_table :
            print('This table is full !!!!!!')
            return False
        first_index = 0
        # print(data.key)
        for i in data.key :
            # print(ord(i),end=' ')
            first_index += ord(i)
        # print('->',index)
        first_index %= len(self.hash_table)
        jumps_index = [first_index]*self.max_collision
        for i in range(len(jumps_index)) :
            jumps_index[i] = (jumps_index[i] + (i**2))%len(self.hash_table)
        # print(jumps_index)
        # print('intsert index ->',index)
        jumps = 0

        while True :
            # print('index -> {} jumps -> {}'.format(index,jumps))
            if self.hash_table[jumps_index[jumps]] == 0 :
                self.hash_table[jumps_index[jumps]] = data
                break
            else :
                print('collision number {} at {}'.format(jumps+1,jumps_index[jumps]))
                jumps += 1

            if jumps >= self.max_collision :
                print ('Max of collisionChain')
                break

        return True

    def print_hash_table(self):
        for i in range(len(self.hash_table )) :
            if self.hash_table[i] != 0 :
                print(f'#{i+1}	({self.hash_table[i].key}, {self.hash_table[i].value})')
            else :
                print(f'#{i+1}      None')

        print('---------------------------')


inp = input(' ***** Fun with hashing *****\nEnter Input : ').split('/')
table_size, max_collision = list(map(int,inp[0].split()))
inp_data = []
for i in inp[1].split(',') :
    inp_data.append(i.split())
# print(table_size, max_collision)
# print(inp_data)
my_hash = hash(table_size, max_collision)
for i in inp_data :
    if my_hash.insert(hash_data(i[0],i[1])) :
        my_hash.print_hash_table()
    else :
        break
    # print(i)