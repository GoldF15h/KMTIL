def odd_even(arr, s):

    if s ==  'L' :
        return arr
    elif s == 'S':
        return ''.join(arr)

print("*** Odd Even ***")
inp = input('Enter Input : ').split(',')
#print(inp)

op = []
#print('debug ',''.join(inp[1].split(' ')))
#print('debug ',inp[1].split(' '))
#print('size =',len(inp[1]))

if inp[0] == 'L' :
    if len(inp[1].split()) > 1:
        inp[1] = ''.join(inp[1].split(' '))
    else:
        #inp[1] = ''
        inp[1] = [ ''.join(inp[1].split(' ')) , ]
elif inp[0] == 'S':
    if len(inp[1].split()) != 1:
        inp[1] = ''
    

if inp[2] == 'Odd':
    for i in range(0,len(inp[1]),2):
        #print(i)
        op.append(inp[1][i])
else:
    for i in range(1,len(inp[1]),2):
        #print(i)
        op.append(inp[1][i])

print(odd_even(op, inp[0]))