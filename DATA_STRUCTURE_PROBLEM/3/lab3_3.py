inp = input('Enter Input : ').split(' ')
stack = []
combo = 0

for i in inp:
    # print(stack)
    stack.append(i)
    
    if len(stack) >= 3 :
        if stack[-1] == stack[-2] and stack[-2] == stack[-3] :
            for j in range(3):
                stack.pop()
            combo += 1

print(len(stack))

if len(stack) > 0:
    stack = stack[::-1]
    for i in stack:
        print(i,end='')
    print()
else:
    print('Empty')

if combo > 1:
    print('Combo :',combo,'! ! !')
