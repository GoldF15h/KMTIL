class Node :
    def __init__(self,data):
        self.data = data
        self.left = None
        self.right = None

class BST:
    def __init__(self):
        self.root = None

    def printTree(self, node, level = 0):
        if node != None:
            self.printTree(node.right, level + 1)
            print('     ' * level, str(node.data))
            self.printTree(node.left, level + 1)

    def printInfix (self,node) :
        global operation
        # print('current data = ',node.data)
        if node != None :
            if node.data in operation :
                print('(',end='')
                self.printInfix(node.left)
                print(str(node.data),end='')
                self.printInfix(node.right)
                print(')',end='')
            else :
                print(str(node.data),end='')

    def printPrefix(self,node) :
        if node != None:
            print(str(node.data),end='')
            self.printPrefix(node.left)
            self.printPrefix(node.right)

inp = input('Enter Postfix : ')
operation = ['+','-','*','/']
stack = []
for i in inp :
    if i not in operation :
        stack.append(Node(i))
    else :
        tmp = Node(i)
        tmp.right = stack[-1]
        tmp.left = stack[-2]
        stack.pop()
        stack.pop()
        stack.append(tmp)

op = BST()
op.root = stack[0]
print('Tree :')
op.printTree(op.root)
print('--------------------------------------------------')
print('Infix : ',end='')
op.printInfix(op.root)
print('\nPrefix : ',end='')
op.printPrefix(op.root)