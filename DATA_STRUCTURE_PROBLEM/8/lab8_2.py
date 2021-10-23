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
            self.root = node(data)
        else :
            if root.data > data : 
                if root.left == None :
                    root.left = node(data)
                else :
                    self.insert(data,root.left)
            else :
                if root.right == None :
                    root.right = node(data)
                else :
                    self.insert(data,root.right)

    def printTree(self,root,level=0) :
        if root != None :
            self.printTree(root.right,level+1)
            print("     "*level,root.data)
            self.printTree(root.left,level+1)

                    
tree = binaryTree()
inp,compare = input("Enter Input : ").split('/')
inp =  [ int(x) for x in inp.split() ]
clostest = inp[0]
compare = int(compare)
# print(inp)
for i in inp :
    if abs(compare - i) <= abs(compare - clostest) :
        if abs(compare - i) == abs(compare - clostest) :
            if i > clostest :
                clostest = i
        else :
            clostest = i
    tree.insert(i,tree.root)
    tree.printTree(tree.root)
    print('--------------------------------------------------')
print(f'Closest value of {compare} : {clostest}')



    