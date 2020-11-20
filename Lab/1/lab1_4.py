print("*** Fun with Drawing ***\nEnter input : ",end="")
n = int(input())

for i in range(n):
    
    print("."*(n-(i+1)) + '*'+ '+'*(2*i-1) + ('*' if(i!=0) else '') + '.'*((2*n-3)-(2*i))+('*' if(i!=n-1) else '')+ '+'*(2*i-1) + ('*' if(i!=0) else '')+ "."*(n-(i+1)))

for j in range(2*(n-1)):

    print('.'*(j+1) + '*' + '+'*((4*n-7)-(2*j)) + ('*' if(j!=2*(n-1)-1) else '') + '.'*(j+1))