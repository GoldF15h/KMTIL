def convertToBinaryFrom0ToN(cureent,endPoint,digit) :
    print(format(cureent,'0'+str(digit)+'b'))
    if cureent < endPoint :
        convertToBinaryFrom0ToN(cureent+1,endPoint,digit)

inp = int(input('Enter Number : '))
if inp < 0 :
    print('Only Positive & Zero Number ! ! !')
else :
    if inp == 0 :
        convertToBinaryFrom0ToN(0,0,1)
    else :
        convertToBinaryFrom0ToN(0,(2**inp)-1,inp)