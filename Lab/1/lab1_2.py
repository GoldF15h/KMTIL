print('*** multiplication or sum ***')
a,b = input('Enter num1 num2 : ').split()
a = int(a)
b = int(b)
#print(a,b)
if a*b <= 1000 :
    print('The result is',a*b)  
else :
    print('The result is',a+b)  