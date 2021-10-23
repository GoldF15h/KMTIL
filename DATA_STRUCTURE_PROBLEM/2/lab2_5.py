class funString:
    def __init__(self,s,num):
        self.s=s
        self.num=num
        if int(num)==1:
            self.lenString()
        elif int(num)==2:
            self.upperLower()
        elif int(num)==3:
            self.reverseString()
        elif int(num)==4:
            self.delcharRepeat()

    def lenString(self):
        print(len(self.s))
    def upperLower(self):
        lis=[]
        for i in self.s:
            if i>='A' and i<='Z':
                i=ord(i)+32
                i=chr(i)               
                lis.append(i)
                
            elif i>='a' and i<='z':
                i=ord(i)-32
                i=chr(i)
                lis.append(i)
        for n in range(0,len(lis)):
            print(lis[n],end='')
    def reverseString(self):
        for j in range(-1,-len(self.s)-1,-1):
            print(self.s[j],end='')
    def delcharRepeat(self):
        seted=set()
        for k in self.s:
            seted.add(k)

        seted = sorted(seted,key=self.s.index)
        for l in range(0,len(seted)):
            print(seted[l],end='')
print('Enter String and Number of Function : ',end='')
x,y=input().split()
funString(x,y)