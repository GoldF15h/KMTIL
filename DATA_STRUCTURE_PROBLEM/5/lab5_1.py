class Node:
    def __init__(self, data) :
        self.data = data
        self.next = None

class LinkedList :
    def __init__(self) :
        self.head = Node('X')
        self.size = 0

    def __str__(self):
        if self.size == 0 :
            return 'List is empty'
        elif self.size == 1 :
            return 'link list : ' + self.head.data
        else :
            op = []
            ptr = self.head

            while ptr.next != None :
                op.append(ptr.data)
                ptr = ptr.next

            op.append(ptr.data)

            return 'link list : '+'->'.join(op)


    def isEmpty(self) :
        if self.size == 0 :
            return True
        else :
            return False

    def append(self,data) :
        # print('append called' ,self.size,self.head.data,self.head.next)

        if self.size == 0 :
            self.head.data = data
            self.size += 1

        else :
            ptr = self.head

            while ptr.next != None :
                # print('db = ' + ptr.data)
                ptr = ptr.next

            self.size += 1
            ptr.next = Node(data)
            # print('next test = ',ptr.next.data)

    def insert(self,_index,data) :
        index = int(_index)

        if index > 0 and index < self.size :
            print(f'index = {index} and data = {data}')
            ptr = self.head
            current = 0

            while current < index - 1:
                ptr = ptr.next
                current += 1

            _node = Node(data)
            _node.next = ptr.next
            ptr.next = _node
            self.size += 1

        elif index == 0 :
            print(f'index = {index} and data = {data}')
            if self.size == 0 :
                self.head.data = data
                self.size += 1
            else :
                _node = Node(data)
                _node.next = self.head
                self.head = _node
                self.size += 1

        elif index == self.size :
            print(f'index = {index} and data = {data}')
            self.append(data)

        else :
            print('Data cannot be added')


inp = input('Enter Input : ').split(',')
# print(inp)
setDef = inp[0].split(' ')
myList = LinkedList()
# print(setDef)

if inp[0] != '' :
    # print('append all')
    for value in setDef :
        # print('debug = '+value)
        myList.append(value)

print(myList)

for _data in range(1,len(inp)) :
    index , data = inp[_data].split(':')
    myList.insert(index,data)
    print(myList)
