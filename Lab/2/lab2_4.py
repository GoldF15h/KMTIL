def sum0(inpt) :
    result = []

    for i in range(len(inpt)):
        for j in range(len(inpt)):
            if j != i:
                for k in range(len(inpt)):
                    if(k != i and k != j):
                        if inpt[i]+inpt[j]+inpt[k] == 0:
                            s = [inpt[i],inpt[j],inpt[k]]
                            
                            result.append(s) 
                        else:
                            continue
                    else:
                        continue
            else:
                continue 
    for i in result:
        i.sort()
    return result

    
inpt = list(map(int,input('Enter Your List : ').split()))
if(len(inpt)<3):
    print("Array Input Length Must More Than 2")
else :
    ans = sum0(inpt)
    lst = []
    for i in ans:
        if i in lst:
            pass
        else:
            lst.append(i)
   
          

print(lst)




