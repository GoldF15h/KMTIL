import sys

def sort (arr) :

    sorted_list = []
    for selector in range(len(arr)) :
        inserted = False

        for current_spot in range(len(sorted_list)) :

            if sorted_list[current_spot] > inp[selector] :
                cur = current_spot
                sorted_list.insert(cur,arr[selector])
                inserted = True
                break

        if not inserted :
            sorted_list.append(inp[selector])

    return(sorted_list)

inp = input('Enter Input : ')
inp = list(map(int,list(inp)))
# print(inp)

check = [0]*10
isDuplicate = False
isSort = False 
isRevSort = False

for i in inp :
    check[i] += 1
    if check[i] > 1 :
        isDuplicate = True

if len(inp) in check :
    print('Repdrome')
    sys.exit()

for i in range(len(inp)-1) :
    if inp[i] > inp[i+1] :
        isRevSort = True
    elif inp[i] < inp[i+1] :
        isSort = True

if isSort and not isRevSort:
    if isDuplicate :
        print('Plaindrome')
    else :
        print('Metadrome')
elif isRevSort and not isSort:
    if isDuplicate :
        print('Nialpdrome')
    else :
        print('Katadrome')
else :
    print('Nondrome')