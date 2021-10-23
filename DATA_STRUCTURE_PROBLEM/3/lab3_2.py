from operator import itemgetter

inp = input('Enter Input : ').split(',')
op = []
plates = []
for i in range(len(inp)):
    inp[i] = list(map(int,inp[i].split(' ')))

# inp = sorted(inp,key=itemgetter(0),reverse = True)
# print(inp)

for i in inp:
    plates.append(i)
    maxx = -1
    while plates != sorted(plates,key=itemgetter(0),reverse = True) :
        # print('hi')
        if plates[maxx][0] <= plates[maxx-1][0]:
            # print('hi')
            maxx = maxx-1
        else:
            op.append(plates[maxx-1])
            plates.pop(maxx-1)

for i in op:
    print(i[1])