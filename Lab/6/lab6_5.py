def asteroid_collision(asts,index):
    if index <= len(asts) - 2 :
        left = asts[index]
        right = asts[index+1]

        if left > 0 and right < 0 :
            if abs(left) > abs(right) :
                asts.pop(index+1)
                return asteroid_collision(asts,0)
            elif abs(left) < abs(right) :
                asts.pop(index)
                return asteroid_collision(asts,0)
            else :
                asts.pop(index)
                asts.pop(index)
                return asteroid_collision(asts,0)

        else :
            return asteroid_collision(asts,index+1)
    else :
        return asts
        

x = input("Enter Input : ").split(",")
x = list(map(int,x))
print(asteroid_collision(x,0))