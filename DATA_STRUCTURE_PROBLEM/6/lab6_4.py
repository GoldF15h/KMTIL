def pantip(k, arr, path):
    if len(arr) > 0 :
        passPath1 = path.copy()
        passPath2 = path.copy()
        passPath1.append(arr[0])
        a = pantip(k,arr[1:],passPath1)
        b = pantip(k,arr[1:],passPath2)
        return a + b
    elif sum(map(int,path)) == k :
        print(' '.join(list(map(str,path))))
        return 1
    else :
        return 0

inp = input('Enter Input (Money, Product) : ').split('/')
arr = [int(i) for i in inp[1].split()]
pattern = pantip(int(inp[0]), arr, [])
print("Krisada can purchase Product: {0} with: {1} Baht | {2} Pattern".format(arr, inp[0], pattern))