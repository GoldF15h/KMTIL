def compare (a,b,arr,arrLen) :
    aPower = arr[a] + getAllThePower(a,arr,arrLen)
    bPower = arr[b] + getAllThePower(b,arr,arrLen)
    # print(aPower,bPower)
    if aPower == bPower :
        print(f'{a}={b}')
    elif aPower < bPower :
        print(f'{a}<{b}')
    else :
        print(f'{a}>{b}')

def getAllThePower(a,arr,arrLen) :
    if 2*a+2 < arrLen :
        return arr[2*a+1] + arr[2*a+2] + getAllThePower(2*a+1,arr,arrLen) + getAllThePower(2*a+2,arr,arrLen)
    elif 2*a+1 < arrLen :
        return arr[2*a+1] + getAllThePower(2*a+1,arr,arrLen)
    else :
        return 0

knights , match = input('Enter Input : ').split('/')
knights = [ int(x) for x in knights.split() ]
match = match.split(',')

# print(knights)
# print(match)

print(sum(knights))
for i in match :
    # print(i)
    compare(int(i.split()[0]),int(i.split()[1]),knights,len(knights))