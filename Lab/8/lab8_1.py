class node :
    def __init__(self,data):
        self.data = data
        self.left = None
        self.right = None

    def __str__(self):
        return str(self.data)

class binaryTree :
    def __init__(self):
        self.root = None
    
    def insert(self,data,root):
        if self.root == None :
            print('*',end='')
            self.root = node(data)
        else :
            if root.data > data : 
                if root.left == None :
                    print('L*',end='')
                    root.left = node(data)
                else :
                    print('L',end='')
                    self.insert(data,root.left)
            else :
                if root.right == None :
                    print('R*',end='')
                    root.right = node(data)
                else :
                    print('R',end='')
                    self.insert(data,root.right)
                    
tree = binaryTree()
inp =  [ int(x) for x in input("Enter Input : ").split() ]
# print(inp)
for i in inp :
    tree.insert(i,tree.root)
    print('')



    