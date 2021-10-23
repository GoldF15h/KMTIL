inp = input('Enter Input : ').split(',')
trees = []
#print(inp)

for i in inp:
    if i == 'B':

        counter = 0
        _max = 0

        for j in trees:
            if j > _max:
                _max = j
                counter += 1

        print(counter)

    elif i == 'S':

        for j in range(len(trees)):
            if trees[j] > 1:
                if trees[j] % 2 == 0:
                    trees[j] -= 1
                else :
                    trees[j] += 2
            
    else :
        trees.insert(0,int(i.split(' ')[1]))
        #print(trees)