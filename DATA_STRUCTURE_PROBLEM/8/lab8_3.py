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

    def findRank(self,rank) :
        sortedList = self.sort(self.root)
        # print(sortedList)
        currtentRank = 0
        for i in sortedList :
            if i <= rank :
                currtentRank += 1   
    
        return currtentRank

    def sort(self,root) :
        if root.left != None and root.right != None :
            return self.sort(root.left) + [root.data] + self.sort(root.right)
        elif root.left != None :
            return self.sort(root.left) + [root.data]
        elif root.right != None :
            return [root.data] + self.sort(root.right)
        else :
            return [root.data]

tree = binaryTree()
inp,rank = input('Enter Input : ').split('/')
inp = [ tree.insert(int(x),tree.root) for x in inp.split() ]
rank = int(rank)
tree.printTree(tree.root)
print('--------------------------------------------------')
# print(len(tree.sort(tree.root)))
print(f'Rank of {rank} : {tree.findRank(rank)}')