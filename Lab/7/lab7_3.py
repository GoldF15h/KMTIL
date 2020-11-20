class Node:
    def __init__(self, data):
        self.data = data
        self.left = None
        self.right = None
    
    def __str__(self):
        return str(self.data)

class BST:
    def __init__(self):
        self.root = None
        self.max = None
        self.min = None

    def insert(self, data):
        if self.root == None :
            self.root = Node(data)
            self.max = data
            self.min = data
        else :
            ptr = self.root
            # print('inserting : ')

            if self.max < data :
                self.max = data
            if self.min > data :
                self.min = data

            while True :
                # print(ptr.data)
                if ptr.data > data :
                    if ptr.left == None :
                        ptr.left = Node(data)
                        break
                    else :
                        ptr = ptr.left
                else :
                    if ptr.right == None :
                        ptr.right = Node(data)
                        break
                    else :
                        ptr = ptr.right

    def lessThanOrEqual (self,ptr,data) :
        if ptr == None :
            return 0
        elif ptr.data <= data :
            return 1 + self.lessThanOrEqual(ptr.left,data) + self.lessThanOrEqual(ptr.right,data)
        else :
            return 0 + self.lessThanOrEqual(ptr.left,data) + self.lessThanOrEqual(ptr.right,data)

    def printTree(self, node, level = 0):
        if node != None:
            self.printTree(node.right, level + 1)
            print('     ' * level, node)
            self.printTree(node.left, level + 1)

T = BST()
inp = input('Enter Input : ').split('/')
ins = list(map(int,inp[0].split()))
for i in ins:
    # print(i)
    root = T.insert(i)
T.printTree(T.root)
print('--------------------------------------------------')
print(T.lessThanOrEqual(T.root,int(inp[1])))