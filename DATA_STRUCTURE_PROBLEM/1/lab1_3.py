from itertools import permutations

print("*** Fun with permute ***")
inp = list(map(int,input('input : ').strip().split(',')))
print('Original Cofllection:  ',end = '')
print(inp)
print('Collection of distinct numbers:\n ',end='')
counter = 0
perm = list(permutations(inp))

for i in perm:
    counter = counter + 1
#print(perm[0][0])
print('[',end = '')
for i in range(-1,-1*(counter+1),-1) :
    print('[',end = '')
    for j in range(0,len(inp)):
        print(perm[i][j],end = '')
        if j != len(inp) - 1 :
            print(', ',end = '')
    print(']',end = '')
    if i != -1*counter:
        print(', ',end ='')
    #print(i)
print(']',end = '')