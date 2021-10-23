inp = input('Enter Input : ').split('/')
arr_of_team = []
for i in inp :
    # print(i)
    team_info  =  i.split(',')
    team_name  =  team_info[0]
    team_score =  3*int(team_info[1]) + 1*int(team_info[3])
    team_gd    =  int(team_info[4]) - int(team_info[5])
    arr_of_team.append( [ team_name,team_score,team_gd ] )

# print(arr_of_team)
for starter in range(len(arr_of_team)) :

    for comare in range(0,len(arr_of_team)-starter-1) :

        if arr_of_team[comare][1] < arr_of_team[comare+1][1] :
            arr_of_team[comare] , arr_of_team[comare+1] = arr_of_team[comare+1] , arr_of_team[comare] 

        elif arr_of_team[comare][1] == arr_of_team[comare+1][1] :

            if arr_of_team[comare][2] < arr_of_team[comare+1][2] :
                arr_of_team[comare] , arr_of_team[comare+1] = arr_of_team[comare+1] , arr_of_team[comare] 

print('== results ==')
for i in arr_of_team :
    print('[\'{}\', {}, {}]'.format(i[0],{'points':i[1]},{'gd':i[2]}))