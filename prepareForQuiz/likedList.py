class Node :
    def __init__(self,data):
        self.data = data
        self.next = None

class linkedList :
    def __init__(self):
        self.head = Node(None)
        self.size = 0

    def __str__(self):
        # print(self.size)
        if self.size > 0:
            ptr = self.head.next
            op = []
            while ptr != None :
                op.append(str(ptr.data))
                ptr = ptr.next 

            return '->'.join(op)
        
        else :
            return "Empty List"

    def append(self,data) :
        ptr = self.head
        while ptr.next != None :
            ptr = ptr.next

        ptr.next = Node(data)
        self.size += 1

    def addHead(self,data) :
        newNode = Node(data)
        newNode.next = self.head.next
        self.head.next = newNode
        self.size += 1

    def head(self) :
        if self.size :
            return str(self.head.next.data)
        else :
            return "Empty List"

    def tail(self) :
        if self.size :
            ptr = self.head.next
            while ptr.next != None :
                ptr = ptr.next 

            return str(ptr.data)

        else :
            return "Empty List"

    def pop(self) :
        if self.size :
            ptr = self.head
            while ptr.next.next != None :
                ptr = ptr.next

            ptr.next = None
            self.size -= 1
        else :
            print("Empty List")

myList = linkedList()
myList.append(1)
myList.append(2)
print(myList)
myList.addHead(3)
myList.pop()
print(myList)
myList.pop()
myList.pop()
print(myList)
myList.pop()
myList.addHead(1)
myList.addHead(3)
myList.addHead(1)
myList.addHead(2)
myList.addHead(1)
myList.addHead(1)
myList.append(10)
print(myList)