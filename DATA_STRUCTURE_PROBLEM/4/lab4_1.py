class queue :
    def __init__(self):
        self.list = []
        self.poped = []

    def add(self,value):
        self.list.append(value)
        return ', '.join(self.list)

    def pop(self):

        if len(self.list) > 0:
            self.poped.append(self.list[0])
            self.list.pop(0)
            if len(self.list) > 0:
                return self.poped[-1] + ' <- ' + ', '.join(self.list)
            else:
                return self.poped[-1] + ' <- ' + 'Empty'
        else:
            return 'Empty'
       
        
    def showQueue(self):
        op = ''
        if len(self.poped) == 0:
            op += 'Empty'
        else:
            op += ', '.join(self.poped)

        op += ' : '

        if len(self.list) == 0:
            op += 'Empty'
        else:
            op += ', '.join(self.list)

        return op

inp = input('Enter Input : ').split(',')
myQueue = queue()

#print(inp)

for i in inp:

    if i == 'D':

        print(myQueue.pop())

    else:
        
        print(myQueue.add(i.split(' ')[1]))
        
print(myQueue.showQueue())