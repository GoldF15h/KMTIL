class Queue:
    def __init__(self):
        self.items = []

    def enQueue(self,i):
        self.items.append(i)

    def deQueue(self):
        return self.items.pop(0)

    def size(self):
        return len(self.items)

    def isEmpty(self):
        return self.items == []

    def insert(self,index,item):
        self.items.insert(index,item)
        
q = Queue()
inp = input("Enter Input : ").split(",")
count = 0

for i in inp:

    devide = i.split()

    if devide[0] == "EN":

        Id = devide[1]
        q.enQueue(Id)

    elif devide[0] == "ES":

        sId = devide[1]
        q.insert(count,sId)
        count += 1

    elif devide[0] == "D":

        if q.size() > 0:

            print(q.deQueue())
            count -= 1
            if count < 0:
                count = 0

        else:

            print("Empty")