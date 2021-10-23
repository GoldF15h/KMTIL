inp = list(map(int,input('input : ').strip().split()))
#inp = sorted(set(inp),key = inp.index)
op = []
if len(inp) < 3 :
    print("Array Input Length Must More Than 2")
else:
    for i in range(0,len(inp)-2): 
        for j in range(i+1,len(inp)-1):
            for k in range(j+1,len(inp)):
                if inp[i] + inp[j] + inp[k] == 0:
                    #print(inp[i],inp[j],inp[k])
                    op.append( [inp[i],inp[j],inp[k]] ) 

op = list(set(x for l in op for x in l))
            
print(op)