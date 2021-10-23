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


    def insert(self, data):
        if self.root == None :
            self.root = Node(data)
        else :
            ptr = self.root
            # print('inserting : ')

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

    def printTree(self, node, level = 0):
        if node != None:
            self.printTree(node.right, level + 1)
            print('     ' * level, node)
            self.printTree(node.left, level + 1)

    def inorderPrint(self,node) :
        if node != None :
            self.inorderPrint(node.left)
            print(node.data,end=' ')
            self.inorderPrint(node.right)

    def posorderPrint(self,node) :
        if node != None :
            # print('Current',node)
            self.posorderPrint(node.left)
            self.posorderPrint(node.right)
            print(node.data,end=' ')

    def preorederPrint(self,node) :
        if node != None :
            print(node.data,end=' ')
            self.preorederPrint(node.left)
            self.preorederPrint(node.right)

    def height(self,node): 
        if node is None: 
            return 0 
        else : 
            # Compute the height of each subtree  
            lheight = self.height(node.left) 
            rheight = self.height(node.right) 

            #Use the larger one 
            if lheight > rheight : 
                return lheight+1
            else: 
                return rheight+1
            
    def printGivenLevel(self,root , level): 
        if root is None: 
            return
        if level == 1: 
            print(root.data,end=" ") 
        elif level > 1 : 
            self.printGivenLevel(root.left , level-1) 
            self.printGivenLevel(root.right , level-1) 

    def breadthPrint(self,root): 
        h = self.height(root) 
        for i in range(1, h+1): 
            self.printGivenLevel(root, i)

T = BST()
inp = [int(i) for i in input('Enter Input : ').split(' ')]
for i in inp:
    # print(i)
    root = T.insert(i)
# T.printTree(T.root)
print('Preorder : ',end='')
T.preorederPrint(T.root)
print('\nInorder : ',end='')
T.inorderPrint(T.root)
print('\nPostorder : ',end='')
T.posorderPrint(T.root)
print('\nBreadth : ',end='')
T.breadthPrint(T.root)