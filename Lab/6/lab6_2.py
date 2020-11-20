def mergeList(a,b,op) :
    if len(a) > 0 and len(b) > 0 :

        if a[0] > b[0] :
            op.append(a[0])
            a.pop(0)
            return mergeList(a,b,op)

        else :
            op.append(b[0])
            b.pop(0)
            return mergeList(a,b,op)

    elif len(a) > 0 :
        return op + a

    else :
        return op + b

def mergeSort (arr) :

    if len(arr) >= 2 :
        halfSize = len(arr) // 2
        a = mergeSort(arr[:halfSize])
        b = mergeSort(arr[halfSize:])
        return mergeList(a,b,[])

    else :
        return arr

inp = list(map(int,input('Enter your List : ').split(',')))
print('List after Sorted :',mergeSort(inp))