_normal , _mirror = input('Enter Input (Normal, Mirror) : ').split(' ')
normalExplode , mirrorExplode , failToInterrupt = 0 , 0 , 0
mirrorItem = []
normal , mirror = [],[]
normal = list(_normal)
mirror = list(_mirror)

# print(normal,mirror)
# CALCULATE EXPLOTION OF MIRROR SIDE
i = 0
while i <= len(mirror)-2 :
    # print(len(mirror),i,mirror[i]+mirror[i+1]+mirror[i+2])
    # print(mirror,mirrorExplode,mirrorItem,end = '\n')

    if mirror[i] == mirror[i+1] and mirror[i+1] == mirror[i+2] :
        mirrorItem.append(mirror[i])
        mirrorExplode += 1
        mirror.pop(i)
        mirror.pop(i)
        mirror.pop(i)
        i = 0
        continue

    i += 1
    
i = 0
while i < len(normal)-2 :
    # print(normal[i],normal[i+1],normal[i+2],sep = '')
    # print(i,len(normal),normal,normalExplode,mirrorItem)
    
    if normal[i] == normal[i+1] and normal[i+1] == normal[i+2] :
        interrupt = False
        if len(mirrorItem) > 0 :
            normal.insert(i+2,mirrorItem[-1])
            mirrorItem.pop()
            interrupt = True
            # print('insert ->',normal,mirrorItem)

        if normal[i] == normal[i+1] and normal[i+1] == normal[i+2] :
            # print('recheck ->',normal[i]+normal[i+1]+normal[i+2])
            if interrupt :
                failToInterrupt += 1
            else :
                normalExplode += 1
            normal.pop(i)
            normal.pop(i)
            normal.pop(i)
            i = 0
            continue
    
    i += 1

print('NORMAL :')
print(len(normal))

if len(normal) == 0 :
    print('Empty')

else :
    print(''.join(normal[::-1]))

print(normalExplode,'Explosive(s) ! ! ! (NORMAL)')

if failToInterrupt > 0 :
    print('Failed Interrupted',failToInterrupt,'Bomb(s)')

print('------------MIRROR------------')
print(': RORRIM')
print(len(mirror))

if len(mirror) == 0 :
    print('ytpmE')

else :
    print(''.join(mirror))

print('(RORRIM) ! ! ! (s)evisolpxE',mirrorExplode)
