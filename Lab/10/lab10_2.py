arr , finder = input('Enter Input : ').split('/') 
arr = list ( map ( int , arr.split() ) )
finder = list ( map (int , finder.split() ) )
# print (arr,finder)
for find in finder :
    # print('-'*20)
    closest = arr[0] - find
    cloaset_value = arr[0]
    FGV = False 
    for i in range(0,len(arr)) :
        # print ( find ,' -> ',arr[i] , 'closet value = ',cloaset_value , 'diff =',closest)
        if arr[i] > find :
            # print('greater' , 'cur diff =',closest,'compet =',arr[i]-find)
            if closest > arr[i] - find or closest <= 0:
                # print('closer')
                closest = arr[i] - find
                cloaset_value = arr[i]
                FGV = True

    if FGV :
        print(cloaset_value)
    else :
        print('No First Greater Value')