def bi_search (l,r,arr,find) :
    # print(arr[l:r])
    if r - l > 1 :
        mid = (l+r)//2 
        if find < arr[ mid ] :
            bi_search(l, mid, arr, find)
        elif find > arr[ mid ] :
            bi_search(mid, r, arr, find)
        else :
            print('True')

    else :
        if arr[l] == find :
            print('True')
        else :
            print('False')

inp , finder = input('Enter Input : ').split('/')
finder = int(finder)
inp = list ( map (int,inp.split(' ')) )
# print(inp,finder)
bi_search(0,len(inp)-1,list(sorted(inp)),finder)