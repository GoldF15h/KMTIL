def is_sorted (arr,cur=0) :
    if cur <= len(arr)-2 :
        if arr[cur] <= arr[cur+1] :
            return is_sorted(arr,cur+1)
        else :
            return False
    else :
        return True 

def sel_swap(arr,max_run_size,cur=0,cur_max=0) :

    if cur >= max_run_size :
        if arr[cur] <= arr[cur_max] :
            arr[cur] , arr[cur_max] = arr[cur_max] , arr[cur]
            print(f"swap {arr[cur_max]} <-> {arr[cur]} : {arr}")
        
    else :  

        if arr[cur] > arr[cur_max] :
            cur_max = cur

        sel_swap(arr,max_run_size,cur+1,cur_max)

def sel_sort(arr,times) :
    # print(arr,times)
    if not is_sorted(arr) and times >= -10:
        sel_swap(arr,times)
        sel_sort(arr,times-1)
    

inp = list(map(int,input('Enter Input : ').split()))
sel_sort(inp,len(inp)-1)
print(inp)