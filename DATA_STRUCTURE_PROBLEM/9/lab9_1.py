import sys
inp = list(map(int,input("Enter Input : ").split()))
for i in range(len(inp)-1) :
    if inp[i] > inp[i+1] :
        print('No')
        sys.exit()

print('Yes')