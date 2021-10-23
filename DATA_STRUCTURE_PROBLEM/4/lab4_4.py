_employees,_action = input('Enter Input : ').split('/')

# print(employees,' +++ ',action)
# employees = dict()
employees = []
_employees = _employees.split(',')
_action = _action.split(',')
queue = []

# print(_employees)

for value in _employees :

    # print(value)
    # employees.update( { value.split(' ')[1] : value.split(' ')[0] } )
    employees.append([value.split(' ')[0],value.split(' ')[1]])

# print(employees)

for action in _action :

    if action == 'D' :

        if len(queue) > 0:
            
            # print('POP')
            print(queue[0][1])
            queue.pop(0)

        else :

            print('Empty')

    elif action.split(' ')[0] == 'E':

        id = action.split(' ')[1]
        # team = employees.get(id)

        for i in employees :
            if i[1] == id :
                team = i[0] 
                break

        #print(id,team)
        # queue.sort(key = lambda x: x[0]) # SORT BY FIRST ELEMENT
 
        if len(queue) <= 1 :

            queue.append([team,id])

        else :

            appended = False 
            for j in range( -1,-1*len(queue)-1,-1) :
                
                # print('check ',queue[j])

                if queue[j][0] == team :
                    
                    if j == -1 :
                        queue.append([team,id])
                    else :
                        queue.insert(j+1,[team,id])
                    appended = True
                    break

            if not appended:

                queue.append([team,id])

    # print(action,' -> ',queue)
