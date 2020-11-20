import math
class Node:
    def __init__(self, value):
        self.data = value
        self.next = None

    def __str__(self):
        return str(self.value)

def createLL(LL):
    head = Node(LL[0])
    ptr = head
    for i in range(1,len(LL)) :
        ptr.next = Node(LL[i])
        ptr = ptr.next        

    return head

def printLL(head):
    ptr = head
    op = []
    while ptr != None :
        op.append(str(ptr.data))
        ptr = ptr.next

    return ' '.join(op)

def SIZE(head):
    ptr = head
    _size = 0
    while ptr != None :
        ptr = ptr.next
        _size += 1

    return _size

def scarmble(head, b, r, size):
    ptr = head
    cuttingPoint = math.floor( b * size / 100 )

    tmpList = []
    while ptr != None :
        tmpList.append(ptr.data)
        ptr = ptr.next
        
    # print('tmplist = ',' '.join(tmpList))
    # print('cutting point = ',cuttingPoint)
    bottomUpList = tmpList[cuttingPoint:] + tmpList[:cuttingPoint]
    print('BottomUp {:.3f} % : {}'.format(b,' '.join(bottomUpList)))

    riffleList = []
    lifingPoint = math.floor( r * size / 100 )
    
    # print('lifting poitn = ',lifingPoint)
    # print('ramain = ',( size - ( 2 * (size - lifingPoint) )))

    riffleListFront = bottomUpList[:lifingPoint]
    riffleListBack  = bottomUpList[lifingPoint:]
    # print('riffleFront ',riffleListFront)
    # print('riffleBack',riffleListBack)

    while len(riffleListFront) != 0 and len(riffleListBack) != 0 :
        riffleList.append(riffleListFront[0])
        riffleList.append(riffleListBack[0])
        riffleListFront.pop(0)
        riffleListBack.pop(0)

    # print('riffileList ',riffleList)

    if len(riffleListFront) != 0 :
        riffleList += riffleListFront
    else :
        riffleList += riffleListBack

    # for i in range( size ) :
    #     riffleList += bottomUpList[i:i+lifingPoint+1:lifingPoint]

    # while len(riffleList) > size : # บัคตอนเลขน้อยๆ
    #     riffleList.pop()

    print('Riffle {:.3f} % : {}'.format( r,' '.join(riffleList)))
    print('Deriffle {:.3f} % : {}'.format( r,' '.join(bottomUpList)))
    print('Debottomup {:.3f} % : {}'.format( b,' '.join(tmpList)))

inp1, inp2 = input('Enter Input : ').split('/')
print('-' * 50)
h = createLL(inp1.split())
for i in inp2.split('|'):
    print("Start : {0}".format(printLL(h)))
    k = i.split(',')
    if k[0][0] == "B" and k[1][0] == "R":
        scarmble(h, float(k[0][2:]), float(k[1][2:]), SIZE(h))
    elif k[0][0] == "R" and k[1][0] == "B":
        scarmble(h, float(k[1][2:]), float(k[0][2:]), SIZE(h))
    print('-' * 50)