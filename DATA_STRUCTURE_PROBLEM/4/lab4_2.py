inp = input("Enter Input : ").split(',')
# print(inp)
queue = []

for i in inp :

    
    # print(queue) # QUEUE DEBUG    

    if i == 'D': # OUT PUT FOR HEAD OF QUEUE

        if len(queue) == 0 :

            print( 'Empty' )
                
        else:

            print( queue[0].split(' ')[1] ) # PRINT NUMBER OF OTA
            queue.pop(0)
            
    else :

        if i.split(' ')[0] == 'EN': # CHECK IF IT'S NORMAL OTA

            queue.append( i )

        elif i.split(' ')[0] == 'ES': # CHECK IF IT'S VIP OTA

            #print('insert!!') # PRINT IF INSERT
            
            if len(queue) == 0:

                queue.append(i)

            else:
                for j in range(len(queue)): # FIND THE INDEX THAT LAST VIP OTA EXIST

                    #print(queue[j]) # INSERTING DEBUG

                    if queue[j].split(' ')[0] == 'EN' :

                        queue.insert( j,i )  # INSERT THE VIP OTA TO THE QUEUE
                        break

                    elif j == len(queue) - 1 :

                        queue.append( i )
            
