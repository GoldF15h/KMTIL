n=int(input("Enter Input : "))
d=n+1
r=1

for i in range(1,n+3):
    print("."*(d)+"#"*(r),end="")
    d-=1
    r+=1
    if i==1 or i==n+2:
            print("+"*(n+2),end="")
    else:
            print("+"+"#"*n+"+",end="")
    print("")
d=n+2
r=0
for i in range(1,n+3):
    
    if i==1 or i==n+2:
            print("#"*(n+2),end="")
    else:
            print("#"+"+"*n+"#",end="")
    print("+"*(d)+"."*(r),end="")
    d-=1
    r+=1
    print("")