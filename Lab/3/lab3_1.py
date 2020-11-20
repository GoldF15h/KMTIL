import sys

inp = input("Enter Input : ")
stack = []

for i in inp :
    #print(i)
    #print(stack)
    if i == '(' or i == '[':
        stack.append(i)
    else:
        if i == ']' :
            if len(stack) <= 0:
                print('Parentheses : Unmatched ! ! !')
                sys.exit()
            elif stack[-1] == '[' :
                stack.pop()
            else:
                print('Parentheses : Unmatched ! ! !')
                sys.exit()
        elif i == ')' :
            if len(stack) <= 0:
                print('Parentheses : Unmatched ! ! !')
                sys.exit()
            elif stack[-1] == '(' :
                stack.pop()
            else:
                print('Parentheses : Unmatched ! ! !')
                sys.exit()
if len(stack) == 0:
    print('Parentheses : Matched ! ! !')
else:
    print('Parentheses : Unmatched ! ! !')