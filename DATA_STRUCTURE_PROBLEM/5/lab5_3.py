class Node:
    def __init__(self,data,next = None ):
        self.data = data
        self.next = next

    def __str__(self):
        return self.data

def createList(l):
    l = list(map(int,l))
    head = Node(l[0])

    ptr = head
    for index in range(1,len(l)) :  # append all value in to list
        _node = Node(l[index]) # create new node
        ptr.next = _node            # point previouse node to the new one
        ptr = ptr.next              # jump to the new one

    return head                # return head

def printList(H = Node(None)):
    ptr = H
    op = []

    while ptr != None :
        # print(ptr.data)
        op.append(str(ptr.data))
        ptr = ptr.next

    print(' '.join(op))

    
def mergeOrderesList(p=Node(None),q=Node(None)):
    head = None

    if p.data < q.data :
        head = Node(p.data)
        p = p.next

    else :
        head = Node(q.data)
        q = q.next

    ptr = head

    while p != None and q != None :
        # print('head = ',end = '')
        # printList(head)
        # print('p = ',end = '')
        # printList(p)
        # print('q = ',end = '')
        # printList(q)
        # print('*************************')
        if p.data < q.data :
            ptr.next = Node(p.data)
            p = p.next

        else :
            ptr.next = Node(q.data)
            q = q.next

        ptr = ptr.next

    remain = None
    
    if p != None :
        remain = p

    elif q != None :
        remain = q

    while remain != None :
        # print('head = ',end = '')
        # printList(head)
        # print('ramain = ',end = '')
        # printList(remain)
        # print('*************************')
        ptr.next = Node(remain.data)
        remain = remain.next
        ptr = ptr.next

    return head

#################### FIX comand ####################   
# input only a number save in L1,L2
L1,L2 = input('Enter 2 Lists : ').split(' ')
LL1 = createList(L1.split(','))
LL2 = createList(L2.split(','))
print('LL1 : ',end='')
printList(LL1)
print('LL2 : ',end='')
printList(LL2)
m = mergeOrderesList(LL1,LL2)
print('Merge Result : ',end='')
printList(m)