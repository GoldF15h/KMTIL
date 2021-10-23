def find_alphabet (str) :
    for i in str :
        if i.isalpha() :
            return i

inp = input('Enter Input : ').split()

for starter in range(len(inp)) :

    for cur in range(len(inp)-1-starter) :
        if ord(find_alphabet(inp[cur])) > ord(find_alphabet(inp[cur+1])) :
            inp[cur] , inp[cur+1] = inp[cur+1] , inp[cur]

print(' '.join(inp))
