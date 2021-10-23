class Node:
    def __init__(self, value):
        self.value = value
        self.next = None
        self.previous = None

class LinkedList:
    def __init__(self):
        self.head = None
        self.tail = None

    def __str__(self):
        if self.isEmpty():
            return "Empty"
        cur, s = self.head, str(self.head.value) + " "
        while cur.next != None:
            s += str(cur.next.value) + " "
            cur = cur.next
        return s

    def reverse(self):
        if self.isEmpty():
            return "Empty"
        cur, s = self.tail, str(self.tail.value) + " "
        while cur.previous != None:
            s += str(cur.previous.value) + " "
            cur = cur.previous
        return s

    def isEmpty(self):
        return self.head == None

    def append(self, item):
        ptr = self.head

        if self.head == None : # if there is nothing in the list
            self.head = Node(item) # create and set the head to new node
            self.tail = self.head # piont the tail at the head
        
        else :
            _node = Node(item) 
            self.tail.next = _node # point old tail to the new tail
            _node.previous = self.tail # point new tail to the old tail
            self.tail = _node # set the tail to new tail

    def addHead(self, item):
        ptr = self.head

        if self.head == None : # if it's noting in the list
            self.head = Node(item)
            self.tail = self.head

        else :
            _node = Node(item)
            self.head.previous = _node # point the old head to the new head
            _node.next = self.head # point the new head to the old head
            self.head = _node # set the new head

    def insert(self, pos, item):
        ptr = self.head 
        
        if ptr == None :
            self.append(item)

        else:
            if pos >= 0 :
                ptr = self.head 
                currentIndex = 0

                while ptr.next != None and currentIndex < pos :
                    ptr = ptr.next
                    currentIndex += 1
            else :
                ptr = self.tail
                currentIndex = -1

                while ptr.previous != None and currentIndex > pos :
                    ptr = ptr.previous
                    currentIndex -= 1

            _node = Node(item)

            if currentIndex == pos :
                if ptr.previous == None and ptr.next == None: # if it's only 1 value
                    self.addHead(item)

                elif ptr.previous != None : # if it's in the midde and tail
                    _node.next = ptr
                    _node.previous = ptr.previous

                    ptr.previous.next = _node
                    ptr.previous = _node

                else : # if it's head ins
                    self.addHead(item)
                    
            else :
                if pos > 0 :
                    self.append(item)
                else :
                    self.addHead(item)

    def search(self, item):
        ptr = self.head

        while ptr != None :
            if ptr.value == item :
                return 'Found'
            ptr = ptr.next

        return 'Not Found'

    def index(self, item):
        ptr = self.head
        currentIndex = 0

        while ptr != None :
            if ptr.value == item :
                return currentIndex
            ptr = ptr.next
            currentIndex += 1

        return -1

    def size(self):
        ptr = self.head
        _size = 1

        if ptr == None :
            return 0

        else :
            while ptr.next != None :
                ptr = ptr.next
                _size += 1

            return _size

    def pop(self, pos):
        
        if pos >= 0 :
            currentIndex = 0
            ptr = self.head
            if ptr == None :
                return 'Out of Range'

            while ptr.next != None and currentIndex < pos :
                ptr = ptr.next
                currentIndex += 1
            
        else :
            currentIndex = -1
            ptr = self.tail
            if ptr == None :
                return 'Out of Range'

            while ptr.previous != None and currentIndex > pos :
                ptr = ptr.previous
                currentIndex -= 1

        if currentIndex == pos : 
            if ptr.next != None and ptr.previous != None : # if it's between
                ptr.next.previous = ptr.previous
                ptr.previous.next = ptr.next
            
            elif ptr.next == None and ptr.previous == None : # if it's 1 value
                self.head = None
                self.tail = None

            elif ptr.next == None : # if it's tail pop
                self.tail = ptr.previous
                ptr.previous.next = None

            elif ptr.previous == None : # if it's head pop
                self.head = ptr.next
                ptr.next.previous = None 

            return 'Success'

        else :
            return 'Out of Range'

L = LinkedList()
inp = input('Enter Input : ').split(',')
for i in inp:
    if i[:2] == "AP":
        L.append(i[3:])
    elif i[:2] == "AH":
        L.addHead(i[3:])
    elif i[:2] == "SE":
        print("{0} {1} in {2}".format(L.search(i[3:]), i[3:], L))
    elif i[:2] == "SI":
        print("Linked List size = {0} : {1}".format(L.size(), L))
    elif i[:2] == "ID":
        print("Index ({0}) = {1} : {2}".format(i[3:], L.index(i[3:]), L))
    elif i[:2] == "PO":
        before = "{}".format(L)
        k = L.pop(int(i[3:]))
        print(("{0} | {1}-> {2}".format(k, before, L)) if k == "Success" else ("{0} | {1}".format(k, L)))
    elif i[:2] == "IS":
        data = i[3:].split()
        L.insert(int(data[0]), data[1])
print("Linked List :", L)
print("Linked List Reverse :", L.reverse())