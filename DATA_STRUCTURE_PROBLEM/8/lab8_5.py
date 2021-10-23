vans , customer = input('Enter Input : ').split('/')
vans = [0]*int(vans)
customer = [ int(x) for x in customer.split(' ')]

for i in range(len(customer)) :
    # print('customer',i,'before booking',vans)
    while 0 not in vans :
        for j in range(len(vans)) :
            vans[j] -= 1

    for j in range(len(vans)) :
        if vans[j] == 0 :
            # print(vans)
            # minHeap(vans)
            print(f'Customer {i+1} Booking Van {j+1} | {customer[i]} day(s)')
            # print('--------------------------------------------------')
            vans[j] = customer[i]
            break
    

    