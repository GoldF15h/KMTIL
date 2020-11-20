inp = input('Enter String and Code : ')
value,key = inp.split(',')

_key = list(str(key))

deCode = list( ''.join( value.split(' ') ) )
enCode = []

for char in deCode :
    
    #print(int(_key[0]),int(_key[0])-1)
    #print(char.islower())
    
    if char.islower() :
        enCode.append( chr( ((ord(char) + int(_key[0]) - ord('a'))% 26) + ord('a')  )  )
        _key.append( _key.pop(0) )
    else :
        enCode.append( chr( ((ord(char) + int(_key[0]) - ord('A'))% 26) + ord('A')  )  )
        _key.append( _key.pop(0) )
    
print('Encode message is : ',enCode)
print('Decode message is : ',deCode)