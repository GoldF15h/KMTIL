def mapping (inp):
    mylist = list()
    outPut = list()
    mylist.append('')
    mylist[0] = inp[0]
    mybool = bool

    for i in range(0,len(inp)):
        #print(inp[i],end=' ')
        mybool = False
        
        for j in range(0,len(mylist)):
            #print("mylistlen = " , len(mylist))
            if mylist[j] == inp[i]:
                #print(j)
                outPut.append(j)
                mybool = True

        if not(mybool) :
            #print("register ",end = '')
            mylist.append(inp[i])
            #print(len(mylist)-1)
            outPut.append(len(mylist)-1)
        
    return outPut

inp = input("Enter String : ")
outPut = mapping(inp)
print(outPut)