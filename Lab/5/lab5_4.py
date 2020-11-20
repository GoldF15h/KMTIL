import sys

class Node:
    def __init__(self,data,next = None ):
        self.data = data
        self.next = next
        self.visit = False

    def __str__(self):
        op = ''
        op += str(self.data)+',' if self.data != None else 'None,'
        op += str(self.next)+',' if self.next != None else 'None,'
        op += 'True,' if self.visit else 'False,'
        return op

class linkedList :
    def __init__(self):
        self.head = None

    def append(self,item) :
        ptr = self.head

        if self.head == None :
            self.head = Node(item)

        else :
            while ptr.next != None :
                ptr = ptr.next 

            ptr.next = Node(int(item))

    def __str__(self):
        op = []
        ptr = self.head
        while ptr != None :
            op.append(str(ptr.data))
            ptr = ptr.next
        if len(op) > 0 :
            return '->'.join(op)   
        else : 
            return 'Empty'

    def set_next(self,a_pos,b_pos) :
        a_pos = int(a_pos)
        b_pos = int(b_pos)
        ptr = self.head
        currentIndex = 0

        if ptr == None :
            return 'Error! {list is empty}'

        while ptr.next != None and currentIndex < int(a_pos) :
            ptr = ptr.next
            currentIndex += 1

        if currentIndex != int(a_pos) :
            # print(currentIndex,a_pos)
            return 'Error! {index not in length}: ' + str(a_pos)

        else :
            a_ptr = ptr
            ptr = self.head 
            currentIndex = 0
            
            while ptr.next != None and currentIndex < b_pos :
                ptr = ptr.next  
                currentIndex += 1

            if currentIndex != b_pos :
                self.append(b_pos)
                return 'index not in length, append : ' + str(b_pos)

            else :
                a_ptr.next = ptr
                return 'Set node.next complete!, index:value = ' + str(a_pos) + ':' + str(a_ptr.data) + ' -> ' + str(b_pos) + ':' + str(ptr.data)

    def isLooped(self) :
        ptr = self.head
        visitedNumber = 0
        while ptr != None and ptr.visit != True :
            # print(ptr)
            visitedNumber += 1
            ptr.visit = True
            ptr = ptr.next

        if ptr == None :
            ptr = self.head
            for i in range(visitedNumber) :
                ptr.visit = False
                ptr = ptr.next

            return False

        else :
            return True
        

inp = input('Enter input : ').split(',')
myList = linkedList()

for i in inp :
    action,value = i.split(' ')
    if action == 'A' :
        myList.append(value)
        print(myList)

    elif action == 'S' :
        print( myList.set_next( value.split(':')[0] , value.split(':')[1] ) )

    if myList.isLooped() :
        print('Found Loop')
        sys.exit()

print('No Loop')
print(myList)


    