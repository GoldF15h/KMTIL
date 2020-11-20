currentI = 1

def print1ToN(n):
    if int(n) <= 1 :
        print('1' + ' ',end = '')
        return None
    global currentI
    print(str(currentI)+' ',end = '')
    currentI += 1
    if currentI <= n :
        print1ToN(n)

def printNto1(n):
    if int(n) <= 1 :
        print('1' + ' ',end = '')
        return None
    print(str(n)+' ',end = '')
    n = n - 1 
    if n >= 1:
        printNto1(int(n))

n = int(input("Enter Input : "))

print1ToN(n)
printNto1(n)