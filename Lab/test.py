def insertion_sort(unsorted_arr,sorted_arr=[],i=0) :
  if not unsorted_arr:
    print("sorted")
    print(sorted_arr)
    return
  else:
    if sorted_arr:
      select_insert(unsorted_arr, sorted_arr, 0, unsorted_arr.pop(0))
    else:
      sorted_arr.append(unsorted_arr.pop(0))
    insertion_sort(unsorted_arr,sorted_arr,i+1)
def select_insert(unsorted_arr, sorted_arr, current, data):
  global condition
  if len(sorted_arr) < condition:
    print(data,sorted_arr[current],current)
    if data > sorted_arr[current] and current < len(sorted_arr) - 1:
    #   print('base case insert')
      select_insert(unsorted_arr,sorted_arr,current+1,data)
    else:
      sorted_arr.insert(current, data)
      if unsorted_arr:
        print(f"insert {data} at index {current} : {sorted_arr} {unsorted_arr}")
      else:
        print(f"insert {data} at index {current} : {sorted_arr}")

def is_sort(lst):
    b = True
    for i in range(len(lst) - 1):
        if lst[i] > lst[i+1]:
            b = False
    return b
inp = list(map(int, input("Enter Input : ").split()))
condition = len(inp)
insertion_sort(inp)