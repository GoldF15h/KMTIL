import sys

class StackCalc :
    def __init__(self):
        self.cal = []
        self.stack = [0]

    def run (self,arg):
        # print(arg)
        self.cal = arg.split()
        for i in range(len(self.cal)):

            if self.cal[i].isdigit():
                self.stack.append(int(self.cal[i]))

            elif self.cal[i] == '+' or self.cal[i] == '-' or self.cal[i] == '*' or self.cal[i] == '/':
                if self.cal[i] == '+':

                    self.stack.append(self.stack[-1] + self.stack[-2])
                    self.stack.pop(-2)
                    self.stack.pop(-2)

                if self.cal[i] == '-':
                    self.stack.append(self.stack[-1] - self.stack[-2])
                    self.stack.pop(-2)
                    self.stack.pop(-2)

                if self.cal[i] == '*':
                    self.stack.append(self.stack[-1] * self.stack[-2])
                    self.stack.pop(-2)
                    self.stack.pop(-2)
                    
                if self.cal[i] == '/':
                    self.stack.append(self.stack[-1] / self.stack[-2])
                    self.stack.pop(-2)
                    self.stack.pop(-2)

            elif self.cal[i] == 'DUP' or self.cal[i] == 'POP' or self.cal[i] == 'PSH' :
                
                if self.cal[i] == 'DUP':
                    self.stack.append(self.stack[-1])
                
                if self.cal[i] == 'POP':
                    self.stack.pop()
                    

            else :
                print('Invalid instruction: '+self.cal[i])
                sys.exit()

        #print(self.stack)


    def getValue(self):
        return int(self.stack[-1])
    


print("* Stack Calculator *")
arg = input("Enter arguments : ")
machine = StackCalc()
machine.run(arg)
print(machine.getValue())